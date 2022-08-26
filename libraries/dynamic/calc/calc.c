#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"add.h"
#include"sub.h"
#include"mul.h"
#include"div.h"

#define STRING_MAX_LEN 20

enum ActionCodes
{
	AC_ADD = 1, AC_SUB, AC_MUL, AC_DIV, AC_EXIT, AC_MENU
};

void UserInput(const char* invite, char* buf)
{
	if((NULL == invite) || (NULL == buf)) return;

	printf("%s", invite);
	fgets(buf, STRING_MAX_LEN, stdin);

	char* pos = NULL;
	pos = strchr(buf, 10);
	if(NULL != pos) *pos = 0;

	pos = NULL;
	pos = strchr(buf, 13);
	if(NULL != pos) *pos = 0;
}

int Menu()
{
	int returnCode = AC_MENU;
	char buf[STRING_MAX_LEN];
	int choice = AC_MENU;

	printf("Menu:\n");
	printf("%d - Addition\n", AC_ADD);
	printf("%d - Substraction\n", AC_SUB);
	printf("%d - Multiplication\n", AC_MUL);
	printf("%d - Division\n", AC_DIV);
	printf("%d - Exit\n\n", AC_EXIT);

	UserInput("Select action: ", buf);
	choice = atoi(buf);

	switch(choice)
	{
		case AC_ADD: returnCode = AC_ADD; break;
		case AC_SUB: returnCode = AC_SUB; break;
		case AC_MUL: returnCode = AC_MUL; break;
		case AC_DIV: returnCode = AC_DIV; break;
		case AC_EXIT: returnCode = AC_EXIT; break;
		default: returnCode = AC_MENU; break;
	}
	return returnCode;
}

int main()
{
	double a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	int choice = AC_EXIT;
	while(1)
	{
		choice = Menu();
		if(AC_EXIT == choice) break;
		if(AC_ADD == choice) printf("%.2f + %.2f = %.2f\n", a, b, my_add(a,b));
		if(AC_SUB == choice) printf("%.2f - %.2f = %.2f\n", c, d, my_sub(c,d));
		if(AC_MUL == choice) printf("%.2f * %.2f = %.2f\n", a, e, my_mul(a,e));
		if(AC_DIV == choice) printf("%.2f / %.2f = %.2f\n", f, b, my_div(f,b));
	}
	return 0;
}
