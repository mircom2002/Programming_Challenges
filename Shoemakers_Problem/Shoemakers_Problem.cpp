#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class op{
public:
	bool operator()(pair<int, pair<int, int> > in, pair<int, pair<int, int> > st){
		if(in.second.first*st.second.second 
			> in.second.second * st.second.first) return true;

		if(in.second.first * st.second.second
			== st.second.first * in.second.second && in.first > st.first) return true;
		return false;
	}
};

int main(){

	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){
		int num;
		scanf("%d", &num);
		int day, fine;
		priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, op> pq;
	
		for(int i=1;i<=num;i++){
			scanf("%d %d", &day, &fine);
			pq.push(make_pair(i, make_pair(day, fine)));
		}

		printf("%d", pq.top().first);
		pq.pop();
		while(!pq.empty()){
			printf(" %d", pq.top().first);
			pq.pop();
		}

		printf("\n\n");
	}
	return 0;
}
