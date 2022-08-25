#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define CUSTOMER_COUNT 30
#define SUPPLIER_COUNT 20
#define SHOP_COUNT 50

int shop[SHOP_COUNT];
int happy_customer_count = 0;
int happy_supplier_count = 0;

pthread_mutex_t mutex[SHOP_COUNT];
pthread_mutex_t m1;
pthread_cond_t cond1;

void shop_init()
{
	srand(time(NULL));
	for(int i = 0; i < SHOP_COUNT; ++i)
	{
		shop[i] = rand()%200 + 900;
	}
}

void shop_info()
{
	for(int i = 0; i < SHOP_COUNT; ++i)
	{
		printf("In shop #%d quantity of goods: %d.\n", i, shop[i]);
	}
}

void mutex_init()
{
	for(int i = 0; i < SHOP_COUNT; ++i)
	{
		if(0 != pthread_mutex_init(&mutex[i], NULL))
		{
			perror("Error on mutex initialization! Exit.\n");
			exit(EXIT_FAILURE);
		}
	}
	if(0 != pthread_mutex_init(&m1, NULL))
	{
		perror("Error on mutex initialization! Exit.\n");
		exit(EXIT_FAILURE);
	}

}

void mutex_deinit()
{
	for(int i = 0; i < SHOP_COUNT; ++i)
	{
		if(0 != pthread_mutex_destroy(&mutex[i]))
		{
			perror("Error on mutex destroy!\n");
		}
	}
	if(0 != pthread_mutex_destroy(&m1))
	{
		perror("Error on mutex destroy!\n");
	}
}

void* customer(void* number)
{
	int* num = (int*)number;

	int required_count = (rand()%20)*100 + 9000;

	printf("I'm customer #%d, my requirement is %d goods.\n", *num, required_count);

	int try_cnt = 0;
	int success_cnt = 0;
	while(required_count > 0)
	{
		for(int i = 0; i < SHOP_COUNT; ++i)
		{
			try_cnt++;
			if(0 == pthread_mutex_trylock(&mutex[i]))
			{
				if(shop[i]>0)
				{
					success_cnt++;
					if(shop[i] >= required_count)
					{
						shop[i] = shop[i] - required_count;
						required_count = 0;
					}
					else
					{
						required_count = required_count - shop[i];
						shop[i] = 0;
					}
					pthread_mutex_unlock(&mutex[i]);
					printf("Customer #%d buy in shop #%d, now his requirement is %d goods.\n", *num, i, required_count);
					sleep(1);
				}
				else pthread_mutex_unlock(&mutex[i]);
			}
			if(0 == required_count)
			{
				pthread_mutex_lock(&m1);
				happy_customer_count++;
				if(happy_customer_count >= CUSTOMER_COUNT)
				{
					pthread_cond_broadcast(&cond1);
				}
				pthread_mutex_unlock(&m1);
				printf("Customer #%d has completed the shopping. Attempts to enter the store: %d, successful shopping: %d.\n", *num, try_cnt, success_cnt);
				break;
			}
		}
		sleep(0.001);
	}
	return number;
}

void* supplier(void* number)
{
	int* num = (int*)number;

	int supply_count = (rand()%5)*50 + 450;
	printf("I'm supplier #%d, i can delivery %d goods\n", *num, supply_count);

	int try_cnt = 0;
	int success_cnt = 0;
	struct timespec ts;
	int finished = 0;
	while(0 == finished)
	{
		for(int i = 0; i < SHOP_COUNT && 0 == finished; ++i)
		{
			try_cnt++;
			if(0 == pthread_mutex_trylock(&mutex[i]))
			{
				success_cnt++;
				shop[i] = shop[i] + supply_count;
				pthread_mutex_unlock(&mutex[i]);
				printf("Supplier #%d brought the goods to shop #%d, now then are %d goods.\n", *num, i, shop[i]);
			}
			pthread_mutex_lock(&m1);
			if(happy_customer_count < CUSTOMER_COUNT)
			{
				clock_gettime(CLOCK_REALTIME, &ts);
				ts.tv_sec += 1;
				if(0 == pthread_cond_timedwait(&cond1, &m1, &ts))
				{
					happy_supplier_count++;
					printf("Supplier #%d has completed the delivery (signal received). Attempts to enter the store: %d, successful delivery: %d.\n", *num, try_cnt, success_cnt);
					finished = 1;
				}
			}
			else
			{
				happy_supplier_count++;
				printf("Supplier #%d has completed the delivery. Attempts to enter the store: %d, successful delivery: %d.\n", *num, try_cnt, success_cnt);
				finished = 1;
			}
			pthread_mutex_unlock(&m1);
		}
	}
	return number;
}

int main()
{
	srand(time(NULL));
	mutex_init();
	pthread_cond_init(&cond1, NULL);
	happy_customer_count = 0;
	happy_supplier_count = 0;

	int customer_id[CUSTOMER_COUNT];
	for(int i = 0; i < CUSTOMER_COUNT; ++i)
	{
		customer_id[i] = i + 1;
	}

	int supplier_id[SUPPLIER_COUNT];
	for(int i = 0; i < SUPPLIER_COUNT; ++i)
	{
		supplier_id[i] = i + 1;
	}

	pthread_t customer_tid[CUSTOMER_COUNT];
	pthread_t supplier_tid[SUPPLIER_COUNT];

	int* customer_status[CUSTOMER_COUNT];
	int* supplier_status[SUPPLIER_COUNT];

	shop_init();
	printf("\nInitial condition of stores:\n");
	shop_info();

	for(int i = 0; i < CUSTOMER_COUNT; ++i)
	{
		pthread_create(&customer_tid[i], NULL, customer, (void*)&customer_id[i]);
	}

	for(int i = 0; i < SUPPLIER_COUNT; ++i)
	{
		pthread_create(&supplier_tid[i], NULL, supplier, (void*)&supplier_id[i]);
	}

	for(int i = 0; i < CUSTOMER_COUNT; ++i)
	{
		pthread_join(customer_tid[i], (void*)&customer_status[i]);
		if(customer_status[i] != &customer_id[i])
		{
			printf("Uncorrect the return value from customer #%d!\n", customer_id[i]);
		}
	}

	for(int i = 0; i < SUPPLIER_COUNT; ++i)
	{
		pthread_join(supplier_tid[i], (void*)&supplier_status[i]);
		if(supplier_status[i] != &supplier_id[i])
		{
			printf("Uncorrect the return value from supplier #%d!\n", supplier_id[i]);
		}

	}

	printf("\nHappy customer count: %d\n", happy_customer_count);
	printf("Happy supplier count: %d\n", happy_supplier_count);
	printf("\nThe needs of all customers are satisfied. Final condition of stores:\n");
	shop_info();

	pthread_cond_destroy(&cond1);
	mutex_deinit();
	exit(EXIT_SUCCESS);
}
