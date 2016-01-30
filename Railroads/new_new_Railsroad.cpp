#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <queue>
#include <list>
#include <map>
#include <vector>
#define MAX_NUM 9999999

using namespace std;

map<string, pair<list<pair<string, pair<int, int> > >, list<pair<string, pair<int, int> > > > >::iterator it;
map<string, pair<int, int> >::iterator gmap;
list<pair<string, pair<int, int> > >::iterator lit;

struct node{
	node(int t, string n):time(t), name(n){};
	int time;
	string name;
};

class compareProblem {
public:
    bool operator()(node& t1, node& t2){
		if (t1.time > t2.time) return true;
		return false;
	}
};


int main(){

	/*
		가장 빨리 도착한  시간 중에 가장 늦은 출발

	*/
	int testCase;
	scanf("%d", &testCase);

	for(int T=1;T<=testCase;T++){
	
		map<string, pair<list<pair<string, pair<int, int> > >, list<pair<string, pair<int, int> > > > > graph; 
		// 출발 지역, 이전지역, (출발시간, 도착시간)), 다음지역, (출발시간, 도착시간)
		map<string, pair<int, int> > graph_map; // 해당 지역의 출발시간 / 도착시간
		
		int num, num2;
		scanf("%d", &num);

		string input;
		for(int i=0;i<num;i++){
			list<pair<string, pair<int, int> > > temp1, temp2;
			cin >> input;
			graph_map.insert(make_pair(input, make_pair(0, MAX_NUM)));
			graph.insert(make_pair(input, make_pair(temp1, temp2)));
		}

		scanf("%d", &num);

		priority_queue<node, vector<node>, compareProblem> pq;

		for(int i=0;i<num;i++){
			scanf("%d", &num2);
			int t;
			int time[100];
			string name[100];
			int k=0;
			for(int j=0;j<num2;j++){
				cin >> t >> input;
				node n(t, input);
				pq.push(n);
			}

			while(!pq.empty()){
				t=pq.top().time;
				time[k]=(t/100)*60+(t%100);
				name[k]=pq.top().name;
				k++;
				pq.pop();
			}

			for(int j=0;j<k;j++){
				if(j>0)
					graph.find(name[j])->second.first.push_back(make_pair(name[j-1], make_pair(time[j-1], time[j])));
				
				if(j<k-1)
					graph.find(name[j])->second.second.push_back(make_pair(name[j+1], make_pair(time[j], time[j+1])));
			}
		}

		/*
			graph.first = 현재 위치
			graph.second->first = 현재 역과 이전 역
			graph.second->second = 현재 역과 다음 역
		*/

		int current;
		string start, end;

		int departure=MAX_NUM;
		int arrival=MAX_NUM;

		scanf("%d", &current);
		cin >> start;
		cin >> end;

		current=(current/100)*60+(current%100);
		queue<pair<string, int > > q; // 현재위치, 현재시간

		// 가장 빠른 도착시간 구하기
		string current_city;
		int current_time=current;
		q.push(make_pair(start, current));
/*
		for(it=graph.begin();it!=graph.end();++it){
			cout << it->first << "-";
			for(lit=it->second.second.begin();lit!=it->second.second.end();++lit){
				cout << lit->first << lit->second.first << lit->second.second;
			}
			cout << endl;

		}
*/
		printf("Scenario %d\n", T);
		
		while(!q.empty()){
			current_city=q.front().first;
			current_time=q.front().second;
			it=graph.find(current_city);	
			q.pop();
			
			for(lit=it->second.second.begin();lit!=it->second.second.end();++lit){
				if(lit->second.first >= current_time){
					gmap=graph_map.find(lit->first);
					if(gmap->second.second > lit->second.second){
						gmap->second.second=lit->second.second;
						
						q.push(make_pair(lit->first, lit->second.second));
					}
				}
			}
		}

		arrival=graph_map.find(end)->second.second;
		if(arrival==MAX_NUM){
			printf("No connection\n\n");
			continue;
		}
		q.push(make_pair(end, arrival));

		while(!q.empty()){
			current_city=q.front().first;
			current_time=q.front().second;
			it=graph.find(current_city);	
			q.pop();
			
			for(lit=it->second.first.begin();lit!=it->second.first.end();++lit){
				if(lit->second.second <= current_time){
					gmap=graph_map.find(lit->first);
					if(gmap->second.first < lit->second.first){
						gmap->second.first=lit->second.first;
						
						q.push(make_pair(lit->first, lit->second.first));
					}
				}
			}
		}
			
		departure=graph_map.find(start)->second.first;

		printf("Departure %.4d %s\n", (departure/60)*100+departure%60, start.c_str());
		printf("Arrival   %.4d %s\n", (arrival/60)*100+arrival%60, end.c_str());
		printf("\n");			
	
	}

	return 0;
}
