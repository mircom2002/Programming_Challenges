#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

char a[252][252]={'\0'};

void swap(int &a, int &b){
	int c=a;
	a=b;
	b=c;
}


void setBoard(int m, int n){
	
	for(int i=0;i<252;i++)
		for(int j=0;j<252;j++)
			a[i][j]='\0';

	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]='O';

}

void drawingColor(int x1, int y1, int x2, int y2, char c){
	if(x1>x2) swap(x1, x2);
	if(y1>y2) swap(y1, y2);
	
	for(int i=y1;i<=y2;i++){
		for(int j=x1;j<=x2;j++){
			a[i][j]=c;
		}
	}
}

void printBoard(int m, int n, char* name){
	printf("%s\n", name);
	//cout << name << endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%c", a[i][j]);
		}
		printf("\n");
	}

}

void fillColor(int x, int y, char oldC, char newC){
	
	if(oldC==newC) return;

	a[y][x]=newC;
	if(a[y-1][x]==oldC) fillColor(x, y-1, oldC, newC);
	if(a[y+1][x]==oldC) fillColor(x, y+1, oldC, newC);
	if(a[y][x-1]==oldC) fillColor(x-1, y, oldC, newC);
	if(a[y][x+1]==oldC) fillColor(x+1, y, oldC, newC);


}


void putColor(int x1, int y1, char c){
	
	if(c==a[y1][x1]) return ;
	
	queue<int> x;
	queue<int> y;
	char current=a[y1][x1];
	a[y1][x1]=c;

	x.push(x1);
	y.push(y1);
	
	int curx, cury;
	while(!x.empty()){
		curx=x.front();
		cury=y.front();
		x.pop();
		y.pop();

		if(a[cury][curx-1]==current){
			x.push(curx-1);
			y.push(cury);
			a[cury][curx-1]=c;
		}

		if(a[cury][curx+1]==current){
			x.push(curx+1);
			y.push(cury);
			a[cury][curx+1]=c;
		}

		if(a[cury-1][curx]==current){
			x.push(curx);
			y.push(cury-1);
			a[cury-1][curx]=c;
		}

		if(a[cury+1][curx]==current){
			x.push(curx);
			y.push(cury+1);
			a[cury+1][curx]=c;
		}

	}

}

int main(){
	
	int chk=1;
	char q, c;
	int x1=0, y1=0, x2=0, y2=0;
	int m=0, n=0;
	char name[2560];

	while(chk){
		scanf("%c", &q);

		switch(q){
		case 'I':
			scanf("%d %d", &m, &n);
			setBoard(m, n);
			break;
		case 'C':
			setBoard(m, n);
			break;
		case 'L':
			scanf("%d %d %c", &x1, &y1, &c);
			drawingColor(x1, y1, x1, y1, c);
			break;
		case 'V':
			scanf("%d %d %d %c", &x1, &y1, &y2, &c);
			drawingColor(x1, y1, x1, y2, c);
			break;
		case 'H':
			scanf("%d %d %d %c", &x1, &x2, &y1, &c);
			drawingColor(x1, y1, x2, y1, c);
			break;
		case 'K':
			scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
			drawingColor(x1, y1, x2, y2, c);
			break;
		case 'F':
			scanf("%d %d %c", &x1, &y1, &c);
			putColor(x1, y1, c);
		//	fillColor(x1, y1, a[y1][x1], c);
			break;
		case 'S':
			scanf("%s", name);
			printBoard(m, n, name);
			break;
		case 'X':
			chk=0;
			//return 0;
			break;
		}
	}

	return 0;
}
