#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <queue>

using namespace std;

class Vertex;
class Edge;
template <typename T> class LinkedList;
class Graph;

int main(){
	/*
		1. 이름 : 논문 데이터를 입력받는다.
		2. 이름을 쪼개어 정점에 저장한다.
		3. 모든 입력 받은 후 간선으로 연결한다.
		4. 너비 우선 탐색으로 탐색한다.
	*/


	int T;
	for(;T>0;T--){
		int n, m;
		scanf("%d %d", &n, &m);

		string paper[n];
		string name[m];
		
		getchar();
		for(int i=0;i<n;i++){
			getline(cin, paper[i]);
		}
		for(int i=0;i<m;i++){
			getline(cin, name[m]);
		}


	}
	return 0;
}
