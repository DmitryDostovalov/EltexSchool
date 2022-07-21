#include<stdio.h>
#include<stdlib.h>

#define N 10

void PrintBytes(int number)
{
	for(int i = sizeof(number)-1; i >= 0; --i)
	{
		int byte = (number >> (i << 3)) & 0xFF;
		if(byte < 0xF) printf("0");
		printf("%X ", byte);
	}
}


int main()
{
	char buf[N];
	int number = 0;
	int pos = 0;
	unsigned int new_byte = 0;


	printf("Enter a number: ");
	fgets(buf, N, stdin);
	number = atoi(buf);
	printf("Number: %d, 0x%X(HEX), bytes: ", number, number);
	PrintBytes(number);

	printf("\nEnter a number of byte (0 - 3) for change: ");
	fgets(buf, N, stdin);
	pos = atoi(buf);
	if((pos < 0)||(pos > 3))
	{
		printf("Uncorrect position. Exit");
		return -1;
	}

	printf("Enter a new byte value (0 - 255): ");
	fgets(buf, N, stdin);
	new_byte = atoi(buf);
	if((new_byte < 0)||(new_byte > 255))
	{
		printf("Uncorrect value. Exit");
		return -1;
	}

	printf("New byte: ");
	if(new_byte < 0xF) printf("0");
	printf("%X,  %d(DEC) in pos: %d", new_byte, new_byte, pos);

	number = (number & ~(0xFF << (pos*8))) | (new_byte << (pos*8));

	printf("\nNew number: %d, 0x%X(HEX), bytes: ", number, number);
	PrintBytes(number);

	return 0;
}
