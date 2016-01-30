#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#define MAX_NUM 999999999


using namespace std;

int main(){
	/*
		how to?

		1. 기존에 존재하던 소방서로 부터 가장 거리가 먼 집을 구함.

		전체 교차로의 개수 n, 기존 소방서 개수 m 일때
		
		플로이드 배열 존재시 O(n^3)
		
		기존 최단거리O(n*m)에서 새로운 최단 거리를 구하는데 O(n^2)

		총 수행시간 n^3

	*/
	int testCase;
	scanf("%d", &testCase);
	for(;testCase>0;testCase--){

		int existNum, roadNum;
		scanf("%d %d", &existNum, &roadNum);
		vector<int> existStation;
		int temp;
		int c[501]={0};
		for(int i=0;i<existNum;i++){
			scanf("%d", &temp);
			existStation.push_back(temp);
			c[existStation[i]]=1;
		}

		int **a=new int*[roadNum+1];
		for(int i=1;i<=roadNum;i++){
			a[i]=new int[roadNum+1];
			for(int j=1;j<=roadNum;j++)	a[i][j]=MAX_NUM;
		}
	
		getchar();
		int v1, v2;
		string input;
		while(1){
			getline(cin, input);
			if(input.size()<1) break;
			sscanf(input.c_str(), "%d %d %d", &v1, &v2, &temp);
			a[v1][v2]=temp;
			a[v2][v1]=temp;
		}

		int size=existStation.size();
		for(int i=0;i<size;i++){
			a[existStation[i]][existStation[i]]=0;
		}

		for(int k=1;k<=roadNum;k++){
			for(int i=1;i<=roadNum;i++){
				for(int j=1;j<=roadNum;j++){
					if(a[i][j]>a[i][k]+a[k][j])
						a[i][j]=a[i][k]+a[k][j];
				}
			}
		}

		// 기존 최단 거리
		int *b=new int[roadNum+1];
		for(int i=1;i<=roadNum;i++){
			b[i]=MAX_NUM;
			for(int j=0;j<size;j++){
				if(b[i]>a[existStation[j]][i])
					b[i]=a[existStation[j]][i];
			}
		}

		// 새로운 최단 거리에 소방서가 지어졌을때 최단거리
		// b[i] : 기존 소방서에서의 최단 거리
		// a[i][j] : i 에서 j 까지 거리

		int min=MAX_NUM;
		int max;
		int newStation=1;//existStation.front();
		for(int i=1;i<=roadNum;i++){// i 새로 지은 소방서의 위치
			//if(c[i]) continue;
			max=-1;
			for(int j=1;j<=roadNum;j++){ // 새로 지은 소방서와 기존 소방서 위치 비교
				if(i==j) continue;
				if(a[j][i]<b[j]){
					if(a[j][i]>max){
						temp=j;
						max=a[j][i];
					}
				}else{
					if(b[j]>max){
						temp=j;
						max=b[j];
					}
				}
			}

			if(min>max){
				min=max;
				newStation=i;
			}



		}

		printf("%d\n\n", newStation);
/*
		for(int i=1;i<=roadNum;i++){
			for(int j=1;j<=roadNum;j++){
				cout << a[i][j] << "\t";
			}
			cout << endl;
		}
		cout << "기존 최단 거리" << endl;
		for(int i=1;i<=roadNum;i++){
			cout << b[i] << endl;
		}
*/
	}
	return 0;
}	
