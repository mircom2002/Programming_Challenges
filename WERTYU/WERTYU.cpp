#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

map<char, char> keymap;

void init_keymap(){
	string a="  \n\n`1234567890-=QWERTYUIOP[]ASDFGHJKL;'ZXCVBNM,./";
	
	for(int i=1;i<a.size();i++){
		keymap.insert(make_pair(a.at(i), a.at(i-1)));
	}
	keymap.insert(make_pair(92, ']'));

}


int main(){

	init_keymap();

	char c;
	while(scanf("%c", &c)==1) printf("%c", keymap.find(c)->second);
	
	cout << endl;
	return 0;

}
