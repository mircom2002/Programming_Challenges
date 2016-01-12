/*
	map과 list를 이용한 그래프(인접리스트)

	1. 입력 - string, 개행문자가 입력되기 전까지 입력받음
	2. 출력
		2-1. 인접리스트 출력
		2-2. 너비우선탐색 결과 출력

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <map>
#include <string>
#include <string.h>
#include <queue>

using namespace std;

class node{
public:
	node(string n, int v):name(n), value(v){};
	string name;
	int value;
};


class graph{
public:
	map<string, node*> v_list;
	map<node*, list<node*> > graphmap;

	node* addVertex(string);
	void addEdge(node*, node*);
	void printGraph();
	void BFS(string);
};

node* graph::addVertex(string name){
	node* temp;
	if(v_list.find(name)==v_list.end()){
		temp=new node(name, 0);
		v_list.insert(make_pair(name, temp));
		list<node*> templist;;
		graphmap.insert(make_pair(temp, templist));
		//cout << "INSERT " << name << endl;
	}else{
		temp=v_list.find(name)->second;
	}

	return temp;
}

void graph::addEdge(node* v1, node* v2){
	
	int size1=graphmap.find(v1)->second.size();
	int size2=graphmap.find(v2)->second.size();
	//cout << endl << endl << "STATE" << endl << endl;
	list<node *>::iterator it;

	if(size1>size2){
		list<node *> *temp=&graphmap.find(v2)->second;
		for(it=temp->begin();it!=temp->end();++it){
			node* t=*it;
			if(*it==v1){
			//	cout << "RETURN : "<<t->name << endl;
				return;
			}
			//cout << "NAME : " << t->name <<" , " << v1->name << endl;
		}

		temp->push_back(v1);
		//cout << v2->name << " PUSH" << endl;
		graphmap.find(v1)->second.push_back(v2);
		//cout << v1->name << " PUSH" << endl;
		//graphmap.find(v2)->second.push_back(v1);
	}else{
		list<node *> *temp=&graphmap.find(v1)->second;
		for(it=temp->begin();it!=temp->end();++it){
			if(*it==v2){
			//	cout <<"RETURN : " << t->name << endl;
				return;
			}
			//cout << "NAME : " <<t->name << " , " <<v2->name << endl;
		}
		temp->push_back(v2);
		//cout << v1->name << " PUSH" << endl;
		graphmap.find(v2)->second.push_back(v1);
		//cout << v2->name << " PUSH" << endl;
		//graphmap.find(v1)->second.push_back(v2);
	}
}

void graph::printGraph(){
	cout << "PRINT GRAPH!" << endl;
	map<node*, list<node*> >::iterator map_it;
	list<node *>::iterator list_it;

	for(map_it=graphmap.begin();map_it!=graphmap.end();++map_it){
		printf("%s(%d) - ", map_it->first->name.c_str(), map_it->first->value);
		//cout<< map_it->first->name << " - ";
		for(list_it=map_it->second.begin();list_it!=map_it->second.end();++list_it){
			printf("%s(%d)\t", (*list_it)->name.c_str(), (*list_it)->value);
			//cout << t->name << ", ";
		}
		cout << endl;
	}
}

void graph::BFS(string n){
	
	if(v_list.find(n)==v_list.end()) return;

	map<string, node *>::iterator init_it;
	for(init_it=v_list.begin();init_it!=v_list.end();++init_it){
		init_it->second->value=-1; // 초기화
	}

	node* temp=v_list.find(n)->second;
	temp->value=1;

	queue<node *> q;
	q.push(temp);

	list<node*>::iterator list_it;
	list<node*> templist;
	int curVal;

	while(!q.empty()){
		templist=graphmap.find(q.front())->second;
		curVal=q.front()->value;
		q.pop();

		for(list_it=templist.begin();list_it!=templist.end();++list_it){
			if((*list_it)->value==-1){
				(*list_it)->value=curVal+1;
				q.push(*list_it);
			}
		}
	}

	printGraph();
}

int main(){


	graph test;
	string input;


	while(1){
		getline(cin, input);
		if(input.size()<1) break;
		char *t=new char(input.size()+1);
		strcpy(t, input.c_str());
		char *token=strtok(t, " ");
		string temp1=string(token);
		token=strtok(NULL, " ");
		string temp2=string(token);
	
		/*
			temp1 - temp2가 이어져 있음을 나타냄.

			temp1이 맵에 있는데 temp2가 맵에 없는 경우
			  - temp2를 맵에 추가
			  - temp1에 temp2추가, temp2에 temp1추가

			temp2가 맵에 있는데 temp1이 맵에 없는 경우
			  - temp1을 맵에 추가
			  - temp1에 temp2추가, temp2에 temp1추가

			중복 방지가 어렵네..

			temp1과 temp2가 맵에 있는 경우 서로 연결되어 있는지를 확인

			  - 연결되어 있지 않을 경우 추가.
		*/
		if(temp1==temp2) continue;	// self-loop는 입력받지 않음			
		test.addEdge(test.addVertex(temp1), test.addVertex(temp2));
	}

//	test.printGraph();

	cout << "-------------------------------------------------------" << endl;

	test.BFS("a");
	return 0;
}
