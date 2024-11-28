#include<iostream>
#include<ctime>
#include "avl_tree.cpp"
#include "avl_tree.h"
#include "bst_tree.cpp"
#include  "b_tree.h"
#include "b_tree.cpp"
using namespace std;

int main(){
	
	//Below is the main Function for the database management system,using all 3 three types of trees.
	
 bst* r1_bst=NULL;
 		avl_t* r1=NULL;
 		BTree b1(3);
 			int ranAge;
 			int ranSt;
 					int ranID;
 					
 			//below loop is helping in random generation of data , and it's insertion;
 		//have "inserted" values in both trees with same seed and loop::
 		
		 for(int i=0;i<11500;i++){
		int ranID=generateRandomID(2,20000);
		int ranAge=generateRandomAGE(1,92);
		string ranSt=generateRandomName(3);
		r1=insert(r1,ranID,ranSt,ranAge);
		r1_bst=insert(r1_bst,ranID,ranSt,ranAge);
	    b1.insert(ranID,ranSt,ranAge);
	}
//	inorder(r1);cout<<endl;
	//b1.traverse();
	
	

/// search,and delete block of code for bst	

/*for(int i=8;i<10510;i++){
			bst* temp1=search(r1_bst,i);
	if(temp1!=NULL){
		cout<<"Found"<<endl;
		cout<<temp1->id<<" "<<temp1->name<<" "<<temp1->age<<endl;
	}else{
		cout<<"Not Found"<<endl;
	}
}*/
bst* temp=delete_t(r1_bst,6990);
inorder(temp);   //Method for traversing , with this the deletion can also be confirmed.
	 

	// search,and delete  block of code for avl/*
 /*  for(int i=8;i<10510;i++){
	avl_t* temp2=search(r1,i);
	if(temp2!=NULL){
		cout<<"Found"<<endl;
		cout<<temp2->id<<" "<<temp2->name<<" "<<temp2->age<<endl;
	}else{
		cout<<"Not Found"<<endl;
	}
}*/
	avl_t* temp22=delete_t(r1,6990);
	inorder(temp22);
	
	//search,and delete block of code for b-trees;
	BTreeNode* temp3=new BTreeNode(2,true);
 /* for(int i=8;i<10510;i++){
temp3->search(i);
if(temp3!=NULL){
	cout<<"Found"<<endl;
	cout<<*temp3->ids<<" "<<*temp3->names<<" "<<*temp3->ages;
}else{
	cout<<"Not Found "<<endl;
}*/
temp3->removeFromLeaf(445);
temp3->traverse();
	

}
