#include <iostream>
#include <stdio.h>
#include <map>
#include <list>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(){

	int testCase;
	scanf("%d", &testCase);

	for(int T=0;T<testCase;T++){

		scanf("\n");
		string temp;
		list<string> input[1000];
		int size, min=99999, max=-1, num=0;
		
		while(1){
			getline(cin, temp);
			size=temp.size();	
			if(size<1) break;
			if(size<min) min=size;
			if(size>max) max=size;
			input[size].push_back(temp);
			num++;
		}
		
		size=min+max;
		
		if(num%2==1){
			cout << input[max].front() << endl << endl;
			continue;
	
		}

		map<string, int> key_map;
		map<string, int>::iterator mit;
		list<string>::iterator it1, it2;

		for(int i=min;i<=(size+1)/2;i++){
			for(it1=input[i].begin();it1!=input[i].end();it1++){
				for(it2=input[size-i].begin();it2!=input[size-i].end();it2++){
					
					if(it1==it2) continue;
					temp=*it1+*it2;
					mit=key_map.find(temp);
					if(mit==key_map.end())
						key_map.insert(make_pair(temp, 0));
					else
						mit->second++;

					temp=*it2+*it1;
					mit=key_map.find(temp);
					if(mit==key_map.end())
						key_map.insert(make_pair(temp, 0));
					else
						mit->second++;
				}
			}
		}

		max=-1;
		for(mit=key_map.begin();mit!=key_map.end();mit++){
			if(mit->second > max) {
				max=mit->second;
				temp=mit->first;
			}
		}

		cout << temp << endl << endl;


	}

	return 0;
}
