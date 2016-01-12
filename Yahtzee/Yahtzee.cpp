#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

class yahtzee{
public:
	yahtzee();
	void addNum(int, int, int, int, int);
	void print();
private:
	int a[13][13];// 각 경우별 합의 배열
	int current;
};

yahtzee::yahtzee(){

	for(int i=0;i<13;i++){
		for(int j=0;j<15;j++){
			a[i][j]=0;
		}
	}
	current = -1;
}

void yahtzee::addNum(int a1, int a2, int a3, int a4, int a5){
	current+=1;
	//cout << current << " "; 
	a[current][a1-1]+=a1;
	a[current][a2-1]+=a2;
	a[current][a3-1]+=a3;
	a[current][a4-1]+=a4;
	a[current][a5-1]+=a5;
	
	a[current][6]=a1+a2+a3+a4+a5;

	int temp[6]={0};
	temp[a1-1]++;
	temp[a2-1]++;
	temp[a3-1]++;
	temp[a4-1]++;
	temp[a5-1]++;

	int max=-1;
	int count=0;
	for(int i=0;i<6;i++){
		if(temp[i]>max) max=temp[i];	
		if(temp[i]>0)
			count++;
		else
			if(count==4)
				a[current][10]=25;
			else if(count==5){
				a[current][10]=25;
				a[current][11]=35;
			}else
				count=0;
	}
	
	switch(max){
	case 3:
		for(int i=0;i<5;i++){
			if(temp[i]==2){
				a[current][12]=40;
				break;
			}
		}
		if(!a[current][12])
			a[current][7]=a1+a2+a3+a4+a5;
		break;
	case 4:
		a[current][8]=a1+a2+a3+a4+a5;
		break;
	case 5:
		a[current][7]=a1+a2+a3+a4+a5;
		a[current][8]=a1+a2+a3+a4+a5;
		a[current][9]=50;
		break;
	}

	
}

void yahtzee::print(){
	for(int i=0;i<13;i++){
		for(int j=0;j<13;j++){
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}

}

int main(){
	string input;
	while(1){
		/*
			1. 입력을 받는다.
			2. 각 입력 별 13개의 경우의 값을 구한다.
			3. 비교 방법 = 각 경우중 가장 큰 값, 같으면 그 중 전체 경우의 합이 작은 것
			4. 비교 순위
				1순위 : 같은 숫자 다섯개
				2순위 : 풀하우스
				3순위 : 롱 스트레이트 & 보너스점수
		*/
		int a1, a2, a3, a4, a5;
		int status=1;//0=종료, 1=실행
		yahtzee a;
		for(int i=0;i<13;i++){
			getline(cin, input);
			if(sscanf(input.c_str(), "%d %d %d %d %d", &a1, &a2, &a3, &a4, &a5)<1){
				status=0;
				break;
			}
			a.addNum(a1, a2, a3, a4, a5);
		}
		
		a.print();

		if(!status)break;

		
	}

	return 0;
}
