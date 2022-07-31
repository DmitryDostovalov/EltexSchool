#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"MyUtils.h"
#include"PersonalCard.h"

int PersonalCardClean(struct PersonalCard *Pc)
{
	int returnCode = RC_OK;
	if(StringClean(Pc->Name)) returnCode = RC_ERROR;
	if(StringClean(Pc->Surname)) returnCode = RC_ERROR;
	if(StringClean(Pc->Patronymic)) returnCode = RC_ERROR;
	if(StringClean(Pc->PhoneNumber)) returnCode = RC_ERROR;
	if(StringClean(Pc->Email)) returnCode = RC_ERROR;
	return returnCode;
}

int Match(const struct PersonalCard *Pc, const char *FindStr)
{
	if(strstr(Pc->Name, FindStr)) return MC_NAME;
	if(strstr(Pc->Surname, FindStr)) return MC_SURNAME;
	if(strstr(Pc->Patronymic, FindStr)) return MC_PATRONYMIC;
	if(strstr(Pc->PhoneNumber, FindStr)) return MC_PHONE;
	if(strstr(Pc->Email, FindStr)) return MC_EMAIL;
	return MC_NONE;
}

int PersonalCardSetup(struct PersonalCard *Pc,
	const char* Surname, const char* Name, const char* Patronymic,
	const char* Phone, const char* Email)
{
	int returnCode = RC_OK;
	if(NULL == Pc) return RC_ERROR;
	if(NULL != Name) returnCode = (StringCopy(Pc->Name, Name) ? RC_ERROR : RC_OK);
	if(NULL != Surname) returnCode = (StringCopy(Pc->Surname, Surname) ? RC_ERROR : RC_OK);
	if(NULL != Patronymic) returnCode = (StringCopy(Pc->Patronymic, Patronymic) ? RC_ERROR : RC_OK);
	if(NULL != Phone) returnCode = (StringCopy(Pc->PhoneNumber, Phone) ? RC_ERROR : RC_OK);
	if(NULL != Email) returnCode = (StringCopy(Pc->Email, Email) ? RC_ERROR : RC_OK);
	return returnCode;
}

int PersonalCardStatus(const struct PersonalCard *Pc)
{
	if(0 == strlen(Pc -> Name))
	{
		return PC_EMPTY;
	}
	return PC_FILLED;
}

int PersonalCardPrint(const struct PersonalCard *Pc)
{
	if(NULL == Pc) return RC_ERROR;
	if(PC_EMPTY == PersonalCardStatus(Pc))
	{
		printf("No person data\n");
		return RC_OK;
	}
	printf("Person: %s %s %s\n", Pc->Surname, Pc->Name, Pc->Patronymic);
	printf("Phone: %s, Email: %s\n", Pc->PhoneNumber, Pc->Email);
	return RC_OK;
}