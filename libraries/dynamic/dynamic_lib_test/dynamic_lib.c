#include"dynamic_lib.h"
#include<stdio.h>

int add = 10;

int my_func(int arg)
{
	printf("Arg = %d\n", arg);
	arg += add;
	printf("New arg = %d\n", arg);
	return arg;
}
