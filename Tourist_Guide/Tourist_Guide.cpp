#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <list>
#include <set>
#include <queue>

using namespace std;

int main(){
	int n, m;
	int t=1;

	while(1){
		map<string, int> graph_map;
		map<string, list<string> > graph;
		set<string> save;

		map<string, int>::iterator gmap, temp;
		map<string, list<string> >::iterator it;
		list<string>::iterator lit;

		set<string>::iterator sit;

		scanf("%d", &n);

		if(n==0) return 0;
	
		string input;
		for(int i=0;i<n;i++){
			cin >> input;
			list<string> temp;
			graph_map.insert(make_pair(input, 0));
			graph.insert(make_pair(input, temp));
		}

		scanf("%d", &m);
	
		string v1, v2;
		for(int i=0;i<m;i++){
			cin >> v1 >> v2;
			graph.find(v1)->second.push_back(v2);
			graph.find(v2)->second.push_back(v1);
		}

		for(it=graph.begin();it!=graph.end();it++){
			
			if(it->second.size()==0){
				graph_map.find(it->first)->second=2;
			}
			
			/*
			printf("%s - ", it->first.c_str());
			for(lit=it->second.begin();lit!=it->second.end();lit++){
				printf("%s, ", (*lit).c_str());
			}
			printf("\n");
			*/
		}
	
		// bfs, 모든 노드의 개수 만큼 실행
		// -1 0 1 2 3 
		int chk;
		string start,  current;

		for(gmap=graph_map.begin();gmap!=graph_map.end();gmap++){
			
			if(gmap->second==2) continue;
			
			queue<string> q;
			q.push(gmap->first);
			graph_map.find(gmap->first)->second=3;
			
			while(!q.empty()){
				
				current=q.front();
				q.pop();

				for(lit=graph.find(current)->second.begin();lit!=graph.find(current)->second.end();++lit){

					temp=graph_map.find(*lit);
					if(temp->second==0){
						temp->second=3;
						q.push(*lit);
					}

				}
			}

			gmap->second=-1;

			for(temp=graph_map.begin();temp!=graph_map.end();temp++){
				if(temp==gmap) continue;
				if(temp->second==3){
			//	cout << temp->first <<  temp->second << endl;
					start=temp->first;
					break;
				}
			}

			q.push(start);
			graph_map.find(start)->second=1;
			
			while(!q.empty()){
				
				current=q.front();
				q.pop();

				for(lit=graph.find(current)->second.begin();lit!=graph.find(current)->second.end();++lit){

					temp=graph_map.find(*lit);
					if(temp->second==3){
						temp->second=1;
						q.push(*lit);
					}

				}
			}
			
			for(temp=graph_map.begin();temp!=graph_map.end();++temp){
				if(temp->second==2) continue;
				if(temp->second==3)	save.insert(gmap->first);
				temp->second=0;
				
			}

		}

		printf("City map #%d: %d camera(s) found\n", t, (int)save.size());
		
		for(sit=save.begin();sit!=save.end();sit++){		
			printf("%s\n", (*sit).c_str());
		}
		
		t++;
		printf("\n");

	}


	return 0;
}
