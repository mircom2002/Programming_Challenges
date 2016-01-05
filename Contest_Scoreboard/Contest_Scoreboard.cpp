#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	Node(int i, int s, int t):num(i), solve(s), time(t){};
	int num;
    int solve;
	int time; 
};

class compareProblem {
public:
    bool operator()(Node& t1, Node& t2){
		if (t1.solve < t2.solve) return true;
    	if (t1.solve == t2.solve && t1.time > t2.time) return true;
    	if (t1.solve==t2.solve && t1.time==t2.time && t1.num > t2.num) return true;
		return false;
	}
};

		
//priority_queue<Node, vector<Node>, CompareProblem> pq;


int main(){


	int testCase;
	scanf("%d\n", &testCase);
	
	for(;testCase>0;testCase--){
		/*
			int chk[100][10] <- 100팀의 10문제 시간저장, 0=체크, 1=시간
			int solveProblem[100] <- 100팀이 각 푼 문제수 체크
			int solveTime[100] <- 100팀이 각 푼 문제시간 체크
			

			solveProblem은 0~10 까지 밖에 없다. = 11개짜리 우선순위 큐 배열을 만들어서 문제 푼 시간을 넣는다 -> 차례로 뺀다.
			
			== pq.push({num, solveProblem[num], soleTime[num]})
		*/
		int chk[101][11]={0};// <- 100팀의 10문제 시간풀이여부 0=못품, 1=품
		int solveProblem[101]={0};// <- 100팀이 각 푼 문제수 체크
		int solveTime[101]={0};// <- 100팀이 각 푼 문제시간 체크
		int unsolveTime[101][11]={0};// <- 100팀이 문제 풀기전 까지 못푼 시간
		int joinChk[101]={0}; // <- 참가여부 확인
		string input;
		//getchar();
		//getline(cin, input);
		while(1){

			getline(cin, input);
			//if(input.size()<1) break;
			//cout << "입력 " << input << endl;		
			char *ex=new char[input.size()+1];
			strcpy(ex, input.c_str());
				
			int _n;
			int _problem;
			int _time;
			char _state;

			if(sscanf(ex, "%d %d %d %c", &_n, &_problem, &_time, &_state)<1) break;
			
			//printf("\n중간값 : %d %d %d %d\n", _n, _problem, _time, _state);

			if(_state=='C'){
				if(chk[_n][_problem]==1) continue;
				chk[_n][_problem]=1;
				solveProblem[_n]++;
				solveTime[_n]+=_time+unsolveTime[_n][_problem];
			}else if(_state=='I'){
				//if(chk[_n][_problem]==1) continue;
				unsolveTime[_n][_problem]+=20;
			}

			joinChk[_n]=1;

		}
		
		priority_queue<Node, vector<Node>, compareProblem> pq;

		for(int i=1;i<=100;i++){
			if(joinChk[i]==0) continue;
			Node n(i, solveProblem[i], solveTime[i]);
			pq.push(n);
		}
		
		while(!pq.empty()){
			Node n=pq.top();
			pq.pop();
			printf("%d %d %d\n", n.num, n.solve, n.time);
		}
		
		printf("\n");
		cin.clear();

	}
	return 0;
}
