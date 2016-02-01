#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#define MAX_NUM 9999
using namespace std;

class node{
public:
	node(node* p, int n, int v):parent(p), num(n), value(v){};
	node* parent;
	int num;
	int value;
};

class tree{
public:
	tree(int);
	bool command(int, int, int);
	node** a;
	int find(int, int, int);
	void print();
	int num;
};


void swap(int &a, int &b){
	int c=a;
	a=b;
	b=c;
}

tree::tree(int n){
	num=n;
	a=new node*[num];

	for(int i=0;i<num;i++){
		a[i]=new node(NULL,i, 0);
	}

	a[0]->value=0;
}

bool tree::command(int cmd, int v1, int v2){
	
	int temp, value;

	if(cmd==1 || cmd==3) 
		temp=1;
	else
		temp=-1;

	if(!cmd && !v1 && !v2) return false;
	
	if(cmd==1 || cmd==2){
	
		if(a[v2]->parent==NULL){
			a[v2]->parent=a[v1];
			a[v2]->value=temp;
			return true;
		}
		value=find(v1, v2, temp);
		if(value==0) return true;	
//		cout << value << endl;
		if(value!=temp){
			printf("-1\n");
		}

	}else{
		value=find(v1, v2, temp);

		if(value==0){
			printf("0\n");		
			return true;
		}
		
		if(temp==1){
			if(value==1)
				printf("1\n");
			else
				printf("0\n");
		}else
			if(value==1)
				printf("0\n");
			else
				printf("1\n");

	}
	return true;
}


int tree::find(int v1, int v2, int c){

	/*
		start node에서 계속 parent로 올라가고

		end node에서 계속 parent로 올라가다 

		서로 만나는 점이 있을 때

		그 값이 같을 경우 1

		값이 다를 경우 2

		값이 없을 경우 0

		v1의 경우 기준값이므로 v2가 parent를 따라 올라왔을 때 v1을 만나면 그 때의 값을 리턴하면 됨.


	*/
	
	int *temp=new int[num];

	for(int i=0;i<num;i++) temp[i]=MAX_NUM;

	node* n = a[v1];
	int value;
	int current;

	temp[v1]=n->value;

	n=n->parent;
	current=temp[v1];

	while(n!=NULL){
		temp[n->num]=current;
//		printf("1 %d(%d)\n", n->num, current);
		current=n->value*current;
		n=n->parent;
	}
	

	n=a[v2];

	if(temp[v2]<MAX_NUM)		
		if(temp[v2]==n->value)
			return 1;
		else
			if(temp[v2]==0)
				return n->value;
			else
		 		return -1;

	temp[v2]=n->value;
	n=n->parent;

	current=temp[v2];

	while(n!=NULL){
//		printf("2 %d(%d)\n", n->num, current);
		if(temp[n->num]<MAX_NUM){	
			if(temp[n->num]==current)
				return 1;
			else
				if(temp[n->num]==0)
					return current;
				else
					return -1;
		}

		temp[n->num]=current;
		current=n->value*current;
		n=n->parent;
	}


	return 0;
}

void tree::print(){

	for(int i=0;i<num;i++){
		node* temp=a[i];
		while(temp!=NULL){
			printf("%d(%d) ->", temp->num, temp->value);
			temp=temp->parent;
		}
		printf("\n");
	}
		



}

int main(){

	int num;
	scanf("%d", &num);
	
	tree t(num);

	int command, v1, v2;
	while(1){
		scanf("%d %d %d", &command, &v1, &v2);
		
		if(v1 > v2) swap(v1, v2);
		
		if(!t.command(command, v1, v2)) break;
	
	}

	t.print();
	return 0;
}
