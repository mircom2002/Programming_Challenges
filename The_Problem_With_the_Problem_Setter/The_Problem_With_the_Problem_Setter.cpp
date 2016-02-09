#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <queue>
#include <map>

using namespace std;

class bipolar{
public:
	int input();
	void output();
	void print();
private:
	int forward(int, int);
	int backward(int, int);

	vector<list<int> > stgraph;
	map<pair<int, int>, int> edge;
	list<int> result[100];

	vector<list<int> >::iterator it;
	list<int>::iterator lit;
	map<pair<int, int>, int>::iterator mit;

	int problem_num, category_num;
	int s, t;
	int* problem;
};

int bipolar::input(){

	// s->문제은행->카테고리->t
	// 문제은행(~1000), 카테고리(~100)
	// s->문제은행 용량 : 1
	// 문제은행->카테고리 용량 : 1
	// 카테고리->t : 용량 = 카테고리 별 문제수(problem_num)

	scanf("%d %d", &category_num, &problem_num);
	
	if(!category_num && !problem_num) return 1;

	int current=0;
	problem=new int[category_num+1];

	for(int i=1;i<=category_num;i++){
		scanf("%d", &problem[i]);
		current+=problem[i];
	}

	s=0;
	t=category_num+current+1;

	for(int i=s;i<=t;i++){
		list<int> temp;
		stgraph.push_back(temp);
	}

	// s<->문제은행<->카테고리 연결
	int temp_num, temp;
	for(int i=1;i<=problem_num;i++){
		scanf("%d", &temp_num);
		for(int j=0;j<temp_num;j++){
			scanf("%d", &temp);
			for(int k=0;k<=problem[temp]
			stgraph[i].push_back(problem_num);
			stgraph[temp+problem_num].push_back(i);

			edge.insert(make_pair(make_pair(i, temp+problem_num), 1));
			edge.insert(make_pair(make_pair(temp+problem_num, i), 0));
		}
		stgraph[0].push_back(i);
		stgraph[i].push_back(0);

		edge.insert(make_pair(make_pair(0, i), 1));
		edge.insert(make_pair(make_pair(i, 0), 0));
	}

	// 카테고리<->t 연결
	current=problem_num;
	for(int i=0;i<category_num;i++){
		for(int j=1;j<=problem_num[i];j++){
		current++;
		stgraph[i+problem_num].push_back(t);
		stgraph[t].push_back(i+problem_num);

		edge.insert(make_pair(make_pair(i+problem_num, t), 1));
		edge.insert(make_pair(make_pair(t, i+problem_num), 0));
		}
	}

	return 0;
}

void bipolar::print(){
	
	int i=0;
	for(it=stgraph.begin();it!=stgraph.end();++it){
		printf("%d : ", i++);
		for(lit=it->begin();lit!=it->end();++lit){
			printf("%d, ", *lit);
		}
		printf("\n");
	}

	printf("map---\n");

	for(mit=edge.begin();mit!=edge.end();++mit){
		printf("%d > %d (%d)\n", mit->first.first, mit->first.second, mit->second);
	}
}

void bipolar::output(){
	
	/* 
	모든 문제에 대한 탐색 실시
	
	탐색 종료 후 각 카테고리별 문제수가 요구하는 문제수 보다 (t~카테고리번호 간선의 가중치) 작으면 0 출력

	 요구하는 문제수 만큼 문제 존재시 역 방향으로 탐색하여 문제 출력
	*/
	// bfs(s, t) <- 더이상 진행 할 수 없으면 0을 리턴
	
	/*
	while(bfs(s, t, NULL)){
		cout << 1 << endl;
	}	
	*/
	for(int i=0;i<problem_num;i++, forward(s, t));
//	while(forward(s, t));
	/*
	while(bfs(t, s, result)){
		cout << 2 << endl;
	}

	for(int i=0;i<category_num;i++){
		cout << 3;
		for(lit=result[i].begin();lit!=result[i].end();++lit){
			cout << *lit << " ";			
		}
		cout << endl;
	}
	*/		
}

int bipolar::forward(int start, int end){

	int count=0, current=start, chk=1;
	int *a=new int[t+1];
	memset(a, 0, (t+1)*sizeof(int));

	// s에서 시작 가능한 간선이 있는지 확인
		
	for(int i=1;i<=problem_num;i++){
		if(edge.find(make_pair(0, i))->second!=0) current=i;
	}

	if(current==start) return 0;

	a[start]=1;
	a[current]=1;

	list<pair<int, int> > temp_list[t+1];
	list<pair<int, int> >::iterator tlit;
	temp_list[count].push_back(make_pair(start, current));

	queue<pair<int, int> > q; // 현재 정점, 카운트
	q.push(make_pair(current, count));

	while(chk && !q.empty()){

		cout << current << endl;

		current=q.front().first;
		count=q.front().second+1;
		q.pop();
		for(lit=stgraph[current].begin();lit!=stgraph[current].end();++lit){
			if(!a[*lit] && edge.find(make_pair(current, *lit))->second){
				cout << current << *lit << endl;
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

	cout << current << endl;
	if(chk) return 1;

	for(int i=count;i>=0;i--){
		for(tlit=temp_list[i].begin();tlit!=temp_list[i].end();++tlit){
			
			if(current==tlit->second){
				cout << tlit->first << tlit->second << endl;
				current=tlit->first;
				edge.find(make_pair(tlit->first, tlit->second))->second--;
				edge.find(make_pair(tlit->second, tlit->first))->second++;
				break;
			}

		}
	}

	return 1;
}

int bipolar::backward(int start, int end){
	// backward, 뒤로 탐색, 역탐색
	
	int current=start;
	int *a=new int[t+1];
	memset(a, 0, (t+1)*sizeof(int));

	// s에서 시작 가능한 간선이 있는지 확인
		
	for(int i=1;i<=category_num;i++){
		if(edge.find(make_pair(start, i+problem_num))->second!=0) current=i;
	}

	if(current==start) return 0;

	a[start]=1;
	a[current]=1;

	queue<int> q;
	q.push(current);

	while(!q.empty()){

		current=q.front();
		q.pop();

		for(lit=stgraph[current].begin();lit!=stgraph[current].end();++lit){
			


		}



	}


}


int main(){

	while(1){		
		bipolar test;
		if(test.input()) return 0;
		test.output();
		test.print();
//		test.output();

	}

	return 0;
}
