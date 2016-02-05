#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int bfs(vector<list<int> > &st, int** m, int start, int end){

	int a[121]={0};
	
	list<pair<int, int> > temp[121];
	
	list<int>::iterator it;
	list<pair<int, int> >::iterator lit;

	queue<pair<int, int> > q;
	q.push(make_pair(start, 0));
	temp[0].push_back(make_pair(0, start));
	a[start]=1;

	int current, count, chk=1;

	while(chk && !q.empty()){
		current=q.front().first;
		count=q.front().second+1;
		q.pop();

		for(it=st[current].begin();it!=st[current].end();++it){
			if(m[current][*it]>0 && a[*it]==0){
				temp[count].push_back(make_pair(current, *it));
				a[*it]=1;
				if(*it==end){
					chk=0;
					current=*it;
					break;
				}
				q.push(make_pair(*it, count+1));
			}

		}
	}

	if(chk) return -1;

	int rv;

	for(int i=count;i>=0;i--){
		for(lit=temp[i].begin();lit!=temp[i].end();++lit){
			if(current==lit->second){
				m[lit->first][lit->second]--;
				m[lit->second][lit->first]++;
				if(i==1){
					rv=lit->second;
				}
				current=lit->first;
				break;
			}
		}
	}

	return rv;

}



int main(){
	/*
		필요한 자료구조
		1. 배열(흐름과 용량을 저장)
		2. 벡터<리스트> 현재 번호와 연결된 다음 노드를 확인
	*/

	while(1){
		int s_num, t_num;
		scanf("%d %d", &s_num, &t_num);

		if(!s_num && !t_num) return 0;

		int start=0, end=s_num+t_num+2;
		int**a=new int*[end];
		vector<list<int> > st_graph;
		list<int>::iterator lit;

		for(int i=0;i<end;i++){
			list<int> temp;
			st_graph.push_back(temp);
			a[i]=new int[end];
			for(int j=0;j<end;j++)
				a[i][j]=0;
		}
		
		for(int i=1;i<=s_num;i++){
			scanf("%d", &a[0][i]);
			st_graph[0].push_back(i);
			st_graph[i].push_back(0);
			for(int j=1;j<=t_num;j++){
				a[i][j+s_num]=1;
				st_graph[i].push_back(j+s_num);
				st_graph[j+s_num].push_back(i);
			}
		}

		for(int i=1;i<=t_num;i++){
			scanf("%d", &a[i+s_num][end-1]);
			st_graph[i+s_num].push_back(end-1);
			st_graph[end-1].push_back(i+s_num);
		}
/*
		for(int i=0;i<end;i++){
			for(lit=st_graph[i].begin();lit!=st_graph[i].end();++lit){
				printf("%d(%d)%d, ", i, a[i][*lit], *lit);
			}
			printf("\n");
		}
*/
		// i -> *lit, a[i][*lit]
		// 각 출발에 대한 BFS 사용

		int num, chk=1;

		for(int i=1;i<=s_num;i++){
			num=a[0][i];
			chk=1;
			for(int j=0;j<num;j++){
				if(bfs(st_graph, a, i, end-1)==-1){
					chk=0;
					break;
				}
			}
			if(!chk) break;
		}
		
		printf("%d\n", chk);
		if(!chk) continue;

/*
		for(int i=0;i<end;i++){
			for(lit=st_graph[i].begin();lit!=st_graph[i].end();++lit){
				printf("%d(%d)%d, ", i, a[i][*lit], *lit);
			}
			printf("\n");
		}
*/

		list<int> resultset[71];

		for(int i=1;i<=t_num;i++){
			num=a[end-1][s_num+i];
			for(int j=0;j<num;j++){
			//	printf("%d %d\n", i+t_num, bfs(st_graph, a, i+t_num, start));
				resultset[bfs(st_graph, a, i+s_num, start)].push_back(i);
			}

		}
		for(int i=1;i<=s_num;i++){
			for(lit=resultset[i].begin();lit!=resultset[i].end();++lit){
				printf("%d ", *lit);
			}
			printf("\n");
		}
/*
		for(int i=0;i<end;i++){
			for(lit=st_graph[i].begin();lit!=st_graph[i].end();++lit){
				printf("%d(%d)%d, ", i, a[i][*lit], *lit);
			}
			printf("\n");
		}
*/	}


	return 0;
}
