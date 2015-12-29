#include <stdio.h>
#include <iostream>

using namespace std;

void swap(int *a, int *b){
	int c=*a;
	*a=*b;
	*b=c;
}

int _3n1(int n){
	
	int count=1;

	while(n!=1){
		count++;
		if(n%2==0){
			n/=2;
		}else{
			n*=3;
			n++;
		}
	}

	return count;
}


int main(){
	
	int i,j;
	int temp;
	int max;

	while(scanf("%d %d", &i, &j)==2){;
	max=-1;
	printf("%d %d ", i, j);

	if(i>j) swap(&i, &j);
	
	for(;i<=j;i++){
		temp=_3n1(i);
		if(temp>max) max=temp;		

	}	
	
	printf("%d\n", max);
	}

	return 0;
}


