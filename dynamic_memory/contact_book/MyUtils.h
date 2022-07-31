#ifndef _MYUTILS_H_
#define _MYUTILS_H_

#define STRING_MAX_LEN 40
#define MAX_CONTACTS_COUNT 10

enum ReturnCodes
{
	RC_ERROR = -1, RC_OK = 0
};

int StringClean(char *Str);

int StringCopy(char *Dest, const char *Src);

void UserInput(const char* invite , char* buf);

#endif