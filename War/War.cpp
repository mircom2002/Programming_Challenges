#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <list>
#include <queue>

using namespace std;

vector<list<pair<int, int> > > graph;
map<pair<int, int>, int> graph_map;
map<pair<int, int>, int>::iterator gmap;
list<pair<int, int> >::iterator lit;


int BFS(int start, int end){

	int a[10000]={0};

	queue<int> q;
	q.push(start);
	a[start]=1;

	while(!q.empty()){
		int current=q.front();
		int value=a[current];
		graph_map.insert(make_pair(make_pair(start, current), a[current]));
		graph_map.insert(make_pair(make_pair(current, start), a[current]));
		q.pop();
		if(a[end]!=0) return a[end];
		
		for(lit=graph[current].begin();lit!=graph[current].end();++lit){
			if(a[lit->first]!=0) continue;

			a[lit->first]=lit->second*value;
			q.push(lit->first);
		}
	}

	return 0;
}


int main(){

	int num;
	scanf("%d", &num);


	for(int i=0;i<num;i++){
		list<pair<int, int> > temp;
		temp.push_back(make_pair(i, 1));
		graph.push_back(temp);
	}

	int command, v1, v2, temp, value;
	while(1){
		scanf("%d %d %d", &command, &v1, &v2);
		
		if(command==1 || command==3) 
			temp=1;
		else
			temp=-1;

		if(!command && !v1 && !v2) return 0;
			
		if(command==1 || command==2){
			gmap=graph_map.find(make_pair(v1, v2));
			/*
				1. gmap에 (v1, v2) 값이 있는지 확인
					- 있을 경우 temp와 같으면 continue;
					- 있고 temp와 다르면 -1출력후 continue;
				2. gmap에 (v1, v2) 값이 없을 경우 BFS 통해 
					- BFS(v1, v2)==temp || 0, 추가
					- BFS(v1, v2)!=temp, 추가
			*/
			if(gmap==graph_map.end()){
				value=BFS(v1, v2);
				if(value==temp) 
					continue;
				else if(value!=0){
					printf("-1\n");
					continue;
				}
			}else{
				if(gmap->second==temp)
					continue;
				else{
					printf("-1\n");
					continue;
				}
			}
	
			graph_map.insert(make_pair(make_pair(v2, v1), temp));
			graph_map.insert(make_pair(make_pair(v1, v2), temp));
			graph[v1].push_back(make_pair(v2, temp));
			graph[v2].push_back(make_pair(v1, temp));	
		}else{

			gmap=graph_map.find(make_pair(v1, v2));
			
			if(gmap==graph_map.end())
				value=BFS(v1, v2);
			else
				value=gmap->second;

			if(value==0){
				printf("0\n");
				continue;
			}

			if(command==3){
				if(value==1)
					printf("1\n");
				else
					printf("0\n");
			}else if(command==4){
				if(value==1)
					printf("0\n");
				else
					printf("1\n");
			}
		
		}	
	}
	return 0;
}
