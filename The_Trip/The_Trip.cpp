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
	float avg;
	float sum;
	float div;

	while(1){

		scanf("%d", &n);
		
		if(n==0) break;
		
		float *a=new float[n];
		avg=0.00;
		sum=0.00;	
		div=0.00;		

		for(int i=0;i<n;i++){
			scanf("%f", &a[i]);
			sum+=a[i];
		}

		avg=floor(sum/n*100)/100;
		div=sum-avg*n;
		if(div<0.001) div=0.00;

		sort(a,  a+n, greater<float>());
		int temp=0;
		float result=0.00;
		
		for(float i=0.001;i<div;i+=0.01){
			if(a[temp]>avg+0.01) {
				result+=(a[temp]-(avg+0.01));
			}else{
				temp++;
				break;
			}
			temp++;
		}
		while(a[temp]>avg){
			result+=(a[temp]-avg);
			temp++;
		}
		printf("$%.2f\n", result);

		delete(a);

	}	

	return 0;
}




