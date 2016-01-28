#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

using namespace std;

vector<pair<int, int* > > chkneck;


void print(vector<list<pair<int, int> > > neck, int current, int start, int size){
	
	list<pair<int, int> >::iterator it;
	
	while(neck[current].front().first!=start){
		neck[current].push_back(neck[current].front());
		neck[current].pop_front();
	}

	for(it=neck[current].begin();it!=neck[current].end();++it){
		printf("%d %d\n", it->first, it->second);
			
		for(int k=0;k<size;k++){
			if(chkneck[k].first && chkneck[k].second[it->second]){
				chkneck[k].first=0;
				print(neck, k, it->second, size);
			}
		}

	}
}


int main(){
	/*
		해결 방법 - 오일러 사이클을 구한다

		오일러 사이클의 조건 - 모든 정점의 차수가 짝수여야 한다.

		1. 입력 testCase, 구슬의 개수

		2. 배열로 유지

		2-1. 이때 홀수 값이 나오면 아웃

		3. dfs로 값을 구함
	*/
	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){
		int n;
		scanf("%d", &n);
		
		int a[51][51]={0};
		int bub[51]={0};
		int t1, t2;

		for(int i=0;i<n;i++){
			scanf("%d %d", &t1, &t2);
			a[t1][t2]++;
			a[t2][t1]++;
			bub[t1]++;
			bub[t2]++;
		}

		bool chk=false;

		for(int i=1;i<=50;i++){
			if(bub[i]%2==1) chk=true;
		}

		printf("Case #%d\n", T+1);
		if(n==0){
			printf("\n");
			continue;
		}
		if(chk) {
			printf("some beads may be lost\n\n");
			continue;
		}

		chkneck.clear();
		vector<list<pair<int, int> > > neck;
		int current;
		for(int i=1;i<=50;){
			if(bub[i]>0){
				current=i;
				list<pair<int, int> > temp;
				chk=true;
				int *tempArray=new int[51];
				for(int j=1;j<=50;j++) tempArray[j]=0;
				while(chk){
					chk=false;
					for(int j=1;j<=50;j++){
						if(a[current][j]>0){
							temp.push_back(make_pair(current, j));
							a[current][j]--;
							a[j][current]--;
							tempArray[current]=1;
							bub[current]--;
							bub[j]--;
							current=j;
							chk=true;
							break;
						}
					}
				}
				neck.push_back(temp);
				chkneck.push_back(make_pair(1, tempArray));
				continue;
			}

			i++;
		}

		int size=chkneck.size();
		list<pair<int, int> >::iterator lit;

//		for(int i=0;i<size;i++){
		chkneck.front().first=0;
		for(lit=neck.front().begin();lit!=neck.front().end();++lit){
			printf("%d %d\n", lit->first, lit->second);
			for(int k=0;k<size;k++){
				if(chkneck[k].first && chkneck[k].second[lit->second]){
					chkneck[k].first=0;
					print(neck, k, lit->second, size);
				}
			}
		}
		printf("\n");
//		}


	}
	return 0;
}
