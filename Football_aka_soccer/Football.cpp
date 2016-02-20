#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class team{
public:
	team(string n);
	string name;
	int point;
	int gamenum;
	int win;
	int draw;
	int lose;
	int wingoal;
	int losegoal;
};

team::team(string n){
	name=n;
	gamenum=0;
	point=0;
	win=0;
	draw=0;
	lose=0;
	wingoal=0;
	losegoal=0;
};

class op{
public:
	bool operator()(team t1, team t2){

		if(t1.point<t2.point) return true;
		
		if(t1.point==t2.point && t1.win<t2.win) return true;
		
		if(t1.point==t2.point && t1.win==t2.win
			&& t1.wingoal-t1.losegoal < t2.wingoal-t2.losegoal) return true;
		
		if(t1.point==t2.point && t1.win==t2.win
			&& t1.wingoal-t1.losegoal==t2.wingoal-t2.losegoal
			&& t1.wingoal<t2.wingoal) return true;

		if(t1.point==t2.point && t1.win==t2.win
			&& t1.wingoal-t1.losegoal==t2.wingoal-t2.losegoal
			&& t1.wingoal==t2.wingoal && t1.gamenum>t2.gamenum) return true;
		
		if(t1.point==t2.point && t1.win==t2.win
			&& t1.wingoal-t1.losegoal==t2.wingoal-t2.losegoal
			&& t1.wingoal==t2.wingoal && t1.gamenum==t2.gamenum
			&& t1.name > t2.name) return true;
			
		return false;
	}
};

int main(){

	int testCase;
	scanf("%d\n", &testCase);

	for(;testCase>0;testCase--){
		
		string temp, gamename;
		getline(cin, gamename);

		int teamnum;
		scanf("%d\n", &teamnum);

		map<string, team> game;

		for(int i=0;i<teamnum;i++){
			getline(cin, temp);
			team t(temp);
			game.insert(make_pair(temp, t));
		}

		int num;
		scanf("%d\n", &num);

		map<string, team>::iterator team1, team2;

		for(int i=0;i<num;i++){
			string t1, t2;
			int p1, p2;
			getline(cin, t1, '#');
			scanf("%d@%d#", &p1, &p2);
			getline(cin, t2);

			team1=game.find(t1);
			team2=game.find(t2);

			if(p1>p2){
				team1->second.win++;
				team1->second.point+=3;
				team2->second.lose++;
			}else if(p1==p2){
				team1->second.draw++;
				team1->second.point++;
				team2->second.draw++;
				team2->second.point++;
			}else{
				team1->second.lose++;
				team2->second.win++;
				team2->second.point+=3;
			}
			
			team1->second.gamenum++;
			team1->second.wingoal+=p1;
			team1->second.losegoal+=p2;

			team2->second.gamenum++;
			team2->second.wingoal+=p2;
			team2->second.losegoal+=p1;
		}

		priority_queue<team, vector<team>, op> pq;

		for(team1=game.begin();team1!=game.end();++team1){
			pq.push(team1->second);
		}
		
		int n=1;
		printf("%s\n", gamename.c_str());
		while(!pq.empty()){
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
				n, pq.top().name.c_str(), pq.top().point, pq.top().gamenum,
				pq.top().win, pq.top().draw, pq.top().lose, 
				pq.top().wingoal-pq.top().losegoal, pq.top().wingoal, 
				pq.top().losegoal);
			pq.pop();
			n++;
		}
		
		printf("\n");


	}

	return 0;
}
