#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <queue>
#include <list>
#include <map>
#define MAX_NUM 999999999

using namespace std;

map<string, list<pair<string, pair<int, int> > > >::iterator it;
list<pair<string, pair<int, int> > >::iterator lit, lit2;

int main(){

	int testCase;
	scanf("%d", &testCase);

	for(int T=1;T<=testCase;T++){
	
		map<string, list<pair<string, pair<int, int> > > > graph; // 출발 지역, list(도착지역, (출발시간, 도착시간))

		int num, num2;
		scanf("%d", &num);

		string input;
		for(int i=0;i<num;i++){
			list<pair<string, pair<int, int> > > temp;
			cin >> input;
			graph.insert(make_pair(input, temp));
		}

		scanf("%d", &num);

		for(int i=0;i<num;i++){
			scanf("%d", &num2);
			int t;
			int time[100];
			string name[100];
			for(int j=0;j<num2;j++){
				cin >> t >> name[j];
				time[j]=(t/100)*60+(t%100);
				if(j>0)
					graph.find(name[j-1])->second.push_back(make_pair(name[j], make_pair(time[j-1], time[j])));
			}

		}

		int current;
		string start, end;

		scanf("%d", &current);
		cin >> start;
		cin >> end;

		// 출발역에서 도착역 까지 경로 BFS로 확인
		// 가장 빨리 도착, 가장 적은 시간에 도착

		current=(current/100)*60+(current%100);
		queue<pair<string, int > > q; // 현재위치, 현재시간

		int current_time;
		string current_city;

		int departure=MAX_NUM;
		int arrival=MAX_NUM;

		if(graph.find(start)==graph.end()) {
			printf("Scenario %d\n\n", T);
			continue;
		}

		for(lit2=graph.find(start)->second.begin();lit2!=graph.find(start)->second.end();++lit2){
			
			if(lit2->second.first<current) continue;
			q.push(make_pair(lit2->first, lit2->second.second));

			while(!q.empty()){

				current_city=q.front().first;
				current_time=q.front().second;

				q.pop();
				
				if(current_city==end){
					// 1. 가장 먼저 도착한 거
					// 2. 같이 도착 했을 경우 가장 늦게 출발 한것

					
					if(arrival>current_time){
						arrival=current_time;
						departure=lit2->second.first;
					}else if(arrival==current_time){
						if(departure<lit2->second.first){
							departure=lit2->second.first;
						}
					}
					continue;
				}
				
				it=graph.find(current_city);
				
				for(lit=it->second.begin();lit!=it->second.end();++lit){
					if(lit->second.first>=current_time){
						q.push(make_pair(lit->first, lit->second.second));
					}
				}
			}

		}

		printf("Scenario %d\n", T);

		if(departure==MAX_NUM)
			printf("No connection\n");
		else{
			printf("Departure %.4d %s\n", (departure/60)*100+departure%60, start.c_str());
			printf("Arrival   %.4d %s\n", (arrival/60)*100+arrival%60, end.c_str());
		}
		printf("\n");			

/*
		for(it=graph.begin();it!=graph.end();++it){
			cout << it->first << "-";
			for(lit=it->second.begin();lit!=it->second.end();++lit){
				cout << lit->first << "(" << lit->second.first << ", " << lit->second.second << ") ";
			}
			cout << endl;
		}
			
*/

	
	}

	return 0;
}
