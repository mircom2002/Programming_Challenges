#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <string.h>
#define MAX_NUM 99999999

using namespace std;

int main(){

	int T;
	scanf("%d", &T);

	for(;T>0;T--){
		int n;
		scanf("%d", &n); // 후보자 수
		string s[n];
		getchar();
		for(int i=0;i<n;i++){ // 후보자 이름 입력
			getline(cin, s[i]);
		}
		/*
			0. 필요한 구조 큐(후보자큐, 투표자큐, 후보자배열)
			1. 투표자의 투표 결과를 큐에 담는다 = 1인당 1큐
			2. 각 투표자큐의 첫번째 elem 값응로 후보자 큐에 큐를 넣는다.
			3. 후보자 큐의 각 표 수를 체크한다.
			4-1. 모든 투표수가 같다 = 모든 후보자의 이름을 출력한다
			4-2. 작은 사람이 있다 = 그 후보자 배열을 비활성화, 각 투표자 큐의
			     첫 원소를 삭제(pop) 후 다시 후보자 큐에 넣는다.
		    5. 반복
		*/
	
		queue<queue<int> > cq[n]; // 후보자 큐	
		string v;
		int vsize=0;
		cin.clear();
		while(1){
			getline(cin, v);
			if(v.size()==0) break;
			
			char *temp=new char[v.size()+1];
			strcpy(temp, v.c_str());

			queue<int> vq;
			char *t=strtok(temp, " ");
			
			for(int i=0;i<n;i++){
				vq.push(atoi(t)-1);
				t=strtok(NULL, " ");
			}
			cq[vq.front()].push(vq);
			vsize++;
		}



		while(1){
		/*	for(int i=0;i<n;i++){
				cout << cq[i].size() << " ";
			}
			cout << endl; 
		*/	int min=MAX_NUM, minnum, max=-1, maxnum;

			for(int i=0;i<n;i++){
				int temp=cq[i].size();
				
				if(temp<min && temp>0) {
					min=temp;
					minnum=i;
				}
				
				if(temp>max && temp>0){
					max=temp;
					maxnum=i;
				}
			}



			if(min==max){
				for(int i=0;i<n;i++){
					if(cq[i].size()==min) cout << s[i] << endl;
				}
				break;
			}else if(max>(vsize+2)/2){
				cout << s[maxnum] << endl;
				break;
			}else{
				int *fail=new int[n];
				for(int i=0;i<n;i++){
					if(cq[i].size()==min)
						fail[i]=i;
					else
						fail[i]=-1;
				}
				for(int k=0;k<n;k++){
					if(fail[k]==-1) continue;
					for(int i=0;i<min;i++){
						while(1){
							cq[k].front().pop();
							if(cq[cq[k].front().front()].size()!=0 
								&& fail[cq[k].front().front()]==-1) break;
						}
						cq[cq[k].front().front()].push(cq[k].front());
						cq[k].pop();
					}
				}
				delete(fail);
			}
		}
		cout << endl;
	}

	return 0;
}



