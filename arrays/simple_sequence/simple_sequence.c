#include<stdio.h>

#define N 10

int main()
{
	int array[N][N];
	for(int i = 0; i < N*N; ++i)
	{
		*((int*)array+i) = i+1;
	}
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			printf("%3d ", array[i][j]);
		}
		printf("\n");
	}
	return 0;
}
