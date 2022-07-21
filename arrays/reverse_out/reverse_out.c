#include<stdio.h>
#include<stdlib.h>

#define N 10
#define BUF_SIZE 5

int main()
{
	int array[N];
	char buf[BUF_SIZE];
	printf("Enter the items (0 - 9999) of array (%d):\n", N);

	for(int i = 0; i < N; ++i)
	{
		fgets(buf, BUF_SIZE, stdin);
		array[i] = atoi(buf);
	}
	for(int i = N-1; i >= 0;  --i)
	{
		printf("%4d ", array[i]);
	}
	return 0;
}
