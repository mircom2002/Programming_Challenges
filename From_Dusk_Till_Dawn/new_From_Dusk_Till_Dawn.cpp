#include <iostream>
#include <stdio.h>
#include <map>
#include <list>
#include <string.h>
#include <queue>
#define MAX_NUM 99999999

using namespace std;

int main(){
	/*
		1. 입력 
			테스트케이스의 수
			노선의 개수
			출발역 도착역 출발시간 걸리는시간

			출발역 도착역

		2. 출력
			최소한의 피의 개수

		3. 필요한구조
			ㄱ. 출발역 -> 도착역의 유향 그래프
				- 처음 입력 과정에서 18시~06시를 초과하는 입력은 제외
			ㄴ. 지나온 역을 체크할 배열 - dfs이용

		4. how to?
			DFS를 이용, 중요한 것은 최단 경로가 아닌 최소 비용	
	*/	

	int testCase;
	int num;
	map<string, list<pair<string, pair<int, int> > > >::iterator it;
	list<pair<string, pair<int, int> > >::iterator lit;
	map<string, pair<int, int> >::iterator mit;

	scanf("%d", &testCase);
	for(int T=1;T<=testCase;T++){
		map<string, list<pair<string, pair<int, int> > > > graph;
		map<string, pair<int, int> > maplist;

		scanf("%d", &num);
		char t1[40], t2[40];
		int start, take;
		for(int i=0;i<num;i++){
			scanf("%s %s %d %d", t1, t2, &start, &take);
			if(start<6) start+=24;
			if(start<18 || start+take>30) continue;
			
			it=graph.find(t1);

			if(it==graph.end()){//출발 지역이 그래프에 있는지 확인
				list<pair<string, pair<int, int> > > temp;
				temp.push_back(make_pair(t2, make_pair(start, start+take)));
				graph.insert(make_pair(t1, temp)); // 출발역과 도착역, 시간을 그래프에 추가
			}else
				it->second.push_back(make_pair(t2, make_pair(start, start+take))); // 그래프에 존재할 시 도착역과 시간만 추가
		

			mit=maplist.find(t2);	// 맵에 도착역 없을시 도착역 추가
			if(mit==maplist.end()){
				maplist.insert(make_pair(t2, make_pair(MAX_NUM, 18)));
			}					

			mit=maplist.find(t1);
			if(mit==maplist.end()){
				maplist.insert(make_pair(t1, make_pair(MAX_NUM, 18)));
			}
		}
		
		scanf("%s %s", t1, t2);
		string s, e;
		s=t1; e=t2;

		printf("Test Case %d.\n", T);
		if(s==e){
			printf("Vladimir needs 0 litre(s) of blood.\n");
			continue;
		}if(maplist.find(t1)==maplist.end() || maplist.find(t2)==maplist.end()){
			printf("There is no route Vladimir can take.\n");
			continue;
		}
		
//		dfs(graph, maplist, s, e, 18);

		/*
			BFS로 도전 혹은 DP

			1. 한 출발역에서 도착역까지 최단 경로(카운트가 적고, 도착 시간이 적은 순)를 구한다.

		*/
/*
		for(mit=maplist.begin();mit!=maplist.end();++mit){
			
			cout << mit->first << mit->second.first << mit->second.second << endl;

		}
*/


		queue<string> q;
		q.push(s);

		maplist.find(s)->second.first=0;
		while(!q.empty()){

			string current=q.front();
			it=graph.find(current);
			mit=maplist.find(current);
			int currentTime=mit->second.second;
			int currentDay=mit->second.first;
			q.pop();
			if(it==graph.end()) continue;	
			
			for(lit=it->second.begin();lit!=it->second.end();++lit){
				
				int tempDay;
				int tempTime;

				if(lit->second.first < currentTime){
					tempDay=currentDay+1;
					tempTime=lit->second.second;
				}else{
					tempDay=currentDay;
					tempTime=lit->second.second;
				}
			
				//cout << current << "->" << lit->first << endl;

				mit=maplist.find(lit->first);
				
				if(mit->second.first==MAX_NUM){
					mit->second.first=tempDay;
					mit->second.second=tempTime;
					q.push(lit->first);
				}else if(mit->second.first==tempDay && mit->second.second > tempTime){
					mit->second.second=tempTime;
					q.push(lit->first);
				}else if(mit->second.first>tempDay){
					mit->second.first=tempDay;
					mit->second.second=tempTime;
					q.push(lit->first);
				}
			}
		}
/*
		for(it=graph.begin();it!=graph.end();++it){
			cout << it->first << " - ";
			for(lit=it->second.begin();lit!=it->second.end();++lit){
				cout << lit->first << "(" << lit->second.first << "," << lit->second.second << "), ";
			}
			cout << endl;
		}
*/

		mit=maplist.find(e);

		if(mit->second.first==MAX_NUM)
			printf("There is no route Vladimir can take.\n");
		else
			printf("Vladimir needs %d litre(s) of blood.\n", mit->second.first);
	}


	return 0;
}
