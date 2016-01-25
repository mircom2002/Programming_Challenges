#include <iostream>
#include <stdio.h>

using namespace std;

int main(){

	int testCase;
	scanf("%d", &testCase);
	int a[100]={0, 1, 3, 0};
	int i, current=3;
	for(;testCase>0;testCase--){
		
		int n;
		scanf("%d", &n);
		if(a[n]!=0){
			printf("%d\n", a[n]);
			continue;
		}
		for(i=current;i<=n;i++){
			/*	
				2개일때 2개 더하고
				3개일때 4개 더하고
				4개일때 4개 더하고
				5개일때 6개 더하고
			*/
			a[i]=a[i-1]+((i+1)/2)*2;
		}
		current=i;
		printf("%d\n", a[n]);
	}


}
