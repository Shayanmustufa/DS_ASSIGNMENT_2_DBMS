#include<iostream>
#include "bst_tree.h"
using namespace std;



bst* insert(bst* root,int val,string name,int age){
if(root==NULL){
return new bst(val,name,age);
}

if(root->id>val){
root->left=insert(root->left,val,name,age);
}
if(root->id<val){
root->right=insert(root->right,val,name,age);
}

return root;
}

bst* search(bst* root,int val){
	if(root==NULL)return root;
	
	if(root->id>val){
	return search(root->left,val);
	}
	if(root->id<val){
		return search(root->right,val);
	}
	
	if(root->id==val){
		return root;
	}
	return root;
	
}

bst* delete_t(bst* root,int id){
if (root == NULL) 
        return root;

    // Navigate left or right
    if (id < root->id)
        root->left = delete_t(root->left, id);
    else if (id > root->id)
        root->right = delete_t(root->right, id);
    else {
        // Node to be deleted found
        if (root->left == NULL || root->right == NULL) {
            bst* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            // Node with two children
            bst* succ = root->right;
            while (succ->left != NULL)
                succ = succ->left;
            root->id = succ->id;
            root->right = delete_t(root->right, succ->id);
        }
    }
}


void inorder(bst* root){
	if(root==NULL)return;
	inorder(root->left);
	cout<<" ID: "<<root->id<<" Name: "<<root->name<<" Age: "<<root->age<<endl;

	inorder(root->right);
}
