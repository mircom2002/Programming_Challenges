#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

void printStar(string input){

	int size=input.size();

	for(int i=0;i<size;i++){
		if(input[i]!=' ')
			printF("*");
		else
			printf(" ");
	}
	printf("\n");
}

void printDescrypt(string input, int **des){
	





}


int main(){
	
	int wordnum;
	scanf("%d", &wordnum);
	int *wordSize=new int[wordnum];

	string word[wordnum];
	for(int i=0;i<wordnum;i++){
		getline(cin, word[i]);
		wordSize[i]=word[i].size();
	}

	string input;
	getline(cin, input);

	while(1){
		getline(cin, input);
		if(input.size()<=1) return 0;

		char *encrypt=new char[input.size()+1];
		strcpy(encrypt, input.c_str());
		//char **e_word=new char*[1000];
		char *temp=strtok(encrypt, " ");
		/*
			1. 단어를 입력 받고
			2. 문장을 입력 받고
			3. 문장을 분해
			4. 분해한 문장의 단어에 하나씩 처음 입력받은 단어를 뺀다
			4-1. 모두 균일한 값이 나온다 => 바른 해석 => 이때 값의 범위는(0~25)
			4-2. 균일한 값이 나오지 않는다 => 잘못된 해석
			5. 바른 단어의 배열을 만든다.
			=> 문장의 각 단어별 배열 [분해한 단어의 개수][0~25]를 만들어 올바른 단어를 집어넣는다.
			6. 판단
			6-1. 모든 분해한 단어에 맞는 해석이 존재하면 출력
			6-2. 맞는 해석이 존재하지 않으면 * 출력.
		*/
		int e_count=0;	
		int descrypt[80][26]={0};	// 문장의 해석한 단어 배열

		while(temp!=NULL){	// 입력 받은 문장 분해
			// temp <- 분해한 단어
			for(int i=0;i<wordnum;i++){
				if(wordSize[i]==strlen(temp)){ // 같은 길이의 단어
					int m_val=abs(word[i][0]-temp[0]+26)%26
					int chk=0;
					for(int j=1;j<wordSize[i];j++){
						if((word[i][j]-temp[j]+26)%26!=m_val){
							chk=1;
							break;
						}
					}

					if(chk) continue;
					descrypt[e_count][m_val]=i;
				}
			}
			//e_word[e_count]=temp;
			temp=strtok(NULL, " ");
			e_count++;
		}

		int find;
		for(int i=0;i<26;i++){
			int chk=1;
			find = i;
			for(int j=0;j<e_count;j++){
				if(descrypt[j][i]==0) chk=0;
			}
			if(chk) break;
		}
			
		if(chk)
			printDescrypt(input, descrypt);
		else
			printStar(input);
		
	}

	return 0;
}
