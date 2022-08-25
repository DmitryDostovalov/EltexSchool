#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1;

int a = 0;

void* inc_func(void* arg)
{
	pthread_mutex_lock(&m1);
	printf("Inc_func, a = %d\n", a);
	a++;
	if(a >= 2) pthread_cond_signal(&cond1);
	printf("Inc_func, a = %d\n", a);
	a++;
	if(a >= 2) pthread_cond_signal(&cond1);
	pthread_mutex_unlock(&m1);
}

void* observer_func(void* arg)
{
	int retcode;
	pthread_mutex_lock(&m1);

	while(a < 3)
	{
		retcode = pthread_cond_wait(&cond1, &m1);
		printf("In obs func, loop, a = %d, retcode = %d\n", a, retcode);
		sleep(0.001);
	}
	printf("Observer_func, a = %d, retcode = %d\n", a, retcode);
	pthread_mutex_unlock(&m1);
}

int main()
{
	pthread_cond_init(&cond1, NULL);
	pthread_t tid[3];
	void* status[3];

	pthread_create(&tid[0], NULL, inc_func, NULL);
	pthread_create(&tid[1], NULL, observer_func, NULL);
	pthread_create(&tid[2], NULL, inc_func, NULL);


	pthread_join(tid[0], &status[0]);
	pthread_join(tid[1], &status[1]);
	pthread_join(tid[2], &status[2]);

	printf("Cond var destroyed with result: %d\n", pthread_cond_destroy(&cond1));
	pthread_mutex_destroy(&m1);
	exit(EXIT_SUCCESS);
}
