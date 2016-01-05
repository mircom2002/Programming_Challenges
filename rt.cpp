#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    clock_t begin = clock();

	    // do something...
	for(int i=0;i<10000000;i++){}
    clock_t end = clock();
    double msec = 1000*(end - begin) / CLOCKS_PER_SEC;

	printf("%f", msec);
}

