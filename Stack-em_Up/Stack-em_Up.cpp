#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

string tile[4]={"Clubs", "Diamonds", "Hearts", "Spades"};

void printCard(int n){
	int t=(n-1)/13;
	switch(n%13){
	case 0:
		printf("Ace ");
		break;
	case 10:
		printf("Jack ");
		break;
	case 11:
		printf("Queen ");
		break;
	case 12:
		printf("King ");
		break;
	default:
		printf("%d ", n%13+1);
		break;
	}

	printf("of ");
	cout << tile[t] << endl;
}

int main(){
	int T;
	scanf("%d", &T);

	for(;T>0;T--){
		int n;
		scanf("%d", &n);

		int **a=new int*[n];
		int deck[53];
		
		for(int i=1;i<=52;i++){
			deck[i]=i;
		}

		for(int i=0;i<n;i++){
			a[i]=new int[53];
			int temp;
			for(int j=1;j<=52;j++){
				scanf("%d", &a[i][j]);
			}
		}
		string input;
		getchar();
		while(1){
			getline(cin, input);	
			if(input.size()<1) break;
			int shuffle=atoi(input.c_str())-1;
			int temp[53]={0};
			for(int i=1;i<=52;i++){
				temp[i]=deck[a[shuffle][i]];
			}

			for(int i=1;i<=52;i++){
				deck[i]=temp[i];
			}
			//cout << shuffle << endl;
		}

		for(int i=1;i<=52;i++){
			printCard(deck[i]);
		}
		cout << endl;
		delete(a);
	}
	return 0;
}
