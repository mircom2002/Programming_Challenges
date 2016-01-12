#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
	int a[10];
	int b[]={5, 7, 4, 2, 6, 9, 8, 1, 3, 0};
	int i=0;
	for (int n:b){
		a[i]=n;
		i++;
	}
	Byte q=1;
	for(i=0;i<10;i++)
		cout << a[i] << endl;

	return 0;
}
