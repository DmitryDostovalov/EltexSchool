#include<stdio.h>

int main()
{
	int value = -1234;
	printf("Dec: %d, Hex: 0x%X\nBytes: ", value, value);
	for(int i = 0; i < sizeof(value); ++i)
	{
		int byte = value & 0xFF;
		if(byte < 0xF) printf("0");
		printf("%X ", byte);
		value = value>>8;
	}
	return 0;
}
