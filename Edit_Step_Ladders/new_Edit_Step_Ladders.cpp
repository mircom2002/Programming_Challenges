#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;

map<string, int> wordlist;

string addChar(const char *w, char c, int len, int p){

	char l[17];
	int i=0, j=0;
	for(i=0;i<=len;i++){
		if(i==p){
			l[i]=c;
			continue;
		}
		l[i]=*w;
		w++;
	}

	l[len+1]='\0';
	return l;
}

string delChar(const char *w, int len, int p){

	int i=0, j=0;;
	char l[17];
	while(w[i]){
		if(p==i){
			i++;
			continue;
		}
		l[j]=w[i];
		j++;
		i++;
	}
	l[len-1]='\0';
	return l;
}




int main(){
	clock_t begin, end;

//	begin=clock();
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
	//char input[17];
	string input;
	string temp;
	int max;
	int length;

	map<string, int>::iterator it;
	
	while(1){
		//cout << "asdf" << endl;
		//if(scanf("%s", input)==EOF) break;
		getline(cin, input);
		length=input.size();
		if(length<1) break;
//		length=strlen(input);
//		cout << length << endl;
		max=0;
		if(length<=15)
			for(int i=0;i<=length;i++){
				for(char c='a';c<='z';c++){
					temp=addChar(input.c_str(), c, length, i);
					it=wordlist.find(temp);
//					cout << temp << endl;
					if(it!=wordlist.end())
						if(it->second+1>max) max=it->second+1;
				}
			}

		for(int i=0;i<length;i++){
			for(char c='a';c<='z';c++){
				temp=delChar(input.c_str(), length, i);
				it=wordlist.find(temp);
//				cout << temp << endl;
				if(it!=wordlist.end())
					if(it->second+1>max) max=it->second+1;
			}

			char t[17];
			strcpy(t, input.c_str());
			for(char c='a';c<='z';c++){
				t[i]=c;
				temp=t;
//				cout << temp << endl;
				if(t==input) continue;
				it=wordlist.find(temp);
				if(it!=wordlist.end())
					if(it->second+1>max) max=it->second+1;
			}
		}

		wordlist.insert(make_pair(input, max));
	}
	
	max=-1;

	for(it=wordlist.begin();it!=wordlist.end();++it){
//		cout << it->first << ":" << it->second << endl;
		if(it->second>max) max=it->second;
	}

	cout << max+1 << endl;
//	end=clock();

//	cout << (end-begin)/CLOCKS_PER_SEC << endl;


	return 0;
}
