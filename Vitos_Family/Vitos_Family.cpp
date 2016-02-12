#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#define MAX_NUM 199999999

using namespace std;

int main(){
	
	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){

		int num, temp;
		vector<int> v;
		scanf("%d", &num);
		for(int i=0;i<num;i++){
			scanf("%d", &temp);
			v.push_back(temp);
		}

		sort(v.begin(), v.end());

		int center[3]={num/2-1, num/2, num/2+1};
		int sum, min=MAX_NUM;
		for(int i=0;i<3;i++){
			if(center[i]<0 || center[i]>num) continue;
			sum=0;
			for(int j=0;j<num;j++){
				sum+=abs(v[j]-v[center[i]]);
			}
			if(sum<min) min=sum;
		}

		printf("%d\n", min);
	
	}
	return 0;
}
