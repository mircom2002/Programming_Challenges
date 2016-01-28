#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>

#define MAX_NUM 99999999

using namespace std;

int main(){

	/*
		1. 구현 방법 - 최소 신장 트리를 구한다.

		2. 입력 - x, y 좌표 

		3. 배열에 구성

	*/


	int testCase;
	scanf("%d", &testCase);

	for(;testCase>0;testCase--){
		int n;
		scanf("%d", &n);
		if(n==0) {
			printf("0.00\n\n");
			continue;
		}
		
		double weight[101][101];
		int check[101]={0};
		pair<double, double> coord[101];

		double x, y;
		for(int i=0;i<n;i++){
			scanf("%lf %lf", &x, &y);
			check[i]=MAX_NUM;
			coord[i]=make_pair(x, y);
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				weight[i][j]=sqrt(pow((coord[i].first-coord[j].first),2)+pow((coord[i].second-coord[j].second),2));
			}
		}
		
		double sum=0;
		int current=0;
		int v=0;
		list<int> tree;
		tree.push_back(current);
		list<int>::iterator it;
		
		while(tree.size()!=n){

			double dist=MAX_NUM;
			check[current]=0;

			for(it=tree.begin();it!=tree.end();++it){
				current=*it;
				for(int i=0;i<n;i++){
					if(i==current) continue;

					if(dist>weight[current][i] && check[i]==MAX_NUM){
						v=i;
						dist=weight[current][i];
					}
				}
			}

			check[v]=0;
			tree.push_back(v);
			sum+=dist;
			current=v;

		}

		printf("%0.2lf\n\n", sum);

	}
	return 0;
}
