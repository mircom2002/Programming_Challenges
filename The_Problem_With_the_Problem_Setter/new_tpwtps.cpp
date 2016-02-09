#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <string.h>

using namespace std;

class stgraph{
public:
	int input();
	void output();
	void print();
private:

	void forward(int, int);
	int backward(int, int);

	vector<list<int> > graph;
	map<pair<int ,int>, int> edge;

	list<int>::iterator lit;
	map<pair<int, int>, int>::iterator mit;

	int problem_num, category_num;
	int *category, *increase;
	int s, t;
};

int stgraph::input(){

	scanf("%d %d", &category_num, &problem_num);
	
	if(!problem_num && !category_num) return 1;
	
	category=new int[category_num+1];
	increase=new int[category_num+1];
	increase[0]=0;

	int temp1, temp2=0;

	for(int i=1;i<=category_num;i++){
		scanf("%d", &category[i]);
		increase[i]=category[i]+increase[i-1];
		temp2+=category[i];
	}

	s=0;
	t=s+problem_num+temp2+1;
	
	for(int i=s;i<=t;i++){
		list<int> temp;
		graph.push_back(temp);
	}


	for(int i=1;i<=problem_num;i++){
		scanf("%d", &temp1);
		for(int j=1;j<=temp1;j++){
			scanf("%d", &temp2);
			for(int k=increase[temp2-1]+1;k<=increase[temp2];k++){
				graph[i].push_back(problem_num+k);
				graph[problem_num+k].push_back(i);
			
				edge.insert(make_pair(make_pair(i, problem_num+k), 1));
				edge.insert(make_pair(make_pair(problem_num+k, i), 0));
			}
		}
		graph[0].push_back(i);
		graph[i].push_back(0);
		
		edge.insert(make_pair(make_pair(0, i), 1));
		edge.insert(make_pair(make_pair(i, 0), 0));
	}

	for(int i=problem_num+1;i<t;i++){
		graph[i].push_back(t);
		graph[t].push_back(i);

		edge.insert(make_pair(make_pair(i, t), 1));
		edge.insert(make_pair(make_pair(t, i), 0));
	}

	return 0;
}


void stgraph::output(){
	for(int i=1;i<=problem_num;i++) 
		forward(i, t);

	//check;

	list<int> result[category_num];
	int temp;

	for(int i=0;i<category_num;i++){
		for(int j=increase[i]+1;j<=increase[i+1];j++){
			temp=backward(problem_num+j, s);
			if(temp==-1) {
				printf("0\n");
				return;
			}

			result[i].push_back(temp);
		}
	}
	
	for(int i=0;i<category_num;i++){
		for(lit=result[i].begin();lit!=result[i].end();++lit){
			printf("%d ", *lit);
		}
		printf("\n");
	}

}

void stgraph::forward(int start, int end){

	int *a=new int[t+1];
	memset(a, 0, (t+1)*sizeof(int));

	int current=start, count=0, chk=1;
	if(!edge.find(make_pair(0, current))->second) return;

	a[0]=1;
	a[current]=1;

	list<pair<int, int> > temp_list[t+1];
	list<pair<int, int> >::iterator tlit;

	temp_list[count].push_back(make_pair(0, current));

	queue<pair<int, int> > q;

	q.push(make_pair(current, count));

	while(chk && !q.empty()){

		current=q.front().first;
		count=q.front().second+1;
		q.pop();

		for(lit=graph[current].begin();lit!=graph[current].end();++lit){

			if(!a[*lit] && edge.find(make_pair(current, *lit))->second){
				
				a[*lit]=1;
				temp_list[count].push_back(make_pair(current, *lit));
				q.push(make_pair(*lit, count));

				if(*lit==end){
					current=*lit;
					chk=0;
					break;
				}
			}
		}
	}

	if(chk) return;

	for(int i=count;i>=0;i--){
		for(tlit=temp_list[i].begin();tlit!=temp_list[i].end();++tlit){
			if(current==tlit->second){
				current=tlit->first;
				edge.find(make_pair(tlit->first, tlit->second))->second--;
				edge.find(make_pair(tlit->second, tlit->first))->second++;
				break;
			}
		}
	}
}

int stgraph::backward(int current, int end){

	int *a=new int[t+1];
	memset(a, 0, (t+1)*sizeof(int));

	a[t]=1;
	a[current]=1;

	queue<int> q;
	q.push(current);

	while(!q.empty()){

		current=q.front();
		q.pop();

		for(lit=graph[current].begin();lit!=graph[current].end();++lit){
			
			if(!a[*lit] && edge.find(make_pair(current, *lit))->second){
				a[*lit]=1;
				q.push(*lit);

				if(*lit==end) {
					return current;
				}
			}
		}
	}

	return -1;
}


void stgraph::print(){

	for(int i=0;i<=t;i++){
		printf("%d -> ", i);
		for(lit=graph[i].begin();lit!=graph[i].end();++lit){
			printf("%d(%d), ", *lit, edge.find(make_pair(i, *lit))->second);
		}
		printf("\n");
	}

}

int main(){

	while(1){
		stgraph test;
		if(test.input()) return 0;
//		test.print();
		test.output();
//		test.print();
		
	}
	return 0;
}
