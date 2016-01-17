#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <list>

using namespace std;

class yahtzee{
public:
	yahtzee();
	void addNum(int, int, int, int, int);
	void print();
	void backtracking();
private:
	int a[13][13];// 각 경우별 합의 배열
	int chk[13]; // 각 경우의 사용유무
	int b[15];
	int tempchk[13]; // 백트랙킹시 사용될 임시 배열
	int subset[4];
	list<int> listNum[13]; // 각 경우별 사용 가능한 번호 저장
	int current;
	int maxsum;
	void backtracking(int); // 현재 순서
	int tempsum;
};

yahtzee::yahtzee(){
	
	for(int i=0;i<13;i++){
		chk[i]=-1;
		tempchk[i]=-1;
	}


	for(int i=0;i<13;i++){
		for(int j=0;j<13;j++){
			a[i][j]=0;
		}
	}

	current = -1;
	maxsum=-1;
	tempsum=0;
	//subset={50, 25, 35, 40};
	subset[0]=50; //9
	subset[1]=25; //10
	subset[2]=35; //11
	subset[3]=40; //12
}

void yahtzee::backtracking(){
/*	list<int>::iterator it;
	for(int i=0;i<13;i++){
		printf("%d(%ld) - " , i, listNum[i].size()+1);
		for(it=listNum[i].begin();it!=listNum[i].end();++it){
			printf("%d ", *it);
		}
		printf("\n");
	}
*/

	backtracking(0);
	//cout << maxsum << endl;
	for(int i=0;i<15;i++)
		printf("%d ", b[i]);

	printf("\n");
}

void yahtzee::backtracking(int tempnum){
	
	
	if(tempnum==13){

		if(tempsum>maxsum){
			maxsum=tempsum;
			for(int i=0;i<13;i++)
				if(tempchk[i]==-1)
					b[i]=0;
				else
					b[i]=a[tempchk[i]][i];

			int t_sum=0;
			for(int i=0;i<6;i++){
				if(tempchk[i]==-1) continue;
				t_sum+=a[tempchk[i]][i];
			}

			if(t_sum>=63)
				b[13]=35;
			else
				b[13]=0;

			b[14]=maxsum;
		}
/*			for(int i=0;i<15;i++)
				cout << b[i] << " ";
		
			cout <<  endl;
*/		
		return;
	}
	
	
	if(tempnum==6 && tempsum>=63) tempsum+=35;

	list<int>::iterator it;
	
	if(tempnum>=9){
		int subsum=0;
		for(int i=tempnum-9;i<4;i++)
			for(it=listNum[i+9].begin();it!=listNum[i+9].end();++it)
				if(chk[*it]==-1){
					subsum+=subset[i];
					break;
				}


		if(tempsum+subsum<=maxsum) return;
	}

	for(it=listNum[tempnum].begin();it!=listNum[tempnum].end();++it){

		if(chk[*it]==-1){
			chk[*it]=tempnum;
			tempchk[tempnum]=*it;
			tempsum+=a[*it][tempnum];

			backtracking(tempnum+1);
			
			tempsum-=a[*it][tempnum];
			chk[*it]=-1;
			tempchk[tempnum]=-1;

		}

	}

	backtracking(tempnum+1);

	if(tempnum==6 && tempsum>=63) tempsum-=35;

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
	int maxcount=-1;
	for(int i=0;i<6;i++){
		if(temp[i]>max) max=temp[i];	
		/*
			1. temp[i]!=0 -> 숫자가 있다.
			
			2. if current == -1  : 처음 시작
		*/
		if(temp[i]!=0)
			count++;
		else{
			if(count>maxcount) maxcount=count;
			count=0;
		}

	}
	if(count>maxcount) maxcount=count;
	if(maxcount==5){
		a[current][10]=25;
		a[current][11]=35;
	}else if(maxcount==4)
		a[current][10]=25;
	
	switch(max){
	case 3:
		for(int i=0;i<6;i++){
			if(temp[i]==2){
				a[current][12]=40;
				break;
			}
		}
		a[current][7]=a1+a2+a3+a4+a5;
		break;
	case 4:
		a[current][7]=a1+a2+a3+a4+a5;
		a[current][8]=a1+a2+a3+a4+a5;
		break;
	case 5:
		a[current][7]=a1+a2+a3+a4+a5;
		a[current][8]=a1+a2+a3+a4+a5;
		a[current][9]=50;
		break;
	}
	
	for(int i=0;i<13;i++)
		if(a[current][i]!=0)
			listNum[i].push_back(current);
	
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
			4. 비교 순위 - 점수가 높은 순위로.
			5. 중요한건 이것도 백트랙킹.
			6. 필요한 자료구조
			  1) 해당 값이 사용되었는지를 저장하는 배열 1~13
			  2) 각 순위별 사용 가능한 데이터가 들어있는 배열
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
		
		if(!status)break;

//		a.print();
		a.backtracking();
		
	}

	return 0;
}
