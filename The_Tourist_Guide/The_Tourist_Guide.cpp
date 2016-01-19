#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#define MAX_VAL 999999999

using namespace std;

class graph{
public:
	int init();
	int v, e;
	int start, end, num;
	int **map;
	vector<list<int> > g;
	void print();
	void fbw();
};

int graph::init(){


	scanf("%d %d", &v, &e);
	if(!v && !e) return 1;

	map=new int*[v+1];
	for(int i=0;i<=v;i++){
		list<int> temp;
		g.push_back(temp);
		map[i]=new int[v+1];
		for(int j=0;j<=v;j++){
			map[i][j]=-1;
		}
		map[i][i]=0; // 배열 초기화
	}
	
	int v1, v2, weight;
	for(int i=0;i<e;i++){
		scanf("%d %d %d", &v1, &v2, &weight);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		map[v1][v2]=weight;
		map[v2][v1]=weight;
	}

	scanf("%d %d %d", &start, &end, &num);
	
	return 0;
}

void graph::print(){
	list<int>::iterator it;
	cout << endl;
	for(int i=1;i<v;i++){
		cout << i << " - ";
		for(it=g[i].begin();it!=g[i].end();++it){
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << endl;

	for(int i=1;i<=v;i++){
		for(int j=1;j<=v;j++)
			cout << map[i][j] << " ";

		cout << endl;
	}
	

}

void graph::fbw(){

	queue<int> q;	
	q.push(start);
	
	map[start][start]=MAX_VAL;

	int current;
	list<int>::iterator it;


	while(!q.empty()){
		current=q.front();
		q.pop();

		for(it=g[current].begin();it!=g[current].end();++it){
			
		//	cout << current << "->" << *it << endl;
		//	if(map[current][*it]==-1) continue;

			if(map[*it][*it]==0){//no chk{
				if(map[current][current]>map[current][*it])
					map[*it][*it]=map[*it][current];
				else
					map[*it][*it]=map[current][current];	
			
			//	map[current][*it]=-1;// delete edge
			//	map[*it][current]=-1;// delete edge
				q.push(*it);
			
			}else if(map[current][current]>map[*it][*it] &&
						map[current][*it]>map[*it][*it]){
				
				if(map[current][current]>map[current][*it])
					map[*it][*it]=map[current][*it];
				else
					map[*it][*it]=map[current][current];
			
			//	map[current][*it]=-1;// delete edge
			//	map[*it][current]=-1;// delete edge
				q.push(*it);
			}
			



		}
		
	}

	//	cout << end << map[end][end] << endl;
	if(map[end][end]-1==0){
		printf("Minimum Number of Trips = %d\n\n", !0);
		return;
	}
	int r=num/(map[end][end]-1);
	int i=0;
	if(num%(map[end][end]-1)>0) i=1;
	printf("Minimum Number of Trips = %d\n\n", r+i);	
	
}


int main(){

	/*
		1. 입력 : 정점의 수, 간선의 수
			- 0 0 입력시 프로그램 종료
			- 간선의 수만큼 추가 입력 = 정점, 정점, 비중
			- 시작 위치와 도착 위치, 총 관람객의 수 입력

		2. 출력 : 최소 왕복 횟수


		3. how to?
			순회

			100*100 배열, map[i][i]=자신 까지 오는데 걸리는 최대 비용

			구분 - 정점의 값 과 간선의 값중 작은 값을 다음 정점의 값으로 지정
		
		4. 필요한 자료구조
		    100*100 비중 배열 0 = no chk, -1 = delete edge
			vector<list<int> > 그래프

	*/
	int T=0;
	while(1){
		graph* G=new graph();
		if(G->init()) break;
		++T;
//		G->print();
		printf("Scenario #%d\n", T);
		G->fbw();
		//G.print();
		delete(G);
	}

	return 0;
}
