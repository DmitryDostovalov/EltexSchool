#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_MAX_LEN 40
#define MAX_CONTACTS_COUNT 10

struct PersonalCard
{
	char Name[STRING_MAX_LEN];
	char Surname[STRING_MAX_LEN];
	char Patronymic[STRING_MAX_LEN];
	char PhoneNumber[STRING_MAX_LEN];
	char Email[STRING_MAX_LEN];
};

struct ContactList
{
	struct PersonalCard Contacts[MAX_CONTACTS_COUNT];
};

enum ReturnCodes
{
	RC_ERROR = -1, RC_OK = 0
};

enum MatchCodes
{
	MC_NONE = 0, MC_NAME, MC_SURNAME, MC_PATRONYMIC, MC_PHONE, MC_EMAIL
};

enum ActionCodes
{
	AC_FIND_CONTACT=1, AC_ADD_CONTACT, AC_EDIT_CONTACT, AC_DELETE_CONTACT, AC_EXIT, AC_MENU
};

enum PersonalCardStatus
{
	PC_EMPTY, PC_FILLED
};

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

const struct PersonalCard* Find(const struct ContactList *Cl, const char *FindStr)
{
	// Не будет работать в многопоточном варианте
	const static struct ContactList *ClPrev = NULL;
	static int NextIndexForFind = 0;

	if(Cl != ClPrev)
	{
		ClPrev = Cl;
		NextIndexForFind = 0;
	}

	if((NULL == Cl) || (NULL == FindStr)) return NULL;

	const struct PersonalCard *Pc = NULL;
	while(NextIndexForFind < MAX_CONTACTS_COUNT)
	{
		Pc = &(Cl->Contacts[NextIndexForFind]);
		++NextIndexForFind;
		if(Match(Pc, FindStr) != MC_NONE) return Pc;
	}
	return NULL;
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

void Fill(struct ContactList *Cl)
{
	for(int i = 0; i < MAX_CONTACTS_COUNT; ++i)
	{
		PersonalCardClean(&(Cl->Contacts[i]));
	}
	PersonalCardSetup(&(Cl->Contacts[4]), "Ivanov", "Ivan", "Ivanovich", "+79011234567", "user@mailserver.com");
	PersonalCardSetup(&(Cl->Contacts[1]), "Petrov", "Ivan", "Sergeevich", "+79011234568", "user1@mailserver.com");
	PersonalCardSetup(&(Cl->Contacts[7]), "Sidorov", "Eugeny", "Nikolaevich", "+79011234569", "user2@mailserver.com");
}

int Menu()
{
	int returnCode = AC_MENU;
	char buf[STRING_MAX_LEN];
	int choice = AC_MENU;

	printf("***********************************\n");
	printf("*         My Contact List         *\n");
	printf("***********************************\n\n");
	printf("Menu:\n");

	printf("%d - Find contact\n", AC_FIND_CONTACT);
	printf("%d - Add contact\n", AC_ADD_CONTACT);
	printf("%d - Edit contact\n", AC_EDIT_CONTACT);
	printf("%d - Delete contact\n", AC_DELETE_CONTACT);
	printf("%d - Exit\n\n", AC_EXIT);

	printf("Select action: ");

	fgets(buf, STRING_MAX_LEN, stdin);
	choice = atoi(buf);

	switch(choice)
	{
		case AC_FIND_CONTACT: returnCode = AC_FIND_CONTACT; break;
		case AC_ADD_CONTACT: returnCode = AC_ADD_CONTACT; break;
		case AC_EDIT_CONTACT: returnCode = AC_EDIT_CONTACT; break;
		case AC_DELETE_CONTACT: returnCode = AC_DELETE_CONTACT; break;
		case AC_EXIT: returnCode = AC_EXIT; break;
		default: returnCode = AC_MENU; break;
	}
	return returnCode;
}

void UserInput(const char* invite , char* buf)
{
	if((NULL == invite) || (NULL == buf)) return;

	printf("%s ", invite);
	fgets(buf, STRING_MAX_LEN, stdin);

	char* pos = NULL;
	pos = strchr(buf, 10);
	if(NULL != pos) *pos = 0;

	pos = NULL;
	pos = strchr(buf, 13);
	if(NULL != pos) *pos = 0;
}

void FindContacts(struct ContactList* Cl)
{
	if(NULL == Cl) return;

	char buf[STRING_MAX_LEN];

	UserInput("Enter text for search:", buf);

	const struct PersonalCard *Pc = NULL;
	int count = 0;
	Find(NULL, NULL);
	while(NULL != (Pc = Find(Cl, buf)))
	{
		PersonalCardPrint(Pc);
		printf("\n");
		count++;
	}
	printf("Find: %d contacts\n\n", count);
}

void AddContact(struct ContactList* Cl)
{
	if(NULL == Cl) return;

	char Name[STRING_MAX_LEN];
	char Surname[STRING_MAX_LEN];
	char Patronymic[STRING_MAX_LEN];
	char PhoneNumber[STRING_MAX_LEN];
	char Email[STRING_MAX_LEN];

	struct PersonalCard *Pc = NULL;
	for(int i = 0; i < MAX_CONTACTS_COUNT; ++i)
	{
		if(PC_EMPTY == PersonalCardStatus(&(Cl->Contacts[i])))
		{
			Pc = &(Cl->Contacts[i]);
			break;
		}
	}

	if(NULL != Pc)
	{
		printf("New card:\n");
		UserInput("Surname:", Surname);
		UserInput("Name:", Name);
		UserInput("Patronymic:", Patronymic);
		UserInput("PhoneNumber:", PhoneNumber);
		UserInput("Email:", Email);
		PersonalCardSetup(Pc, Surname, Name, Patronymic, PhoneNumber, Email);
	}
	else
	{
		printf("Unable to add a contact! No blank personal cards.\n");
	}
}


int main()
{
	/*struct PersonalCard Pc;
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
	if(Match(&Pc, "+7913")!=MC_NONE) printf("+7913 matched\n");*/

	/*struct ContactList Cl;
	Fill(&Cl);

	printf("List of contacts: \n");
	for(int i = 0; i < MAX_CONTACTS_COUNT; ++i)
	{
		printf("\nContact %d:\n", i+1);
		PersonalCardPrint(&(Cl.Contacts[i]));
	}

	printf("Find testing. Match for \"Ivan\"\n");
	const struct PersonalCard *Pc = NULL;
	int count = 0;
	while(NULL != (Pc = Find(&Cl, "Ivan")))
	{
		PersonalCardPrint(Pc);
		printf("\n");
		count++;
	}
	printf("Find: %d contacts\n\n", count);

	printf("Find testing. Match for \"user@\"\n");
	Find(NULL, NULL); // reset find
	Pc = NULL;
	count = 0;
	while(NULL != (Pc = Find(&Cl, "user@")))
	{
		PersonalCardPrint(Pc);
		printf("\n");
		count++;
	}
	printf("Find: %d contacts\n\n", count);*/

	struct ContactList Cl;
	Fill(&Cl);

/*	printf("List of contacts: \n");
	for(int i = 0; i < MAX_CONTACTS_COUNT; ++i)
	{
		printf("\nContact %d:\n", i+1);
		PersonalCardPrint(&(Cl.Contacts[i]));
	}

	printf("Find testing. Match for \"\"\n");
	const struct PersonalCard *Pc = NULL;
	int count = 0;
	while(NULL != (Pc = Find(&Cl, "")))
	{
		PersonalCardPrint(Pc);
		printf("\n");
		count++;
	}
	printf("Find: %d contacts\n\n", count);
*/
	int choice = AC_EXIT;

	while(1)
	{
		choice = Menu();
		if(AC_EXIT == choice) break;
		if(AC_FIND_CONTACT == choice) FindContacts(&Cl);
		if(AC_ADD_CONTACT == choice) AddContact(&Cl);
	}
	return 0;
}
