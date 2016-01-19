#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>


using namespace std;

int* upper(int temp){

	int *t=new int[4];

	int a1, a2, a3, a4;
	a1=temp/1000;
	a2=(temp%1000)/100;
	a3=(temp%100)/10;
	a4=temp%10;

	t[0]=((a1+1)%10)*1000+temp%1000;
	t[1]=a1*1000+((a2+1)%10)*100+temp%100;
	t[2]=a1*1000+a2*100+((a3+1)%10)*10+a4;
	t[3]=(temp/10)*10+((a4+1)%10);


	return t;

}

int *lower(int temp){
		
	int *t=new int[4];

	int a1, a2, a3, a4;
	a1=temp/1000;
	a2=(temp%1000)/100;
	a3=(temp%100)/10;
	a4=temp%10;

	t[0]=((a1+9)%10)*1000+temp%1000;
	t[1]=a1*1000+((a2+9)%10)*100+temp%100;
	t[2]=a1*1000+a2*100+((a3+9)%10)*10+a4;
	t[3]=(temp/10)*10+((a4+9)%10);

	return t;
}



void bfs(int *a, int start, int end){

	a[start]=0;
	queue<int> q;
	q.push(start);

	while(!q.empty()){

		int current=q.front();
		if(current==end) return;
		int currentnum=a[current]+1;
		q.pop();
		int *t=upper(current);
		int *l=lower(current);
		
		for(int i=0;i<4;i++){
			
			if(a[t[i]]==0){
				q.push(t[i]);
				a[t[i]]=currentnum;
				if(t[i]==end) return;
			}

			if(a[l[i]]==0){
				q.push(l[i]);
				a[l[i]]=currentnum;
				if(l[i]==end) return;

			}

		}

	}


}


int main(){

	/*
		1. 입력
			- 총 테스트 케이스 
			- 현재 상태
			- 최종 상태
			- 금지된 배치 개수
			- 금지된 배치
	
		2. 출력 - bfs 수행 후 결과 출력

		3. 필요한 구조
		   - bfs
		   - 배열(시작 위치 = 0, 금지된 위치 = -1)

		2_개선).
		   - 예외처리 = 금지된 배치가 시작 상태와 최종 상태 사이의 값을 
		   				둘러싸는 경우일 경우
		  			
						금지상태 e4e3e2(e1+-1)
								 e4e3(e2+-1)e1
								 e4(e3+-1)e2e1
								 (e4+-1)e3e2e1
					  => 지나가지 못하는 경우 -1 출력
		   - 예외처리 통과후 수를 증가하는 방향과 감소하는 방향 두개를 지정

		2_개선2).
			- 예외처리 없이 시작 상태에서 최종 상태로 두가지 방향으로 향함
			- 두 방향 모두 막혔을 경우 -1 출력
			- a1 먼저 최종 상태 만든 후 a2 ... a4까지
			- 만약 중간에 금지배치가 나올 경우 a1 중지 후 a2 ...
			- while(최종상태==?) , 아닐 경우 다시 a1부터 수행

			- 중요한 것은 한 방향에 대해서 최단 방향을 구하는 법
				현재 위치 a => abs(a-end) <> abs((a+10)-end) 적은 쪽으로
				if(abs(a-end) < abs(a+10-end))
					방향 +
				else 
					방향 - 

		2_개선3).
			다시 개선1의 예외처리를 넣어서 도달 할 수 있느지 만 판단
			결과 값 : 최종상태 각 자리수의 합  -  시작 상태 각 자리수의 합

		2_개선4).
			....
			결국 BFS를 이용해야 할 것 같다.
	*/

	int testCase;
	scanf("%d", &testCase);
	int a4, a3, a2, a1;
	int s4, s3, s2, s1;
	int e4, e3, e2, e1;
	int start, end;
	int forbid_num;


	for(;testCase>0;testCase--){

		int searchArray[10000]={0};

		scanf("%d %d %d %d", &s4, &s3, &s2, &s1);
		start=s4*1000+s3*100+s2*10+s1;

		
		scanf("%d %d %d %d", &e4, &e3, &e2, &e1);
		end=e4*1000+e3*100+e2*10+e1;

		scanf("%d", &forbid_num);
	
		for(int i=0;i<forbid_num;i++){

			scanf("%d %d %d %d", &a4, &a3, &a2, &a1);
			int temp=a4*1000+a3*100+a2*10+a1;

			searchArray[temp]=-1;
		}
		
		bfs(searchArray, start, end);
		if(start!=end && searchArray[end]==0)
			printf("-1\n");
		else
			printf("%d\n", searchArray[end]);
	}

	return 0;
}
