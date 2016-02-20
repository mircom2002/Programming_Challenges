#include <iostream>
#include <stdio.h>
#include <stack>
#include <queue>
#include <map>
#include <list>
#include <string>
#include <string.h>

using namespace std;

class op{
public:
	bool operator()(pair<string, int> t1, pair<string, int> t2){
		return t1.second<t2.second;
	}
};


int main(){

	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){
		int num;
		scanf("%d\n", &num);
	
		string temp;

		list<string> rlist;
		for(int i=0;i<num;i++){
			getline(cin, temp);
			rlist.push_front(temp);
		}

		map<string, int> rank;
		for(int i=0;i<num;i++){
			getline(cin, temp);
			rank.insert(make_pair(temp, i));
		}
		
		priority_queue<pair<string, int>, vector<pair<string, int> >, op> st;
		map<string, int>::iterator mit;
		list<string> result;
		int current=num-1;

	//	cout<< "start"<<endl;
		while(!rlist.empty()){

			mit=rank.find(rlist.front());
	//		printf("current front %s\n", mit->first.c_str());
			if(mit->second!=current){
				
	//			printf("%d :: %d\n", mit->second, current);
				st.push(make_pair(mit->first, mit->second));
				//printf("stack add %s %d\n", st.top().first.c_str(), st.top().second);
			}else{
				current--;
			}
			rlist.pop_front();
		}

		while(!st.empty()){
			result.push_back(st.top().first);
			st.pop();
		}

		list<string>::iterator it;
		for(it=result.begin();it!=result.end();++it){
			printf("%s\n", (*it).c_str());
		}
		printf("\n");
	}
	return 0;
}
