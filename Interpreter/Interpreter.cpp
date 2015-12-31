#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


int main(){
	int T;
	char input[30];
	fgets(input, sizeof(input), stdin);

	T=atoi(input);
	//scanf("%d", &T);
	
	int num;

	for(;T>0;T--){
		int count=0;	
		int reg[10]={0};
		int a[1000]={0};
		int com, reg1, reg2;
		int i=0;
		int state=1;
		string s(" ");
	/*	char s[10];
		fgets(s, sizeof(s), stdin);
		while(1){
			fgets(s, sizeof(s), stdin);
			if(s[0]=='\n') break;

			a[i]=atoi(s);
			i++;
	//		cout << "test";
		}
	*/
		while(s.size() < 3)
		    getline(cin, s);

		while(cin.eof() == false) {
			a[i]=(int)(s[0]-'0')*100+(int)(s[1]-'0')*10+(int)(s[2]-'0');
			i++;
			getline(cin, s);
			if(s.size() < 3)
				break;
	    }
	
		if(i==0) continue;		
		i=0;

		while(state){
			
			count++;
			com=a[i]/100;
			reg1=(a[i]/10)%10;
			reg2=a[i]%10;

			switch(com){
			case 1:
				state=0;
				break;
			case 2:
				reg[reg1]=reg2;
				break;
			case 3:
				reg[reg1]+=reg2;
				reg[reg1]%=1000;
				break;
			case 4:
				reg[reg1]*=reg2;
				reg[reg1]%=1000;
				break;
			case 5:
				reg[reg1]=reg[reg2];
				break;
			case 6:
				reg[reg1]+=reg[reg2];
				reg[reg1]%=1000;
				break;
			case 7:
				reg[reg1]*=reg[reg2];
				reg[reg1]%=1000;
				break;
			case 8:
				reg[reg1]=a[reg[reg2]];
				break;
			case 9:
				a[reg[reg2]]=reg[reg1];
				break;
			case 0:
				if(reg[reg2]!=0) {
					i=reg[reg1]-1;
				}
				break;
			}
			i++;
		}
		printf("%d\n", count);
	}

	return 0;
}
