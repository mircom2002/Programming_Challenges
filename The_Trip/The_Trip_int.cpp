#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <math.h>

using namespace std;

int main(){

	// 1. 입력값 정렬
	// 2. 평균 값 구함(정수로)
	// 3. 소수점 맞춤( 평균, 평균, ... , 평균+소수점, 평균+소수점, ... )
	// 4. 평균 이상의 값에서 차례로 평균을 뺀 차를 더함

	int n;
	long long int avg;
	long long int sum;
	long long int div;

	while(1){

		scanf("%d", &n);
		
		if(n==0) return 0;

		
		int *a=new int[n];
		avg=0;
		sum=0;	
		div=0;		

		double d;

		for(int i=0;i<n;i++){
			scanf("%lf", &d);
			a[i]=(int)(d*100+0.5);
			sum+=a[i];
		}

		avg=sum/n;
		div=sum-avg*n;
		sort(a,  a+n, greater<int>());
		int temp=0;
		long long int result=0;
		
		for(int i=0;i<div;i+=1){
			if(a[temp]>avg+1) {
				result+=(a[temp]-(avg+1));
			}
			temp++;
		}
		while(a[temp]>avg){
			result+=(a[temp]-avg);
			temp++;
		}

		printf("$%.2lf\n", result/100.00);

		delete(a);

	}	

	return 0;
}




