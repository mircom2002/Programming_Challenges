#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <queue>

using namespace std;

vector<string> word[17];
map<string, int> wordvalue;
map<string, list<string> > graph_in;
map<string, list<string> > graph_out;

void dfs(list<string> wordlist, int depth){

	list<string>::iterator lit;

	for(lit=wordlist.begin();lit!=wordlist.end();++lit){
	
		if(depth<wordvalue.find(*lit)->second) continue;
		wordvalue.find(*lit)->second=depth;
		dfs(graph_in.find(*lit)->second, depth+1);
	}



}


int distinct(string w1, string w2, int w1_size, int w2_size){
	
	int chk=0, i;
	switch(w1_size-w2_size){
	case -1:		
		if(w2.find(w1)==string::npos){
			for(i=0;i<w1_size;i++)
				if(w1.at(i)!=w2.at(i)) break;

			for(;i<w1_size;i++)
				if(w1.at(i)!=w2.at(i+1)) return 1;
		}
		return 0;
		break;
	case 0:
		for(i=0;i<w1_size;i++){
			if(w1.at(i)!=w2.at(i)) chk++;
			if(chk>1) return 1;
		}
		if(chk>1) return 1;
		return 0;
		break;
	case 1:
		if(w1.find(w2)==string::npos){
			for(i=0;i<w2_size;i++)
				if(w2.at(i)!=w1.at(i)) break;

			for(;i<w2_size;i++)
				if(w2.at(i)!=w1.at(i+1)) return 1;
		}
		return 0;
		break;
	}
	return 1;
}



int main(){

	/*
		1. 입력 - 소문자로 구성된 10글자 이하의 영어 단어, 공백 입력시 종료
		
		2. 출력 - 편집 단계 값이 가장 큰 값 출력
				= 가장 먼 거리 값 출력

		3. 구현방법
			1) 영어단어를 저장하는 배열 생성, 단어 입력시 해당 단어의 그래프 정점 생성
			2) 입력 받은 단어와 영어단어 배열 비교
				- 편집 단계 시 해당 단어와 입력 받은 단어를 연결
			
			3) bfs가 아닌 유향 그래프이므로 topological 이

		4. how to? 편집 단계 구별
			1) 단어의 길이로 -1~+1 까지 판별
				ㄱ. -1 혹은 +1 시 
					끝, 처음 글자 비교
				ㄴ. 0 시
					글자 모두 비교
	*/
	string input;

	while(1){
		getline(cin, input);
		if(input.size()<1) break;
		
		int wordsize=input.size();
		list<string> temp;	
		graph_in.insert(make_pair(input, temp));
		graph_out.insert(make_pair(input, temp));

		for(int i=wordsize-1;i<=wordsize+1;i++){
			if(i>16) break;
			int wordsize2=word[i].size();

			for(int j=0;j<wordsize2;j++){
				if(distinct(word[i][j], input, i, wordsize)) continue;
				graph_in.find(input)->second.push_back(word[i][j]); // 들어오는 간선
				graph_out.find(word[i][j])->second.push_back(input); // 나가는 간선
			}
		}
		wordvalue.insert(make_pair(input, 1));
		word[wordsize].push_back(input);
	}

	/*
		1. 들어오는 간선이 없는 정점을 구한다 - depth=0;
		2. 위의 정점에 나가는 간선을 모두 큐에 넣는다 - depth=1;
		3. bfs(), 큐가 빌때까지.
	*/

	queue<string> q;
	map<string, list<string> >::iterator it;
	list<string>::iterator lit;

	for(it=graph_out.begin();it!=graph_out.end();++it){
		if(it->second.size()==0){
			q.push(it->first);
		}
	}

	//while(!q.empty()){

		dfs(graph_in.find(q.front())->second, 1);
		q.pop();

	//}

	map<string, int>::iterator vit;
	int max=-1;
	for(vit=wordvalue.begin();vit!=wordvalue.end();++vit){
		if(vit->second>max) max=vit->second;
	}

	cout << max+1 << endl;


/*
	int depth;
	int max=-1;
	while(!q.empty()){
		
		string temp=q.front();
		depth=wordvalue.find(temp)->second+1;
		//if(depth>max) max=depth;
		q.pop();

		for(lit=graph_out.find(temp)->second.begin();
			lit!=graph_out.find(temp)->second.end();++lit){
			if(wordvalue.find(*lit)->second>depth) continue;
			
			q.push(*lit);
			wordvalue.find(*lit)->second=depth;
		}
	}
	
*/
//	cout << q.size() << endl;;
	


/*
	for(it=graph_in.begin();it!=graph_in.end();++it){
		cout << it->first << " : ";
		for(lit=it->second.begin();lit!=it->second.end();++lit){
			cout << *lit << ",  ";
		}
		cout << endl;
	}

	map<string, int>::iterator vit;
	for(vit=wordvalue.begin();vit!=wordvalue.end();++vit){
	
		cout << vit->first << " : " << vit->second << endl;

	}

*/

	return 0;
}
