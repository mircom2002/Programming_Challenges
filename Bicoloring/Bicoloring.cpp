#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;

int bfs(vector<list<int> > g, int v){

	if(v==1) return 0;

	int *color=new int[v];
	for(int i=0;i<v;++i) color[i]=-1;
	
	//color=0 : 검은색, 1=빨간색

	queue<int> q;
	q.push(g[1].front());
	color[q.front()]=0;
	while(!q.empty()){
		
		int current=q.front();
		int current_color=(color[current]+1)%2;
		q.pop();
		list<int>::iterator it;
	
		if(g[current].size()==0) continue;

		for(it=g[current].begin();it!=g[current].end();++it){
	
//			cout << current << " - " << *it << " = " << g[current].size() << endl;

			if(color[*it]==-1){
				q.push(*it);
				color[*it]=current_color;
			}else if(color[*it]!=current_color) return 1;
		}


	}

	return 0;
}




int main(){

	/*
		1. 정점의 수, 간선의 수 입력, 0입력시 프로그램종료
		
		2. self-loop 이 없는 무방향 그래프로 구성
		
		3. 서로 다른 색 칠할시  NOT BICOLORABLE, 아닐시 BICOLORABLE
		 
		4. 구조
			색칠 여부를 저장하는 배열(0~199)
			vertex-list형식의 그래프
			너비우선탐색
	*/

	int v_num, e_num;
	int v1, v2;
	while(1){
		scanf("%d", &v_num);
		if(v_num==0) break;
		scanf("%d", &e_num);
	
		vector<list<int> > graph;
		
		for(int i=0;i<v_num;++i){
			list<int> temp;
			graph.push_back(temp);
		}
		
		for(int i=0;i<e_num;++i){
			scanf("%d %d", &v1, &v2);
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);
		}

		if(bfs(graph, v_num))
			printf("NOT BICOLORABLE.\n");
		else
			printf("BICOLORABLE.\n");

	}

	return 0;
}
