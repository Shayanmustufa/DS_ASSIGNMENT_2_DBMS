#include<iostream>
#include<ctime>
#include "random_record_generator.h"
#include "random_record_generator.cpp"
#include "avl_tree.h"
using namespace std;

avl_t* search(avl_t* root,int val){
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
int height(avl_t* root){
	if(root==NULL)return 0;
	return root->height;
}

int updateheight(avl_t* root){
	if(root==NULL)return 0;
	return 1+max(height(root->left),height(root->right));
	}
int getbalance(avl_t* root){
	
	if(root==NULL)return 0;
	return height(root->left)-height(root->right);
}


avl_t* left_rotate(avl_t* root){
	avl_t* y=root->right;
	avl_t* temp=y->left;
	 root=y->left;
	root->right=y;
	
	updateheight(root);
	updateheight(y);
return y;
}
avl_t* right_rotate(avl_t* root){
	avl_t* y=root->left;
	avl_t* temp=y->right;
	y->right=root;
	root->left=temp;
	
	updateheight(root);
updateheight(y);

return y;
}


avl_t* insert(avl_t* root,int id,string name,int age){
	
	if(root==NULL)return new avl_t(id,name,age);
	if(root->id>id){
		root->left=insert(root->left,id,name,age);
	}else if(root->id<id){
		root->right=insert(root->right,id ,name,age);
	}
	
	updateheight(root);
	
	int bal=getbalance(root);
	
	if(bal>1 && id<root->left->id){
		return left_rotate(root);
	}
	if(bal<-1 && id>root->right->id){
		return right_rotate(root);
	}
	
	if(bal>1 && id>root->left->id){
		root->left=left_rotate(root->left);
		return right_rotate(root);
	}
	
	if(bal<-1 && id<root->right->id){
		root->right=right_rotate(root->right);
		return left_rotate(root);
	}
	return root;
}

avl_t* delete_t(avl_t* root,int id){
	if(root==NULL)return root;
	
	if(root->id>id){
		root->left=delete_t(root->left,id);
	}
	if(root->id<id){
		root->right=delete_t(root->right,id);
	}
	
	if(root->id==id){
		
		if(root->left==NULL && root->right==NULL){
			avl_t* temp=root;
			delete root;
			return temp;
		}
		if(root->left!=NULL && root->right==NULL){
			avl_t* temp=root->left;
			delete root;
			return temp;
		}
		
		if(root->right!=NULL && root->left==NULL){
			avl_t* temp=root->right;
			delete root;
			return temp;
			
		}
		
		if(root->right!=NULL && root->left!=NULL){
			avl_t* succ=root->right;
			while(succ->left!=NULL){
				succ=succ->left;
			}
			root->id=succ->id;
			root->right=delete_t(root->right,succ->id);
			return root;
		}
	}
			updateheight(root);
	
	int bal=getbalance(root);
	
	if(bal>1 && id<root->left->id){
		return left_rotate(root);
	}
	if(bal<-1 && id>root->right->id){
		return right_rotate(root);
	}
	
	if(bal>1 && id>root->left->id){
		root->left=left_rotate(root->left);
		return right_rotate(root);
	}
	
	if(bal<-1 && id<root->right->id){
		root->right=right_rotate(root->right);
		return left_rotate(root);
	}
	
	return root;
}
void inorder(avl_t* root){
	if(root==NULL)return;
	inorder(root->left);
	cout<<" ID: "<<root->id<<" Name: "<<root->name<<" Age: "<<root->age<<endl;

	inorder(root->right);
}
