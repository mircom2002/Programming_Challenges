#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

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
		char **e_word=new char*[1000];
		char *temp=strtok(encrypt, " ");
		int e_count=0;
		while(temp!=NULL){
			e_word[e_count]=temp;
			temp=strtok(NULL, " ");
			e_count++;
		}
		
		for(int i=0;i<count;i++){
			int e_size=strlen(e_word[i]);
			

		}
			




	}

	return 0;
}
