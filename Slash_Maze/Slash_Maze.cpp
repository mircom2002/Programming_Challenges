#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <list>
#include <queue>
#define lp list<pair<int, int> >


using namespace std;

class Graph{
public:
	int init();
	int w, h;
	map<pair<int, int>, list<pair<int, int> > > g;
	map<pair<int, int>, int> chklist;
	void print();
	void output();
	int dfs(pair<int, int>, pair<int, int>, int);
	priority_queue<int> v;
};

int Graph::dfs(pair<int, int> base, pair<int, int> temp, int count){

	list<pair<int, int> >::iterator it;

	for(it=g.find(temp)->second.begin();it!=g.find(temp)->second.end();++it){
		if(*it==base && count>1){
			v.push(count);
			chklist.find(*it)->second=0;
		//	printf("\n(%d, %d) = ", it->first ,it->second);
			return 1;
		}else if(chklist.find(*it)->second==1){
			chklist.find(*it)->second=0;
			if(dfs(base, *it, count+1)) {
		//		printf("(%d, %d)\t", it->first, it->second);
				return 1;
			}
			chklist.find(*it)->second=1;
		}
	}

	return 0;
}


void Graph::output(){

	map<pair<int, int>, int>::iterator mit;
	for(mit=chklist.begin();mit!=chklist.end();++mit){
		if(mit->second!=1) continue;
	
		mit->second=0;
		dfs(mit->first, mit->first, 0);// mit->second=2;

	}	
//	chklist.find(make_pair(1, 1))->second=0;
//	dfs(make_pair(1, 1), make_pair(1, 1), 0);

	if(v.empty())
		printf("There are no cycles.\n");
	else
		printf("%d Cycles; the longest has length %d.\n", (int)v.size(), (int)(v.top()+1));

	printf("\n");

}


int Graph::init(){

	scanf("%d %d", &w, &h);
	if(!w && !h) return 1;


	char *temp=new char[w+1];

	map<pair<int, int>, list<pair<int, int> > >::iterator it;

	int x, y;

	for(int i=0;i<h;i++){
		
		y=i*2+1;

		scanf("%s", temp);
		
		for(int j=0;j<w;j++){

		/*
			/ <- [(-1, 0), (0, -1)], [(1, 0), (0, 1)]
			\ <- [(-1, 0), (0, 1)], [(0, -1), (1, 0)] 
		*/
			x=j*2+1;

			if(temp[j]=='/'){// (i+1, j), (i, j+1)
				
				it=g.find(make_pair(y-1, x));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y, x-1));
					g.insert(make_pair(make_pair(y-1, x), temp));
					chklist.insert(make_pair(make_pair(y-1, x), 1));
				}else{
	//				it->second.push_back(make_pair(i+1, j));
					it->second.push_back(make_pair(y, x-1));
				}

				it=g.find(make_pair(y, x-1));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y-1, x));
					g.insert(make_pair(make_pair(y, x-1), temp));
					chklist.insert(make_pair(make_pair(y, x-1), 1));
				}else{
					it->second.push_back(make_pair(y-1, x));
	//				it->second.push_back(make_pair(i, j+1));
				}

				it=g.find(make_pair(y+1, x));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y, x+1));
					g.insert(make_pair(make_pair(y+1, x), temp));
					chklist.insert(make_pair(make_pair(y+1, x), 1));
				}else{
	//				it->second.push_back(make_pair(i+1, j));
					it->second.push_back(make_pair(y, x+1));
				}

				it=g.find(make_pair(y, x+1));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y+1, x));
					g.insert(make_pair(make_pair(y, x+1), temp));
					chklist.insert(make_pair(make_pair(y, x+1), 1));
				}else{
					it->second.push_back(make_pair(y+1, x));
	//				it->second.push_back(make_pair(i, j+1));
				}

	
			}else{ // '\', (i, j), (i+1, j+1)
			
				it=g.find(make_pair(y-1, x));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y, x+1));
					g.insert(make_pair(make_pair(y-1, x), temp));
					chklist.insert(make_pair(make_pair(y-1, x), 1));
				}else{
	//				it->second.push_back(make_pair(i+1, j));
					it->second.push_back(make_pair(y, x+1));
				}

				it=g.find(make_pair(y, x+1));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y-1, x));
					g.insert(make_pair(make_pair(y, x+1), temp));
					chklist.insert(make_pair(make_pair(y, x+1), 1));
				}else{
					it->second.push_back(make_pair(y-1, x));
	//				it->second.push_back(make_pair(i, j+1));
				}

				it=g.find(make_pair(y+1, x));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y, x-1));
					g.insert(make_pair(make_pair(y+1, x), temp));
					chklist.insert(make_pair(make_pair(y+1, x), 1));
				}else{
	//				it->second.push_back(make_pair(i+1, j));
					it->second.push_back(make_pair(y, x-1));
				}

				it=g.find(make_pair(y, x-1));
				if(it==g.end()){
					lp temp;
					temp.push_back(make_pair(y+1, x));
					g.insert(make_pair(make_pair(y, x-1), temp));
					chklist.insert(make_pair(make_pair(y, x-1), 1));
				}else{
					it->second.push_back(make_pair(y+1, x));
	//				it->second.push_back(make_pair(i, j+1));
				}
			}

		}

	}

	return 0;
}


void Graph::print(){

	map<pair<int, int>, list<pair<int, int> > >::iterator it;

	for(it=g.begin();it!=g.end();++it){
			
		printf("(%d, %d) - ", it->first.first, it->first.second);

		lp::iterator lpit;
		for(lpit=it->second.begin();lpit!=it->second.end();++lpit){
			printf("(%d, %d)", lpit->first, lpit->second); 
		}

		printf("\n");
	}

}



int main(){

	/*
		1. 입력 
			미로의 너비, 높이
			미로
			너비==높이==0 일시 종료

		2. 출력
			cycle의 수, 길이

		3. 구현방법
			각 슬래시/백슬래시의 끝점을 좌표로 적용, 그래프로 만든 후
			사이클의 수 체크.
			
			how to?
			슬래시 한칸당 1*1을 차지

			pair 값 이용.
			map<pair<int, int>, list<pair<int, int> > >

			결론 pair를 이용하여 구현후, DFS
	*/

	int T=0;
	while(1){

		Graph G;
		if(G.init()) break;
		++T;
		//G.print();
		printf("Maze #%d:\n", T);
		G.output();
	}


	return 0;
}
