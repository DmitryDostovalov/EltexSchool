#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"MyUtils.h"

int StringClean(char *Str)
{
	if(NULL == Str) return RC_ERROR;
	memset(Str, 0, STRING_MAX_LEN);
	return RC_OK;
}

int StringCopy(char *Dest, const char *Src)
{
	if(NULL == Src || NULL == Dest) return RC_ERROR;
	memset(Dest, 0, STRING_MAX_LEN);
	memcpy(Dest, Src, STRING_MAX_LEN);
	return RC_OK;
}

void UserInput(const char* invite , char* buf)
{
	if((NULL == invite) || (NULL == buf)) return;

	printf("%s ", invite);
	if(NULL == fgets(buf, STRING_MAX_LEN, stdin))
	{
		perror("Input error!\n");
		exit(EXIT_FAILURE);
	}

	char* pos = NULL;
	pos = strchr(buf, 10);
	if(NULL != pos) *pos = 0;

	pos = NULL;
	pos = strchr(buf, 13);
	if(NULL != pos) *pos = 0;
}
