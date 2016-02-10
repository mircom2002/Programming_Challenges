#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class test{
public:
	test();
	void find(char* );
	void printmap();
private:
	char** word_map;
	vector<pair<int, int> > move;	
	int n, m;
};

test::test(){
	scanf("%d %d\n", &n, &m);

	word_map=new char*[n];
	char temp;
	for(int i=0;i<n;i++){
		word_map[i]=new char[m+1];
		scanf("%s", word_map[i]);
		
		for(int j=0;j<m;j++)
			if(word_map[i][j]>='a') word_map[i][j]-=32;
	}

	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			move.push_back(make_pair(i, j));
		}
	}

}

void test::printmap(){
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			printf("%c", word_map[i][j]);
		}
		printf("\n");
	}

}

void test::find(char* s){

	queue<pair<int, int> > q;	
	
	int len=strlen(s);

	for(int i=0;i<len;i++){
		if(s[i]>='a') s[i]-=32;
	}


	char temp=s[0];

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(word_map[i][j]==temp) q.push(make_pair(i, j));
		}
	}
	
	if(len==1){
		printf("%d %d\n", q.front().first+1, q.front().second+1);
		return; 
	}

	int c_x, c_y;
	while(!q.empty()){

		for(int i=0;i<9;i++){
			if(i==4) continue;
			c_y=q.front().first;
			c_x=q.front().second;
			
			for(int j=1;j<len;j++){
			
				c_y-=move[i].first;
				c_x-=move[i].second;
			
				if(c_y<0 || c_x<0 || c_y>=n || c_x>=m) break;
				if(word_map[c_y][c_x]!=s[j]) break;
				if(j==len-1){
					printf("%d %d\n", q.front().first+1, q.front().second+1);
					return;
				}
			}

		}

		q.pop();
	}
	
}



int main(){
	
	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){
		test test1;

//		test1.printmap();

		int n;
		scanf("%d", &n);
		
		for(int i=0;i<n;i++){
			char input[21];
			scanf("%s", input);
			
			test1.find(input);
		}

		printf("\n");
	}

	return 0;
}
