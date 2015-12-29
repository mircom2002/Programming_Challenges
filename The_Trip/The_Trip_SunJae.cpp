#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(){

	while(1){
		int n;
		scanf("%d", &n);
		if(n==0) break;

		double sum=0.0;
		double avg=0.0;
		double div=0.0;
		double temp;
	
		double *a=new double[n];
		
		for(int i=0;i<n;i++){
			scanf("%lf", &a[i]);
			sum+=a[i];
		}

		avg=sum/n;
		div=floor((avg+0.005)*100)/100;
		if(div<0.0001) div=0.00;

		double result=0.0;

		for(int i=0;i<n;i++){
			if(a[i]>div) result+=(a[i]-div);
		}
		
		if(result<=0.011)
			printf("$0.00\n");
		else
			printf("$%.2lf\n", result);

	}

	return 0;
}
