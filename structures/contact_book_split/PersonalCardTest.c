#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"MyUtils.h"
#include"PersonalCard.h"

int main()
{
	struct PersonalCard Pc;
	PersonalCardClean(&Pc);
	printf("Empty card:\n");
	PersonalCardPrint(&Pc);
	PersonalCardSetup(&Pc, "Ivanov", "Ivan", "Ivanovich", "+79011234567", "user@mailserver.com");
	printf("\n\nFilled card:\n");
	PersonalCardPrint(&Pc);

	if(Match(&Pc, "Ivan")!=MC_NONE) printf("Ivan matched\n");
	if(Match(&Pc, "Iv")!=MC_NONE) printf("Iv matched\n");
	if(Match(&Pc, "Dmitry")!=MC_NONE) printf("Dmitry matched\n");
	if(Match(&Pc, "+7901")!=MC_NONE) printf("+7901 matched\n");
	if(Match(&Pc, "+7913")!=MC_NONE) printf("+7913 matched\n");

	return 0;
}