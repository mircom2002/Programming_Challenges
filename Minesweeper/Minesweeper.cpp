#include <stdio.h>
#include <iostream>

using namespace std;

int main(){

	int n,m; // n=줄의 개수, m=한 줄에서 문자의 개수
	int T=0;
	
	while(1){
		scanf("%d %d", &n, &m);
		if(n==0 && m==0) {
			break;
		}
		T++;
	
		int a[102][102]={0};
	
		char s[100];

		for(int i=1;i<n+1;i++){
			scanf("%s", s);
			for(int j=1;j<m+1;j++){
				if(s[j-1]=='*'){
					a[i][j]=-1000;
					a[i-1][j-1]++;
					a[i-1][j]++;
					a[i-1][j+1]++;
					a[i][j-1]++;
					a[i][j+1]++;
					a[i+1][j-1]++;
					a[i+1][j]++;
					a[i+1][j+1]++;		
				}	
			}

		}

		printf("\nField #%d:\n", T);	
		
		for(int i=1;i<n+1;i++){
			for(int j=1;j<m+1;j++){
				if(a[i][j]<0)
					printf("*");
				else
					printf("%d", a[i][j]);
			}
			printf("\n");
		}	

	}
	return 0;
}
