#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

int main(){

	char test[]="asdfasdf                   asdfasdfdsf";

	char *tok=strtok(test, " ");
	while(tok!=NULL){

		cout << tok << endl;
		tok=strtok(NULL, " ");
	}


}
