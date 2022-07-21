#include<stdio.h>

#define N 10

int SetSubmatrix(int(*)[N], unsigned int, unsigned int, int);

int main()
{
	int matrix[N][N];
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			matrix[i][j] = 0;
		}
	}

	SetSubmatrix(matrix, N, N, 1);

	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}

int SetSubmatrix(int (*matrix)[N], unsigned int size, unsigned int level, int initial_value)
{
	if(1 == level)
	{
		matrix[(size-1)/2][(size-1)/2] = initial_value;
		return initial_value;
	}
	if(2 == level)
	{
		matrix[size/2-1][size/2-1] = initial_value++;
		matrix[size/2-1][size/2] = initial_value++;
		matrix[size/2][size/2] = initial_value++;
		matrix[size/2][size/2-1] = initial_value;
		return initial_value;
	}

	int i = 0;
	int j = 0;

	int bound1 = (size-level)/2;
	int bound2 = size-1-bound1;

	i = bound1;
	for(j = bound1; j < bound2; ++j)
	{
		matrix[i][j] = initial_value++;
	}
	j = bound2;
	for(i = bound1; i < bound2; ++i)
	{
		matrix[i][j] = initial_value++;
	}
	i = bound2;
	for(j = bound2; j > bound1; --j)
	{
		matrix[i][j] = initial_value++;
	}
	j = bound1;
	for(i = bound2; i > bound1; --i)
	{
		matrix[i][j] = initial_value++;
	}
	return SetSubmatrix(matrix, N, level-2, initial_value);
}
