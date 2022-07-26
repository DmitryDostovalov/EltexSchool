#include<stdio.h>

long sum(long a, long b, long c,
	long d, long e, long f, long g, long h)
{
	long sum = 0;
	sum = a+b+c+d+e+f+g+h;
	return sum;
}

int main()
{
	long result = 0;
	long a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8;
	result = sum(a, b, c, d, e, f, g, h);
	return 0;
}
