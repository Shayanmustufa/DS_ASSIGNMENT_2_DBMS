#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <string>
using namespace std;

class BTreeNode {
public:
    int *ids;                 // Array of IDs
    string *names;            // Array of names
    int *ages;                // Array of ages
    int t;                    // Minimum degree
    BTreeNode **children;     // Array of child pointers
    int n;                    // Current number of keys
    bool leaf;                // True if leaf node

    BTreeNode(int _t, bool _leaf);
    void traverse();
    BTreeNode* search(int id);
    void insertNonFull(int id, const string& name, int age);
    void splitChild(int i, BTreeNode* y);

    void remove(int id);
    int findKey(int id);

    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

class BTree {
public:
    BTreeNode* root;  // Pointer to root node
    int t;            // Minimum degree

    BTree(int _t) {
        root = NULL;
        t = _t;
    }

    void traverse() {
        if (root != NULL) {
            root->traverse();
        }
    }

    BTreeNode* search(int id) {
        return (root == NULL) ? NULL : root->search(id);
    }

    void insert(int id, const string& name, int age) {
        if (root == NULL) {
            root = new BTreeNode(t, true);
            root->ids[0] = id;
            root->names[0] = name;
            root->ages[0] = age;
            root->n = 1;
        } else {
            if (root->n == 2 * t - 1) {
                BTreeNode* s = new BTreeNode(t, false);
                s->children[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->ids[0] < id) {
                    i++;
                }
                s->children[i]->insertNonFull(id, name, age);
                root = s;
            } else {
                root->insertNonFull(id, name, age);
            }
        }
    }

    void remove(int id) {
        if (root == NULL) {
            cout << "The tree is empty.\n";
            return;
        }
        root->remove(id);
        if (root->n == 0) {
            BTreeNode* tmp = root;
            if (root->leaf) {
                root = NULL;
            } else {
                root = root->children[0];
            }
            delete tmp;
        }
    }
};

#endif // B_TREE_H
