#ifndef BST_TREE_H
#define BST_TREE_H

#include <string>
#include <vector>
using namespace std;


class bst{
	public:
		int age;
		int id;
		string name;
		int height;
		bst* right;
		bst* left;
		
	bst(int i,string n,int ag){
		left=right=NULL;
		id=i;
		name=n;
		age=ag;
	}
};

bst* insert(bst* root,int val,string name,int age);
bst* delete_t(bst* root,int val);
bst* search(bst* root,int val);
void inorder(bst* root);
bst* left_rotate(bst* root);
bst* right_rotate(bst* root);

#endif
