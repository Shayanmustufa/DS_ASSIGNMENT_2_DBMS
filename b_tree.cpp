#include<iostream>
#include "b_tree.h"
using namespace std;

BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    ids = new int[2 * t - 1];
    names = new string[2 * t - 1];
    ages = new int[2 * t - 1];
    children = new BTreeNode *[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
        cout<<"Data Organized as a table "<<endl;
    for (int i = 0; i < n; i++) {
        if (!leaf) {
            children[i]->traverse();
        }
        cout << "ID: " << ids[i] << ", Name: " << names[i] << ", Age: " << ages[i] << endl;
    }
    if (!leaf) {
        children[n]->traverse();
    }
}

BTreeNode* BTreeNode::search(int id) {
    int i = 0;
    while (i < n && id > ids[i]) {
        i++;
    }

    if (i < n && ids[i] == id) {
        return this;
    }

    if (leaf) {
        return NULL;
    }

    return children[i]->search(id);
}

void BTreeNode::insertNonFull(int id, const string& name, int age) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && ids[i] > id) {
            ids[i + 1] = ids[i];
            names[i + 1] = names[i];
            ages[i + 1] = ages[i];
            i--;
        }
        ids[i + 1] = id;
        names[i + 1] = name;
        ages[i + 1] = age;
        n++;
    } else {
        while (i >= 0 && ids[i] > id) {
            i--;
        }
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (ids[i + 1] < id) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(id, name, age);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->ids[j] = y->ids[j + t];
        z->names[j] = y->names[j + t];
        z->ages[j] = y->ages[j + t];
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }

    y->n = t - 1;

    for (int j = n; j > i; j--) {
        children[j + 1] = children[j];
    }
    children[i + 1] = z;

    for (int j = n - 1; j > i; j--) {
        ids[j + 1] = ids[j];
        names[j + 1] = names[j];
        ages[j + 1] = ages[j];
    }

    ids[i] = y->ids[t - 1];
    names[i] = y->names[t - 1];
    ages[i] = y->ages[t - 1];
    n++;
}

void BTreeNode::remove(int id) {
    int idx = findKey(id);

    if (idx < n && ids[idx] == id) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            cout << "Key " << id << " not found in the tree.\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);
        if (children[idx]->n < t) {
            fill(idx);
        }

        if (flag && idx > n) {
            children[idx - 1]->remove(id);
        } else {
            children[idx]->remove(id);
        }
    }
}

int BTreeNode::findKey(int id) {
    int idx = 0;
    while (idx < n && ids[idx] < id) {
        ++idx;
    }
    return idx;
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; i++) {
        ids[i - 1] = ids[i];
        names[i - 1] = names[i];
        ages[i - 1] = ages[i];
    }
    n--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int id = ids[idx];
    if (children[idx]->n >= t) {
        int pred = getPredecessor(idx);
        ids[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        ids[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(id);
    }
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf) {
        cur = cur->children[cur->n];
    }
    return cur->ids[cur->n - 1];
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf) {
        cur = cur->children[0];
    }
    return cur->ids[0];
}

void BTreeNode::fill(int idx) {
    if (idx > 0 && children[idx - 1]->n >= t) {
        borrowFromPrev(idx);
    } else if (idx < n && children[idx + 1]->n >= t) {
        borrowFromNext(idx);
    } else {
        if (idx < n) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    for (int i = child->n - 1; i >= 0; i--) {
        child->ids[i + 1] = child->ids[i];
        child->names[i + 1] = child->names[i];
        child->ages[i + 1] = child->ages[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->ids[0] = ids[idx - 1];
    child->names[0] = names[idx - 1];
    child->ages[0] = ages[idx - 1];

    if (!leaf) {
        child->children[0] = sibling->children[sibling->n];
    }

    ids[idx - 1] = sibling->ids[sibling->n - 1];
    names[idx - 1] = sibling->names[sibling->n - 1];
    ages[idx - 1] = sibling->ages[sibling->n - 1];

    child->n++;
    sibling->n--;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->ids[child->n] = ids[idx];
    child->names[child->n] = names[idx];
    child->ages[child->n] = ages[idx];

    if (!child->leaf) {
        child->children[child->n + 1] = sibling->children[0];
    }

    ids[idx] = sibling->ids[0];
    names[idx] = sibling->names[0];
    ages[idx] = sibling->ages[0];

    for (int i = 1; i < sibling->n; i++) {
        sibling->ids[i - 1] = sibling->ids[i];
        sibling->names[i - 1] = sibling->names[i];
        sibling->ages[i - 1] = sibling->ages[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->n++;
    sibling->n--;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->ids[t - 1] = ids[idx];
    child->names[t - 1] = names[idx];
    child->ages[t - 1] = ages[idx];

    for (int i = 0; i < sibling->n; i++) {
        child->ids[i + t] = sibling->ids[i];
        child->names[i + t] = sibling->names[i];
        child->ages[i + t] = sibling->ages[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++) {
            child->children[i + t] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < n; i++) {
        ids[i - 1] = ids[i];
        names[i - 1] = names[i];
        ages[i - 1] = ages[i];
    }

    for (int i = idx + 2; i <= n; i++) {
        children[i - 1] = children[i];
    }

    child->n += sibling->n + 1;
    n--;
    delete sibling;
}
