#include <stdio.h>
#include <iostream>

using namespace std;

int main(){

	char s[100];
	printf("TEST!\n");
	while(1){

		fgets(s, sizeof(s)-1, stdin);
		//s[2]='\0';
		if(s[0]=='\n') 
			printf("ENTER!\n");
		else
			printf("%s", s);
	}


	return 0;
}
