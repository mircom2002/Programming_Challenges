#include <iostream>
#include <stdio.h>
#include <stack>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

bool op(int i, int j){return i>j;}

int main(){

	while(1){
		int temp, num=0;
		list<int> v, origin;
		priority_queue<int> pq;
		do{
			if(scanf("%d", &temp)!=1) return 0;
			v.push_back(temp);
			pq.push(temp);
			origin.push_back(temp);
			num++;
		}while(getc(stdin)==' ');
		
		// pq로 최대 값 구함
		// v에서 최대값 위치 구함
		// 최대값을 맨 위로 올림
		// 최대값을 필요한 위치로 이동시킴

		int count;
		list<int> result;
		list<int>::iterator it;
		for(int i=1;i<=num;i++){
			temp=pq.top();
			pq.pop();
			count=0;
			queue<int> q;
			it=v.begin();

			for(int j=0;j<num-i;j++, it++);
			
			if(*it==temp) continue;

			if(v.front()!=temp){
				while(v.front()!=temp){
					q.push(v.front());
					v.pop_front();
					count++;
				}
			
				q.push(v.front());
				v.pop_front();

				while(!q.empty()){
					v.push_front(q.front());
					q.pop();
				}
				result.push_back(num-count);
			}

			while(i <= v.size()){
				q.push(v.front());
				v.pop_front();	
			}

			while(!q.empty()){
				v.push_front(q.front());
				q.pop();
			}

			result.push_back(i);
		}

		result.push_back(0);

		for(it=origin.begin();it!=origin.end();it++) 
			printf("%d ", *it);

		printf("\n");
		for(it=result.begin();it!=result.end();it++)
			printf("%d ", *it);
		printf("\n");
	}


	return 0;
}
