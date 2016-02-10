#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


class node{
public:
	node(node* p, int n):parent(p), num(n){};
	node* parent;
	int num;
	int relation;

	void set_relation(int r){
		relation=r;
	}

};

class ufset{
public:
	ufset();
	void set(int, int, int);
	void get(int, int, int);
	void print();
private:
	int num;
	node** list;
	int* make_array(int);
	int chk(int, int);
};


ufset::ufset(){
	scanf("%d", &num);
	list=new node*[num];

	for(int i=0;i<num;i++)
		list[i]=new node(NULL, i);

	list[0]->relation=1;
}

int* ufset::make_array(int n){

	int *a=new int[num];
	memset(a, 0, num*sizeof(int));

	node* temp=list[n];

	while(temp!=NULL){		
		a[temp->num]=1;
		temp=temp->parent;

	}

	return a;
}

int ufset::chk(int n1, int n2){
	
	if(n1>n2){
		n1=n1+n2;
		n2=n1-n2;
		n1=n1-n2;
	}

	int *arr=make_array(n1);
/*
	for(int i=0;i<10;i++){
		printf("%d\n", arr[i]);
  }
*/

	node* temp=list[n2];
	int current=1;
	while(temp!=NULL){
		current*=temp->relation;
		//printf("%d(%d)\n", temp->num, current);
		if(arr[temp->num]!=0)
			if(arr[temp->num]==current) 
				return 1;
			else
				return -1;
		
		temp=temp->parent;

	}

	return 0;
}

void ufset::set(int n1, int n2, int r){

	if(n1>n2){
		n1=n2+n1;
		n2=n1-n2;
		n1=n1-n2;
	}

	if(list[n2]->parent==NULL){
		list[n2]->parent=list[n1];
		list[n2]->set_relation(r);
		return;
	}

	int temp=chk(n1, n2);
	
	if(temp==-1){
		printf("-1\n");
	}

}

void ufset::get(int n1, int n2, int r){
	
	int temp=chk(n1, n2);
//	printf("chk value : %d\n", temp);
	if(temp!=r)
		printf("0\n");
	else
		printf("1\n");

}

void ufset::print(){

	for(int i=0;i<num;i++){

		node* temp=list[i];

		while(temp!=NULL){
			printf("%d(%d) ", temp->num, temp->relation);
			temp=temp->parent;
		}
		printf("\n");
	}

}

int main(){

	int temp, n1, n2, relation;
	ufset test;

	while(1){
		scanf("%d %d %d", &temp, &n1, &n2);	
		if(!temp && !n1 && !n2) return 0;
		
		if(temp%2==1) 
			relation=1;
		else
			relation=-1;

		if(temp<3)
			test.set(n1, n2, relation);
		else
			test.get(n1, n2, relation);

		//test.print();
	}



	return 0;
}


