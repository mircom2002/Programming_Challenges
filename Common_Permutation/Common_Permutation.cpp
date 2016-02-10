#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

int main(){

	string a, b;	
	int len_a, len_b;
	while(getline(cin, a, '\n')){
		int temp_arr1[26]={0};
		int temp_arr2[26]={0};
		len_a=a.size();

		for(int i=0;i<len_a;i++){
			temp_arr1[a.at(i)-'a']++;
		}

		getline(cin, b, '\n');
		len_b=b.size();
		
		for(int i=0;i<len_b;i++){
			temp_arr2[b.at(i)-'a']++;
		}
	
		for(int i=0;i<26;i++){
			if(temp_arr1[i] && temp_arr2[i])
				if(temp_arr1[i]>temp_arr2[i])
					for(int j=0;j<temp_arr2[i];j++) printf("%c", 'a'+i);
				else
					for(int j=0;j<temp_arr1[i];j++) printf("%c", 'a'+i);
		}
		printf("\n");

	}

}
