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

map<string, list<pair<string, pair<int, int> > > >::iterator it;
map<string, pair<int, int> >::iterator gmap;
list<pair<string, pair<int, int> > >::iterator lit, lit2;

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

	int testCase;
	scanf("%d", &testCase);

	for(int T=1;T<=testCase;T++){
	
		map<string, list<pair<string, pair<int, int> > > > graph; // 출발 지역, list(도착지역, (출발시간, 도착시간))
		map<string, pair<int, int> > graph_map; // 해당 지역의 출발시간 / 도착시간
		
		int num, num2;
		scanf("%d", &num);

		string input;
		for(int i=0;i<num;i++){
			list<pair<string, pair<int, int> > > temp;
			cin >> input;
			graph_map.insert(make_pair(input, make_pair(MAX_NUM, MAX_NUM)));
			graph.insert(make_pair(input, temp));
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
				pq.pop();
				if(k>0)
					graph.find(name[k-1])->second.push_back(make_pair(name[k], make_pair(time[k-1], time[k])));
				k++;
			}

		}

		int current;
		string start, end;

		scanf("%d", &current);
		cin >> start;
		cin >> end;
/*
		if(start==end){
			printf("Scenario %d\n", T);
			printf("Departure %.4d %s\n", current, start.c_str());
			printf("Arrival   %.4d %s\n", current, end.c_str());
			printf("\n");
			continue;
		}
*/

		// 출발역에서 도착역 까지 경로 BFS로 확인
		// 가장 빨리 도착, 가장 적은 시간에 도착

		current=(current/100)*60+(current%100);
		queue<pair<string, int > > q; // 현재위치, 현재시간

		int current_time;
		string current_city;
		int departure=MAX_NUM;
		int arrival=MAX_NUM;

		if(graph.find(start)==graph.end() || graph.find(end)==graph.end() || start==end){
			printf("Scenario %d\n", T);
			printf("No connection\n");
			printf("\n");
			continue;
		}


		for(lit2=graph.find(start)->second.begin();lit2!=graph.find(start)->second.end();++lit2){
			/*
			*/
			/*for(gmap=graph_map.begin();gmap!=graph_map.end();++gmap){
				gmap->second.first=MAX_NUM;
				gmap->second.second=MAX_NUM;
			}*/

			gmap=graph_map.find(lit2->first); 
			// gmap = 해당 위치 까지오는데 출발한 시간과, 도착한 시간이 들어감
			// gmap->first - 역
			// gmap->second.first = 처음 역에서 출발한 시간
			// gmap->second.second = 역까지 도착시간

			//printf("%s %d %d %d\n",lit2->first.c_str(), gmap->second.first, lit2->second.first, current);

			if(lit2->second.first<current) continue; 
			//if(gmap->second.first > lit2->second.first && gmap->second.first!=MAX_NUM)	continue;
			// lit2 -> start에서 열차를 타고 이동한 위치가 들어감
			// lit2 -> first = 이동된 위치
			// lit2 -> second.first = 이동된 위치로 오는 열차의 출발시간
			// lit2 -> second.second = 이동된 위치로 오는 열차의 도착시간
/*
			if(gmap->second.second < lit2->second.second
				&& gmap->second.first > lit2->second.first) continue;
			
			if(gmap->second.second==lit2->second.second && gmap->second.first > lit2->second.first) continue;
*/

		//printf("%s(%d) - %s(%d)\n", start.c_str(), lit2->second.first, lit2->first.c_str(), lit2->second.second);

			gmap->second.first=lit2->second.first;
			gmap->second.second=lit2->second.second;

			q.push(make_pair(lit2->first, lit2->second.second));
			// q - 현재 역, 현재 시간

			while(!q.empty()){

				current_city=q.front().first;
				current_time=q.front().second;

				q.pop();

				if(end==current_city){
					gmap=graph_map.find(end);
					printf("%d - %d\n", gmap->second.first, gmap->second.second);
					if(arrival>gmap->second.second){
						departure=gmap->second.first;
						arrival=gmap->second.second;
					}else if(arrival==gmap->second.second 
							&& departure < gmap->second.first){
						departure=gmap->second.first;
						arrival=gmap->second.second;
					}
				continue;
				}

				it=graph.find(current_city);
				
				for(lit=it->second.begin();lit!=it->second.end();++lit){
				 	// lit - 현재 역에서 이동 할수 있는 역들의 리스트
					// lit->first : 다음 역
					// lit->second.first : 다음 역으로의 출발시간
					// lit->second.second : 다음 역으로의 도착시간
					if(lit->second.first>=current_time){
		//				printf("%s(%d) - %s(%d)\n", current_city.c_str(), current_time, lit->first.c_str(), lit->second.second);
						gmap=graph_map.find(lit->first); // 다음 역의 도착 정보가 있을 경우
						if(gmap->second.second < lit->second.second && gmap->second.first > lit2->second.first) continue;
						gmap->second.second=lit->second.second;
						gmap->second.first=lit2->second.first;
						// 정보 갱신
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
