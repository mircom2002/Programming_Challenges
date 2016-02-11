#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <queue>
#include <stack>

using namespace std;

map<string, list<string> > word_map;
map<string, int> word_list;

map<string, list<string> >::iterator it, mit;
map<string, int>::iterator cit;
list<string>::iterator lit;

void init_map(){
	for(cit=word_list.begin();cit!=word_list.end();++cit){
		cit->second=0;
	}
}


int main(){

	string word;
	int len;

	while(1){
		getline(cin, word);

		if(word.size()<1) break;

		list<string> temp;
		word_map.insert(make_pair(word, temp));
		word_list.insert(make_pair(word, 0));

		it=word_map.find(word);

		len=word.size();
		char *c=new char[len];
	
		for(int i=0;i<len;i++){
			strcpy(c, word.c_str());
			for(char t='a';t<='z';t++){
				c[i]=t;	
				mit=word_map.find(c);
				if(mit==word_map.end()) continue;
				
				it->second.push_back(c);
				mit->second.push_back(word);
			}
		}
	}

	char start[16], end[16];
	scanf("\n");
	while(getline(cin, word)){
		int chk=1, count;
		sscanf(word.c_str(), "%s %s", start, end);
		//bfs
		list<pair<string, string> > word_order[1000];
		queue<pair<string, int> > q;
		
		q.push(make_pair(start, -1));
		
		string current;

		while(chk && !q.empty()){
			current=q.front().first;
			count=q.front().second+1;
			q.pop();
			
			it=word_map.find(current);
			for(lit=it->second.begin();lit!=it->second.end();++lit){
				
				cit=word_list.find(*lit);
				if(cit->second) continue;
				
				if(*lit==end){
					word_order[count].push_back(make_pair(current, *lit));
					current=*lit;
					chk=0;
					break;
				}
				
				word_order[count].push_back(make_pair(current, *lit));
				q.push(make_pair(*lit, count));
				cit->second=1;
			}
		}
		
		if(chk)	
			printf("No solution.\n");
		else{
			stack<string> result;
			list<pair<string, string> >::iterator temp_lit;
			for(int i=count;i>=0;i--){
				for(temp_lit=word_order[i].begin();
					temp_lit!=word_order[i].end();
					temp_lit++){
					if(temp_lit->second==current){
						result.push(temp_lit->second);
						current=temp_lit->first;
						break;
					}
				}

			}
			
			result.push(start);
			while(!result.empty()){
				printf("%s\n", result.top().c_str());
				result.pop();
			}

		}
		printf("\n");
		init_map();
	}


	return 0;
}

