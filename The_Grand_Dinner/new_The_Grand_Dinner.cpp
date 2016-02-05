#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
#include <list>

using namespace std;

struct node{
	node(int v, int n):value(v), num(n){};
	int value;
	int num;
};

class op{
public:
	bool operator()(node& t1, node& t2){
		if(t1.value < t2.value) return true;
		return false;
	}

};


int main(){

	while(1){
		int m_num, t_num;
		scanf("%d %d", &m_num, &t_num);

		if(!m_num && !t_num) break;

		int temp;
		
		priority_queue<node, vector<node>, op> pq, temp_pq, m_pq;

		for(int i=0;i<m_num;i++){
			scanf("%d", &temp);
			node n(temp, i+1);
			m_pq.push(n);

		}

		for(int i=1;i<=t_num;i++){
			scanf("%d", &temp);
			node n(temp, i);
			pq.push(n); 
		}

		int chk=1;
		int temp_value, temp_num, current_num, current_m;
		list<int> result[71];
		list<int>::iterator lit;

		for(int i=0;i<m_num;i++){
			
			current_num=m_pq.top().value;
			current_m=m_pq.top().num;
			m_pq.pop();

			//printf("current : %d(%d)\n", m_arr[i], (int)pq.size());
			if(current_num>pq.size()){
				chk=0;
				break;
			}
			// current_m = 팀 번호
			// temp_num = 테이블 번호
			for(int j=0;j<current_num;j++){
				temp_value=pq.top().value;
				temp_num=pq.top().num;
				pq.pop();
				temp_value--;

				result[current_m].push_back(temp_num);
		
			//	printf("%d %d\n", temp_value, temp_num);

				if(temp_value==0) continue;
				node n(temp_value, temp_num);
				temp_pq.push(n);
			}
			
			while(!temp_pq.empty()){
				node n(temp_pq.top().value, temp_pq.top().num);
				pq.push(n);
				temp_pq.pop();
			}

		}

		printf("%d\n", chk);
		if(!chk) continue;

		for(int i=1;i<=m_num;i++){
			for(lit=result[i].begin();lit!=result[i].end();++lit){
				printf("%d ", *lit);
			}
			printf("\n");
		}

		//cout <<"AF"<< endl;

	}

	return 0;
}
