#include <ctime>
#include <iostream>
#include <stdio.h>
#include <list>
#include <stdlib.h>

using namespace std;

int main(){
	srand((unsigned int)time(NULL));
	int k, n, m;
	scanf("%d %d %d",&k, &n, &m);
	cout << k << endl;//testCase

	for(int testCase=1;testCase<=k;testCase++){
		cout << endl;
		cout << n << endl;
		for(int i=0;i<n;i++)
			cout << "a"<<i+1 << endl;
		


		for(int i=0;i<m;i++){
			int *a=new int[n];
			for(int j=0;j<n;j++) a[j]=j;
			
			int tempm=n;

			for(int j=n;j>0;j--){
				int temp=rand()%j;
	
				cout << a[temp]+1 << " ";
				tempm--;
				for(;temp<tempm;temp++){
					a[temp]=a[temp+1];
				}

			}
			cout << endl;
			delete(a);
		}
	}
}
