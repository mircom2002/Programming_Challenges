#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main(){

	vector<pair<int, int> > graph[5];
	while(1){
		int start, end;
		scanf("%d %d", &start, &end);
		if(start==-1 && end==-1) break;;
		graph[start].push_back(make_pair(end, 0));
	}

//	vector<pair<int, int> >::iterator it;
	for(int i=0;i<5;++i){
		//cout << *it << endl;
		for(int j=0;j<graph[i].size();j++){
			cout << graph[i][j].first << endl;
			cout << graph[i][j].second << endl;
		}
	}

	return 0;
}
