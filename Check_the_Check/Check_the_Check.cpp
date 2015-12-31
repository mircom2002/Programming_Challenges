#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

char a[8][8];
int white_x, white_y, black_x, black_y;


int input_board(){
	int check=0;
	for(int i=0;i<8;i++){
		//cin.getline(a[i], 9);
		scanf("%s", a[i]);
		for(int j=0;j<8;j++){
			if(a[i][j]=='.') {
				check++;
			}else if(a[i][j]=='k'){
				black_x=j;
				black_y=i;
			}else if(a[i][j]=='K'){
				white_x=j;
				white_y=i;
			}
		}
	}
	if(check==64) return 1;
	return 0;

}

int knight(int x, int y, int kx, int ky){

	if(y-2==ky && x-1==kx) return 1;
	if(y-1==ky && x-2==kx) return 1;
	if(y-2==ky && x+1==kx) return 1;
	if(y-1==ky && x+2==kx) return 1;
	if(y+2==ky && x-1==kx) return 1;
	if(y+1==ky && x-2==kx) return 1;
	if(y+2==ky && x+1==kx) return 1;
	if(y+1==ky && x+2==kx) return 1;
	return 0;
}


int bishop(int x, int y, int kx, int ky){
	if(abs(ky-y)==abs(kx-x)){
		if(ky>y && kx>x){
			for(int k=1;k<8;k++){
				if(y+k<8 && x+k<8){
					if(y+k==ky && x+k==kx) return 1;
					else if(a[y+k][x+k]!='.') break;
				}
			}
		}else if(ky>y && kx<x){
			for(int k=1;k<8;k++){
				if(y+k<8 && x-k>=0){
					if(y+k==ky && x-k==kx) return 1;
					else if(a[y+k][x-k]!='.') break;
				}
			}
		}else if(ky<y && kx>x){
			for(int k=1;k<8;k++){
				if(y-k>=0 && x+k<8){
					if(y-k==ky && x+k==kx) return 1;
					else if(a[y-k][x+k]!='.') break;
				}
			}
		}else if(ky<y && kx<x){
			for(int k=1;k<8;k++){
				if(y-k>=0 && x+k>=0){
					if(y-k==ky && x-k==kx) return 1;
					else if(a[y-k][x-k]!='.') break;
				}
			}
		}
	}
	return 0;
}

int rook(int x, int y, int kx, int ky){

	if(y==ky){
		if(x>kx){
			for(int k=1;k<8;k++){
				if(x-k>=0)
					if(x-k==kx) return 1;
					else if(a[y][x-k]!='.') break;
			}
		}else{
			for(int k=1;k<8;k++){
				if(x+k<8)
					if(x+k==kx) return 1;
					else if(a[y][x+k]!='.') break;
			}
		}
	}else if(x==kx){
		if(y>ky){
			for(int k=1;k<8;k++){
				if(y-k>=0)
					if(y-k==ky) return 1;
					else if(a[y-k][x]!='.') break;
			}
		}else{
			for(int k=1;k<8;k++){
				if(y+k<8)
					if(y+k==ky) return 1;
					else if(a[y+k][x]!='.') break;
			}
		}	
	}
	return 0;

}


int queen(int x, int y, int kx, int ky){
	if(bishop(x, y, kx, ky) || rook(x, y, kx, ky)) return 1;
	return 0;
}

int check(){ // 0 - white Check , 1 - black Check
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			switch(a[i][j]){
			case'p':// pawn
				if(i+1==white_y && (j-1==white_x || j+1==white_x)) return 0;
				break;
			case'P':
				if(i-1==black_y && (j-1==black_x || j+1==black_x)) return 1;
				break;
			case'n':// knight, 8가지 방향
				if(knight(j, i, white_x, white_y)) return 0;
				break;
			case'N':
				if(knight(j, i, black_x, black_y)) return 1;
				break;
			case'b'://bishop, 대각선
				if(bishop(j, i, white_x, white_y)) return 0;
				break;
			case'B':
				if(bishop(j, i, black_x, black_y)) return 1;
				break;
			case'r':
				if(rook(j, i, white_x, white_y)) return 0;
				break;
			case'R':
				if(rook(j, i, black_x, black_y)) return 1;
				break;
			case'q':
				if(queen(j, i, white_x, white_y)) return 0;
				break;
			case'Q':
				if(queen(j, i, black_x, black_y)) return 1;
				break;
			case'k':
				if(abs(white_x-black_x)<=1 && abs(white_y-black_y)<=1) return 0;
				break;
			case'K':
				if(abs(white_x-black_x)<=1 && abs(white_y-black_y)<=1) return 1;
				break;
			}
		}
	}
	return 2;
}


void print_board(){

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
			cout << a[i][j];
		cout << endl;
	}
		/*
		puts(a[i]);
		putchar('\n');
		*/
	
}

int main(){
	
	int T;
	int gameState;
	for(T=1;;T++){
			
		if(input_board()) return 0;

		gameState=check();
		
		if(gameState==1)
			printf("Game #%d: black king is in check.\n", T);
		else if(gameState==0)
			printf("Game #%d: white king is in check.\n", T);
		else
			printf("Game #%d: no king is in check.\n", T);

		//print_board();
	}
	return 0;
}
