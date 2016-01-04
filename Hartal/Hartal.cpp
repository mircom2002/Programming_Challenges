#include <iostream>
#include <stdio.h>

using namespace std;

int main(){

	int T;
	scanf("%d", &T);
	for(;T>0;T--){
		int day;
		scanf("%d", &day);
	
		int *a=new int[day+1];
		for(int i=1;i<=day;i++){
			a[i]=0;
		}

		int hnum;
		scanf("%d", &hnum);

		for(;hnum>0;hnum--){
			int i;
			scanf("%d", &i);
			if(i>day) continue;
			for(int k=i;k<=day;k+=i){
				if(k%7==6 || k%7==0 || k>day) continue;
				a[k]++;
		//		cout << k;
			}
		//	cout << endl;
		}

		int count=0;
		for(int i=1;i<=day;i++){
			if(a[i]>0) count++;
		}

		printf("%d\n", count);
		delete(a);
	}
	return 0;
}
