#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <vector>
using namespace std;


class avl_t{
	public:
		int age;
		int id;
		string name;
		int height;
		avl_t* right;
		avl_t* left;
		
	avl_t(int i,string n,int ag){
		height=1;
		left=NULL;
		right=NULL;
		id=i;
		name=n;
		age=ag;
		
	
	}
};

avl_t* insert(avl_t* root,int val,string name,int age);
avl_t* delete_t(avl_t* root,int val);
avl_t* search(avl_t* root,int val);


int updateheight(avl_t* root);
int height(avl_t* root);
int getbalance(avl_t* root);
void inorder(avl_t* root);
avl_t* left_rotate(avl_t* root);
avl_t* right_rotate(avl_t* root);

#endif
