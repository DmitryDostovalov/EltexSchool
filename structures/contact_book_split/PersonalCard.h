#ifndef _PERSONALCARD_H_
#define _PERSONALCARD_H_

#include"MyUtils.h"

struct PersonalCard
{
	char Name[STRING_MAX_LEN];
	char Surname[STRING_MAX_LEN];
	char Patronymic[STRING_MAX_LEN];
	char PhoneNumber[STRING_MAX_LEN];
	char Email[STRING_MAX_LEN];
};

enum PersonalCardStatus
{
	PC_EMPTY, PC_FILLED
};

enum MatchCodes
{
	MC_NONE = 0, MC_NAME, MC_SURNAME, MC_PATRONYMIC, MC_PHONE, MC_EMAIL
};

int PersonalCardClean(struct PersonalCard *Pc);

int Match(const struct PersonalCard *Pc, const char *FindStr);

int PersonalCardSetup(struct PersonalCard *Pc,
	const char* Surname, const char* Name, const char* Patronymic,
	const char* Phone, const char* Email);

int PersonalCardStatus(const struct PersonalCard *Pc);

int PersonalCardPrint(const struct PersonalCard *Pc);

#endif