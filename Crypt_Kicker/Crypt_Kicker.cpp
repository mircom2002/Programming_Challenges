#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

void print(string, int);
int backTracking(string*, int); // 해독할 문자 배열과, 해독할 현재 위치

int countLength[17]={0};
char descryptTable[26];
char encryptTable[26];
int *wordLength;
string *word;
int n;

int main(){
	// 결론은 백트랙킹
	/*	
		  0) 시간과 공간은 반비례 한다.

		  1) 예외처리
		    사전 단어의 길이는 2~16까지 이므로 2~16까지의 단어 길이를 저장하는 배열을 만들어 입력받은 문장에서의 단어의 길이와 비교한다
		  
		  2) 고민해결
		  	 ㄱ. 단어의 길이를 저장한다.
			 ㄴ. 단어를 통째로 저장한다.

	      3) 전체 해독 배열을 만든다.
		    a b c d e f g h i j k l m n o p q r s t u v w x y z
	       암호화, 복호화를 위한 배열 밑으로는 암호화 위로는 해독

		  4) 문장의 단어를 사전의 단어와 비교해 해당 배열에 집어넣는다.

		  5) 경우의 수
		     ㄱ. 배열이 다 찼을 경우 - 암호 해독이 완료된 경우이므로 마지막으로 사전에 해당 단어가 있는 지 검사 후 출력, 없으면 다음 단어로 이동. 없으면 이전 단어로
			 ㄴ. 중간에 겹치는 경우 - 암호 해독이 실패된 경우이므로 사전의 다음 단어를 해독 하고 더이상 단어가 없으면 이전 단어부터 다시 해독한다.
			 	a. 이전 단어로 갔을 때 어떻게 이전 단어만 제외시킬 것인가? 
				   - 재귀를 이용, 
				       문자를 추가하는 부분
					           재귀
					   문자를 제외하는 부분
			 ㄷ. 모든 단어가 다 겹치는 경우

		  6) 필요한 자료구조
		     ㄱ. 마지막 단어 검사를 위해 필요한 map
			 ㄴ. 모든 단어를 저장하는 배열
			 ㄷ. 모든 단어의 길이를 저장하는 배열
			 ㄹ. 2~16까지 길이의 단어가 몇개 존재하는지 나타내는 배열
			 ㅁ. 해독 한 결과가 저장되는 배열
			 ㅂ. 해독할 문장의 단어를 저장하는 배열
	*/
	scanf("%d", &n);
	getchar();
	string input;

	wordLength=new int[n];
	word=new string[n];

	for(int i=0;i<n;++i){
		getline(cin, input);
		word[i]=input;
		wordLength[i]=word[i].size();
		countLength[wordLength[i]]++;
	}

	while(1){
		getline(cin ,input);
		if(input.size()<1){
			getline(cin, input);
			if(input.size()<1)
				break;
		}

		for(int i=0;i<26;i++){
			descryptTable[i]=' ';
			encryptTable[i]=' ';
		}

		int state=0;// 해당 문장이 해독 가능한지 여부 체크, 1은 해독 불가능
		int start=0;
		int index;
		int count=0;
		string encryptWord[80];

		while(1){
			index=input.find(" ", start);
			if(index==string::npos) {
				encryptWord[count]=input.substr(start, input.size());
				count++;
				break;
			}
			encryptWord[count]=input.substr(start, index-start);
			start=index+1;
			count++;
		}
		
		state=backTracking(encryptWord, count-1);

		print(input, state);

	}


	return 0;

}

int backTracking(string *encryptWord, int current){ // 마지막 단어에서 부터 앞으로 접근.
	if(current<0) return 0;

	int c_size=encryptWord[current].size();
	
	if(countLength[c_size]==0) return 1;

	int chk;
	char enc_temp;
	char word_temp;	
	for(int i=0;i<n;i++){
		chk=0;
		if(wordLength[i]==c_size){
			char temp[26]="                         ";
			char e_temp[26]="                         ";
			// 단어의 중복방지.. HOW TO?
			for(int j=0;j<c_size;j++){
				enc_temp=encryptWord[current].c_str()[j];
				word_temp=word[i].c_str()[j];
				if(descryptTable[enc_temp-'a']!=' ' &&
					descryptTable[enc_temp-'a']!=word_temp) {
					chk=1;
					break;
				}
			
				if(encryptTable[word_temp-'a']!=' ' &&
					encryptTable[word_temp-'a']!=enc_temp){
					chk=1;
					break;
				}
	
				if(descryptTable[enc_temp-'a']==' '){
					descryptTable[enc_temp-'a']=word_temp;
					temp[enc_temp-'a']=word_temp;
				}

				if(encryptTable[word_temp-'a']==' '){
					e_temp[word_temp-'a']=enc_temp;
					encryptTable[word_temp-'a']=enc_temp;
				}


			}
			
			if(!chk) if(!backTracking(encryptWord, current-1)) return 0;

			for(int j=0;j<c_size;j++){
				word_temp=word[i].c_str()[j];
				enc_temp=encryptWord[current].c_str()[j];
				if(temp[enc_temp-'a']!=' ')	descryptTable[enc_temp-'a']=' ';
				if(e_temp[word_temp-'a']!=' ') encryptTable[word_temp-'a']=' ';
			}
		}
	}

	return 1;
}


void print(string input, int state){// state 0이면 정상 출력, 1이면 *출력

	int size=input.size();
	char temp;
	for(int i=0;i<size;i++){
		temp=input.c_str()[i];
		if(temp==' ')
			cout << " ";
		else{
			if(state){
				cout << "*";
			}else{
				cout << descryptTable[temp-'a'];
			}
		}
	}
	cout << endl;
}










