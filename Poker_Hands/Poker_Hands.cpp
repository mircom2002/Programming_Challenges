#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <queue>
#include <stdlib.h>

using namespace std;

string num="23456789TJQKA";
string tile="CDHS";

int chkValue(int* num, int* tile){
/*
	하이카드 : cardNum;
	원페어 : 100 + cardNum;
	투페어 : 200 + cardNum;
	쓰리카드 : 300 + cardNum;
	스트레이트 : 400 + maxCardNum;
	플러시 : 500 + maxCardNum;
	풀하우스 : 600 + maxCardNum;
	포카드 : 700 + maxCardNum;
	스트레이트 플러시 : 800 + maxCardNum;
*/
	int tileValue=0;
	priority_queue<int> onePair;
	priority_queue<int> threeCard;
	priority_queue<int> fourCard;
	int pairChk=0;
	int highCard=-1;

	for(int i=0;i<4;i++){
		if(tile[i]>tileValue) tileValue=tile[i];
	}
	 
	for(int i=0;i<13;i++){
		switch(num[i]){
		case 1:
			if(i>highCard) highCard=i;
			break;
		case 2:
			onePair.push(i);
			pairChk=1;
			break;
		case 3:
			threeCard.push(i);
			pairChk=1;
			break;
		case 4:
			fourCard.push(i);
			pairChk=1;
			break;
		}
	}

	if(pairChk){// 스트레이트가 아닌경우
		if(fourCard.size()>0)//포카드
			return 700+fourCard.top();

		if(threeCard.size()>0 && onePair.size()>0)//풀하우스
			return 600+threeCard.top();

		if(tileValue==5)//플러시
			return 500+highCard;

		if(threeCard.size()>0)
			return 300+threeCard.top();

		if(onePair.size()>1)
			return 200+onePair.top();

		if(onePair.size()>0)
			return 100+onePair.top();

		return highCard;
	}else{
		int straightChk=0;
		for(int i=0;i<5;i++){
			if(num[(highCard-i+13)%13]==1) continue;
			straightChk=1;
		}

		if(straightChk==1){// 스트레이트가 아닌경우
			if(tileValue==5) // 플러시
				return 500+highCard;

			return highCard;
		}else{// 스트레이트인 경우
			if(tileValue==5) // 스트레이트 플러시
				return 800+highCard;

			return 400+highCard;
		}
	}

}

int main(){
	
	string input;
	while(1){
		getline(cin, input);
		if(input.size()<=1) return 0;

		int black[13]={0};
		int white[13]={0};
		int blacktile[4]={0};
		int whitetile[4]={0};
		
		int blackValue=0;
		int whiteValue=0;
		char *temp=new char[input.size()+1];
		strcpy(temp, input.c_str());
		char *token=strtok(temp, " ");

		int blackHigh=0;
		int whiteHigh=0;

		for(int i=0;i<5;i++){
			black[num.find(token[0])]++;
			blacktile[tile.find(token[1])]++;
			blackHigh |= (1 << num.find(token[0]));
			token=strtok(NULL, " ");
		}
		
		for(int i=0;i<5;i++){
			white[num.find(token[0])]++;
			whitetile[tile.find(token[1])]++;
			whiteHigh |= (1 << num.find(token[0]));
			token=strtok(NULL, " ");
		}

		blackValue=chkValue(black, blacktile);
		whiteValue=chkValue(white, whitetile);
		
	  //cout << endl << blackValue << "\t" << whiteValue << endl;
	
		if(whiteValue>blackValue)
			printf("White wins.\n");
		else if(whiteValue==blackValue)
			if(blackHigh>whiteHigh)
				printf("Black wins.\n");
			else if(blackHigh==whiteHigh)
				printf("Tie.\n");
			else
				printf("White wins.\n");
		else
			printf("Black wins.\n");
	}	

	return 0;
}

