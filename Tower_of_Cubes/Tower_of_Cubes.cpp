#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

char d_array[6][10]={"front", "back", "left", "right", "top", "bottom"};

class face{
public:
	face(int n, int, int, int);
	int top;
	int bottom;
	int direction;
	int height;
	int layer;
	face* top_face;
};

face::face(int n, int t, int b, int r){
	top=t;
	bottom=b;
	direction=r;
	layer=n;
	height=0;
}

class qube{
public:
	qube(int, int, int, int , int ,int , int);
	face *f[6];
	int findMax(int);
};

qube::qube(int n, int front, int rear, int left, int right, int top, int bottom){
	f[0]=new face(n, front, rear, 0);
	f[1]=new face(n, rear, front, 1);
	f[2]=new face(n, left, right, 2);
	f[3]=new face(n, right, left, 3);
	f[4]=new face(n, top, bottom, 4);
	f[5]=new face(n, bottom, top, 5);
}

int qube::findMax(int temp){ // height가 최대인 face번호 반환
	int max=-1;
	int num=-1;
	for(int i=0;i<6;i++){
		if(f[i]->bottom==temp)
			if(f[i]->height>max){
				max=f[i]->height;
				num=i;
			}
	}
	return num;
}

void print(vector<qube*> graph, int n, int s){

	face *temp=graph[n]->f[s]->top_face;
	if(temp!=NULL)
		print(graph, temp->layer, temp->direction);	
	printf("%d %s\n", n+1 ,d_array[s]);

}

int main(){

	/*
		1. 입력 : 정육면체의 개수, 0일시 종료
				앞, 뒤, 왼쪽, 오른쪽, 위, 아래 색 입력받음

		2. 출력 : 최대 높이, 위를 향하는 면의 색 들.

		3. how to?
			우선 무게순으로 입력받는다.

			앞뒤, 뒤앞, 왼쪽오른쪽, 오른쪽왼쪽, 위아래, 아래위 간선 생성(차례대로, 0, 1, 2, 3, 4, 5)
			(유향그래프), 총 경우의 수 6가지

			중요한 것은 한 면을 바닥에 놓았을때 위에 올 수 있는 정육면체의 수가 아닐까?

			1번째 입력 - 0, 1, 2, 3, 4, 5 - 0개

			2번째 입력 - 0 - 1개, 1 - 1개, 2 - 0개, 3 - 0개, 4 - 1개, 5 - 1개

			3번째 입력 - 0 - 2개, 1 - 1개, 2 - 0개, 3 - 2개, 4 - 0개, 5 - 0개

			...

			한 면에 대한 높이 값을 구할 때까지 위로 올라가는 탐색 과정을 거침.

			- 간선에 height값을 두어서 .

			Vector 이용, random access 를 통해 뒤에서부터 차례로 앞의 값으로 접근.
	*/
	int num;
	int f, b, l, r, u, d;
	int T=0;
	while(1){
		vector<qube*> graph;
		scanf("%d", &num);
		if(!num) break;
		for(int i=0;i<num;i++){
			scanf("%d %d %d %d %d %d", &f, &b, &l, &r, &u, &d);
			qube *temp= new qube(i, f, b, l, r, u, d);

			int size=graph.size()-1;
			int current;
			int temp_max;
			int max;
			for(int j=0;j<6;j++){
				max=-1;
				face* temp_face=NULL;
				for(int k=size;k>=0;k--){
					//temp->face[j] <- j번째 정점에 대한 값
					current=graph[k]->findMax(temp->f[j]->top);
					//cout << current << endl;
					if(current==-1) continue;
					//cout << "asf"<< current <<endl;
					if(graph[k]->f[current]->height>max){
						max=graph[k]->f[current]->height;
						temp_face=graph[k]->f[current];
					}
				}
				//cout << "adf" << endl;
				temp->f[j]->height=max+1;
				temp->f[j]->top_face=temp_face;
			}	
			graph.push_back(temp);
		}


		int size=graph.size();
		int current_max=-1;
		int num_of_cube=0;
		int face_of_cube=0;
		for(int i=0;i<size;i++){
			for(int j=0;j<6;j++){
				//cout << i << "번째 " << j << "위치 " << graph[i]->f[j]->height << endl;
				if(graph[i]->f[j]->height>current_max){
					current_max=graph[i]->f[j]->height;
					num_of_cube=i;
					face_of_cube=j;
				}
			}
		}
		T++;
		printf("Case #%d\n", T);
		printf("%d\n", current_max+1);
		print(graph, num_of_cube, face_of_cube);
		printf("\n");
	}


	return 0;
}
