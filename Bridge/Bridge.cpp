#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>

bool op(int i, int j){return i>j;}

using namespace std;

int main(){

	/*
		가장 빠른 사람과 두번째로 빠른 사람이 건넌다.
		
		가장 빠른 사람이 돌아온다.

		가장 느린 사람과 두번째로 가장 느린 사람이 건넌다.

		두번째로 빠른 사람이 돌아온다.

		가장 빠른 사람과 두번째로 빠른 사람이 건넌다.

		...

		결론은 가장 빠른 두명만 이용하면 된다.
	*/

	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){
		int num, temp;
		scanf("%d", &num);

		vector<int> member;

		for(int i=0;i<num;i++){
			scanf("%d", &temp);
			member.push_back(temp);
		}

		sort(member.begin(), member.end());
		int sum=0;
		list<pair<int, int> > result;

		while(1){
			if(num>3){
				if(member[num-2] + member[0] < member[1]*2){
					result.push_back(make_pair(member[0], member[num-1]));
					result.push_back(make_pair(member[0], -1));
					result.push_back(make_pair(member[0], member[num-2]));
					result.push_back(make_pair(member[0], -1));
					sum+=2*member[0]+member[num-1]+member[num-2];
					num-=2;
				}else{
					result.push_back(make_pair(member[0], member[1]));
					result.push_back(make_pair(member[0], -1));
					result.push_back(make_pair(member[num-2], member[num-1]));
					result.push_back(make_pair(member[1], -1));
					sum+=member[0]+2*member[1]+member[num-1];
					num-=2;
				}
			}else if(num==3){
				result.push_back(make_pair(member[0], member[2]));
				result.push_back(make_pair(member[0], -1));
				result.push_back(make_pair(member[0], member[1]));
				sum+=member[0]+member[1]+member[2];
				break;
			}else if(num==2){
				result.push_back(make_pair(member[0], member[1]));
				sum+=member[1];
				break;
			}else if(num==1){
				result.push_back(make_pair(member[0], -1));
				sum+=member[0];
				break;
			}else 
				break;
		}

		printf("%d\n", sum);
		list<pair<int, int> >::iterator lit;
		for(lit=result.begin();lit!=result.end();lit++){
			if(lit->second==-1)
				printf("%d\n", lit->first);
			else
				printf("%d %d\n", lit->first, lit->second);
		}

		printf("\n");
	}
	return 0;
}
