#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

char key[]="the quick brown fox jumps over the lazy dog";
int len_key=strlen(key);

int main(){

	int testCase;
	scanf("%d", &testCase);
	
	for(int T=0;T<testCase;T++){
		scanf("\n");
		string input[100], temp;
		int num=0;
		while(1){
			getline(cin, temp, '\n');
			if(temp.size()<1) break;
			input[num]=temp;
			num++;
		}
	
		char descrypt_table[26], tc; // descrypt_table[어떤문자 - 'a'] = 원래 문자
		int chk=0;
		for(int i=0;i<num;i++){
			memset(descrypt_table, 0, 26*sizeof(char));
			if(input[i].size()!=len_key) continue;
			
			for(int j=0;j<len_key;j++){
				chk=1;
				tc=input[i].at(j);
				if(tc==' '){
					if(key[j]!=' ') {
						chk=0;
						break;
					}
					continue;
				}
				tc-='a';
				if(descrypt_table[tc]==0){
					descrypt_table[tc]=key[j];
				}else if(descrypt_table[tc]!=key[j]){
					chk=0;
					break;
				}
			}
			if(chk)	break;
		}

		if(!chk){
			printf("No solution.\n\n");
			continue;
		}
		for(int i=0;i<num;i++){
			int temp_size=input[i].size();

			for(int j=0;j<temp_size;j++){
				if(input[i].at(j)==' ') 
					printf(" ");
				else
					printf("%c", descrypt_table[input[i].at(j)-'a']);
			}
			printf("\n");
		}
	
		printf("\n");



	}

	return 0;
}
