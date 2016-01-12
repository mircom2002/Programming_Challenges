#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <queue>

using namespace std;

class Node;
class Vertex;
/*

	최대한 단순하게!, 인접리스트로!

	1. 정점 - 데이터, 인접한 정점 리스트
	
*/

class LinkedList{
public:
	LinkedList();
	Node* header;
	Node* tailer;
	Node* addNode(Vertex *v);
	Node* searchNode(Vertex *v);
	Node* searchNode(string n);
	int size;
};

class Vertex{ // 정점, 이름
public:
	Vertex(string);
	string name;
	int ervalue;
	LinkedList *alist;
};

Vertex::Vertex(string n){
	name=n;
	alist=new LinkedList();
	ervalue=99999999;
}


class Node{
public:
	Node(string n);
	Node(Vertex *v);
	Vertex* elem;
	Node* next;
};

Node::Node(Vertex *v){
	elem=v;
	next=NULL;
}

Node::Node(string n){
	elem=new Vertex(n);
	next=NULL;
}


LinkedList::LinkedList(){
	header=NULL;
	tailer=NULL;
	size=-1;
}

Node* LinkedList::addNode(Vertex *v){
	
	Node* st=searchNode(v);

	if(searchNode(v)!=NULL) return st;

	Node* temp=new Node(v);


	size++;
	if(size==0){
		header=temp;
		tailer=temp;
		return temp;
	}

	Node* temp2=header;
	for(int i=0;i<size-1;i++){
		temp2=temp2->next;
	}

	temp2->next=temp;
	tailer=temp;
	return temp;
}

Node* LinkedList::searchNode(Vertex* v){
	if(size==-1) return NULL;

	Node* temp=header;
	for(int i=0;i<=size;i++){
		if(temp->elem==v) return temp;
		temp=temp->next;
	}
	return NULL;
}

Node* LinkedList::searchNode(string n){
	if(size==-1) return NULL;
	Node* temp=header;
	for(int i=0;i<=size;i++){
		if(temp->elem->name==n) 
			return temp;
//		else
//			cout << temp->elem->name << " <-> " << n << endl;
		temp=temp->next;
	}
	return NULL;
}

class Graph{
public:
	Graph();
	LinkedList* vlist;
	void addNew(string *n, int num);
	void print();
	void BFS();
	void printValue(string);
};

Graph::Graph(){
	vlist=new LinkedList();
}

void Graph::addNew(string *n, int num){

	Node** t_array=new Node*[num];
	

	for(int i=0;i<num;i++){
		t_array[i]=vlist->searchNode(n[i]);
		if(t_array[i]==NULL){
			Vertex* v=new Vertex(n[i]);
			t_array[i]=vlist->addNode(v);
		}
//			cout << "not found! : " << n[i] << endl;
//		}else
//			cout << "found : " << n[i] << endl;
	}
//	for(int i=0;i<num;i++)
//		cout << t_array[i]->elem->name;

	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
			if(i==j) continue;
			t_array[i]->elem->alist->addNode(t_array[j]->elem);
		}
	}
	
//	cout << vlist->size << endl;
}

void Graph::print(){
	cout << endl;
	int vsize=vlist->size;
	Node* temp=vlist->header;
	for(int i=0;i<=vsize;i++){
		cout << temp->elem->name << "(" << temp->elem->ervalue <<") - ";
		int asize=temp->elem->alist->size;
		Node* temp2=temp->elem->alist->header;

		for(int j=0;j<=asize;j++){
			cout << temp2->elem->name << ",";
			temp2=temp2->next;
		}
		cout << endl;
		temp=temp->next;
	}
}

void Graph::BFS(){
	
	Node* temp=vlist->searchNode("Erdos, P.");
	if(temp==NULL) return;

	temp->elem->ervalue=0;	
	queue<Node*> q;
	q.push(temp);

	while(!q.empty()){
		Node* cur=q.front();
		int cur_count=cur->elem->ervalue+1;
		int size=cur->elem->alist->size;
		cur=cur->elem->alist->header;
		for(int i=0;i<=size;i++){
			if(cur->elem->ervalue>cur_count){
				cur->elem->ervalue=cur_count;
				q.push(cur);
			}
			cur=cur->next;
		}
		q.pop();
	}


}

void Graph::printValue(string s){

	Node* temp=vlist->searchNode(s);

	if(temp==NULL){
		cout << s << " infinity" <<endl;
		return;
	}

	if(temp->elem->ervalue==99999999)
		cout << s << " infinity" << endl;
	else
		cout << s << " " << temp->elem->ervalue << endl;
}

string trim(string s){
	
	int start=0;
	int end=s.size()-1;

	while(s.at(start)==' ') start++;
	while(s.at(end)==' ') end--;
	
	return s.substr(start, end-start+1);
}

int main(){
	/*
		1. 이름 : 논문 데이터를 입력받는다.
		2. 이름을 쪼개어 정점에 저장한다.
		3. 모든 입력 받은 후 간선으로 연결한다.
		4. 너비 우선 탐색으로 탐색한다.
	*/
	int T;
	scanf("%d", &T);

	for(int testCase=1;testCase<=T;testCase++){
		int n, m;
		scanf("%d %d\n", &n, &m);

		string input;	
		Graph G;
		for(int i=0;i<n;i++){
			getline(cin, input);
			
			int start=0;
			int end=0;
			int comma;
			int count=0;
			string s[1000];
			
			while(1){

// 문자열 분리
// 1. ~:까지 자르고
// 2. 자르기
// 2-1 . 후 , 
				comma=input.find(".", start);
				if(comma==string::npos) break;

				while(end < comma && end != string::npos)
					end=input.find(",", end+1);
//				cout << start << comma << end <<endl;
				
				if(end==string::npos){
					break;
				}
				
				s[count]=trim(input.substr(start, end-start));
				start=end+1;
				count++;
			}
			
			end=input.find(":", start);
			if(1<end-start){ 
				s[count]=trim(input.substr(start, end-start));
				count++;
			}
			G.addNew(s, count);
		}

//		G.addNew(paper, n);
		G.BFS();
//		G.print();
		cout << "Scenario " << testCase << endl;
		for(int i=0;i<m;i++){
			getline(cin, input);
			G.printValue(input);
		}
	}
	return 0;
}
