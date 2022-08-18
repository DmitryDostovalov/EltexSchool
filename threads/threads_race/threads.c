#include<pthread.h>
#include<stdio.h>

#define THREADS_COUNT 5

int a = 0;

void* func(void* arg)
{
	int tmp;
	for(int i = 0; i < 1e6; ++i)
	{
		tmp = a;
		tmp++;
		a = tmp;
	}
	pthread_exit(0);
}

int main()
{
	pthread_t tid[THREADS_COUNT];
	void* status[THREADS_COUNT];
	int i, i1;
	printf("Initial value, a = %d\n", a);
	for(i = 0; i < THREADS_COUNT; ++i)
	{
		pthread_create(&tid[i], NULL, func, NULL);
	}
	for(i1 = 0; i1 < THREADS_COUNT; ++i1)
	{
		pthread_join(tid[i1], &status[i1]);
	}
	printf("Final value, a = %d\n", a);
	return 0;
}
