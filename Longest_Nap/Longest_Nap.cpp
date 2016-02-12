#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main(){

	int num, day=1;
	while(scanf("%d\n", &num)==1){
		int h1, m1, h2, m2, start, end;
		string s;

		int schedule[481]={0};
		schedule[480]=1;
		for(int i=1;i<=num;i++){
			getline(cin, s);
			sscanf(s.c_str(), "%d:%d %d:%d", &h1, &m1, &h2, &m2);
			start=h1*60+m1;
			end=h2*60+m2;
			if(start<600) start=600;
			if(end>1080) end=1080;

			for(int j=start-600;j<end-600;j++){
				schedule[j]=1;
			}
		}

		int nap=0, temp, time=600;
		int current=0;
			
		for(int i=0;i<480;i++){
			if(!schedule[i]){
				current=i;
				temp=0;
				for(int j=i;;j++){
					if(schedule[j]) break;
					temp++;
				}

				if(temp>nap) {
					time=current+600;
					nap=temp;	
				}
			}
		}

		printf("Day #%d: ", day);
		printf("the longest nap starts at %02d:%02d and will last for ", time/60, time%60);
		if(nap>=60)
			printf("%d hours and %d minutes.", nap/60, nap%60);
		else
			printf("%d minutes.\n", nap);
		day++;

	}


	return 0;
}
