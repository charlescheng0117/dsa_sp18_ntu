#include <stdio.h>
#include <time.h>
//#include <windows.h>

#define M 10000
#define N 20000

int array[M][N];

int rowSum(){
	int total=0;
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			total+=array[i][j];
	return total;
}

int colSum(){
	int total=0;
	for (int j=0; j<N; j++)
		for (int i=0; i<M; i++)
			total+=array[i][j];
	return total;
}

int main(){
	clock_t tic;

	tic=clock();
	int total01=rowSum();
	printf("Time for rowSum() = %f sec\n", (clock()-tic)/(double)CLOCKS_PER_SEC);

	tic=clock();
	int total02=colSum();
	printf("Time for colSum() = %f sec\n", (clock()-tic)/(double)CLOCKS_PER_SEC);

}