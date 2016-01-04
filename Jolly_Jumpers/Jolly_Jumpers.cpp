#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

int main(){
	int n, state;// n : 입력 받는 정수의 개수, state : Jolly, Not Jolly 저장
	while(1){
		state=1;
		
		string input;
		getline(cin, input);
		
		if(input.size()<=1) return 0;
		
		char *input_arr=new char[input.size()+1];
		strcpy(input_arr, input.c_str());
		char *tok=strtok(input_arr, " ");

		n=atoi(tok);

		int *a=new int[n];
		int temp_prev, temp_cur, temp;
		tok=strtok(NULL, " ");
		temp_prev=atoi(tok);
		for(int i=1;i<n;i++){
			tok=strtok(NULL, " ");
			temp_cur=atoi(tok);
			temp=abs(temp_cur-temp_prev);
			temp_prev=temp_cur;
			
			if(temp>=n){ 
				state=0;
				break;
			}else if(a[temp]==1){
				state=0;
				break;
			}

			if(state) a[temp]=1;

		}

		if(state)
			printf("Jolly\n");
		else
			printf("Not jolly\n");
	}

}
