#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
	
	int n, s;
	//n==1 인 경우
	// 0	
	//0 0	
	// 0 
	//0 0
	// 0

	/*
		LCD 배열
		상단 - : 0, 2, 3, 5, 6, 7, 8, 9
		상단 1 | : 0, 4, 5, 6, 8, 9
		상단 2 | : 0, 1, 2, 3, 4, 7, 8, 9
		중단 - : 2, 3, 4, 5, 6, 8, 9
		하단 1 | : 0, 2, 6, 8
		하단 2 | : 0, 1, 3, 4, 5, 6, 7, 8, 9
		하단 _ : 0, 2, 3, 5, 6, 8, 9

		1. s를 입력 받고, s의 최대 길이는 8까지이다.
		2. 배열을 만들고, 각 배열에는 s의 자릿값이 순서대로 들어간다.
		3. 위의 LCD 배열을 이용, lcd[a[0~9]][상단~하단] = 1 이면 n의 개수만큼 - 또는 |를 출력한다.
	*/
	int lcd[7][10]={{1, 0, 1, 1, 0, 1, 1, 1, 1, 1}, //상단 -
					{1, 0, 0, 0, 1, 1, 1, 0, 1, 1}, //상단 1 |
					{1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, //상단 2 |
					{0, 0, 1, 1, 1, 1, 1, 0, 1, 1}, //중단
					{1, 0, 1, 0, 0, 0, 1, 0, 1, 0}, //하단 1 |
					{1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, //하단 2 |
					{1, 0, 1, 1, 0, 1, 1, 0, 1, 1}}; //하단 -
	

	int a[8]={0};

	while(1){

		
		scanf("%d %d", &n, &s);

		if(!n && !s) return 0;
		int current=7;
		// s 분해
		while(current>=0){
			if(s==0 && current<7)
				a[current]=-1;
			else
				a[current]=s%10;

			//printf("%d", a[current]);
			s/=10;
			current--;
		}

		// 출력
		for(int i=0;i<5;i++){// 상단 중단 하단

			if(i==0 || i==2 || i==4){ // '-'
				for(int j=0;j<8;j++){
					if(a[j]==-1) continue;
					printf(" ");
					if(lcd[i*3/2][a[j]]==1) // 출력
						for(int k=0;k<n;k++)
							printf("-");
					else
						for(int k=0;k<n;k++)
							printf(" ");
					printf("  ");
				}
				printf("\n");

			}else{ // '|'
			//1 3 -> 1 4
				for(int k=0;k<n;k++){
					for(int j=0;j<8;j++){

						if(a[j]==-1) continue;
						
						if(lcd[i*4/3][a[j]]==1)
							printf("|");
						else
							printf(" ");
					
					
						for(int l=0;l<n;l++)
							printf(" ");

						if(lcd[i*4/3+1][a[j]]==1)
							printf("|");
						else
							printf(" ");

						printf(" ");
					}
					printf("\n");
				}
			}

		}



	}

	return 0;
}
