#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"MyUtils.h"
#include"PersonalCard.h"
#include"ContactList.h"

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
		printf("Card %d:\n", count+1);
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
		printf("Ok!\n");
		printf("New information:\n");
		PersonalCardPrint(Pc);

	}
	else
	{
		printf("Unable to add a contact! No blank personal cards.\n");
	}
}

void EditContact(struct ContactList* Cl)
{
	if(NULL == Cl) return;

	char Name[STRING_MAX_LEN];
	char Surname[STRING_MAX_LEN];
	char Patronymic[STRING_MAX_LEN];
	char PhoneNumber[STRING_MAX_LEN];
	char Email[STRING_MAX_LEN];

	char buf[STRING_MAX_LEN];

	printf("Enter a number of contact for edit (1 - %d):", MAX_CONTACTS_COUNT);
	UserInput("", buf );
	int pos = -1;
	pos = atoi(buf) - 1;
	if((pos >= 0)&&(pos < MAX_CONTACTS_COUNT))
	{
		if(PC_EMPTY == PersonalCardStatus(&(Cl->Contacts[pos])))
		{
			printf("This card is empty!\n");
			return;
		}
		printf("Current information:\n");
		PersonalCardPrint(&(Cl->Contacts[pos]));

		printf("Enter  new data (empty string for keep old value):\n");
		UserInput("Surname:", Surname);
		UserInput("Name:", Name);
		UserInput("Patronymic:", Patronymic);
		UserInput("PhoneNumber:", PhoneNumber);
		UserInput("Email:", Email);
		PersonalCardSetup(&(Cl->Contacts[pos]),
			((0 != strlen(Surname)) ? Surname : NULL),
			((0 != strlen(Name)) ? Name : NULL),
			((0 != strlen(Patronymic)) ? Patronymic : NULL),
			((0 != strlen(PhoneNumber)) ? PhoneNumber : NULL),
			((0 != strlen(Email)) ? Email : NULL));
		printf("Ok\n");
		printf("New information:\n");
		PersonalCardPrint(&(Cl->Contacts[pos]));

	}
	else
	{
		printf("Uncorrect number of contact!\n");
	}
}


void DeleteContact(struct ContactList* Cl)
{
	if(NULL == Cl) return;

	char buf[STRING_MAX_LEN];

	printf("Enter a number of contact for delete (1 - %d):", MAX_CONTACTS_COUNT);
	UserInput("", buf );
	int pos = -1;
	pos = atoi(buf) - 1;
	if((pos >= 0)&&(pos < MAX_CONTACTS_COUNT))
	{
		if(PC_EMPTY == PersonalCardStatus(&(Cl->Contacts[pos])))
		{
			printf("This card is empty!\n");
			return;
		}
		PersonalCardClean(&(Cl->Contacts[pos]));
		printf("Ok\n");
	}
	else
	{
		printf("Uncorrect number of contact!\n");
	}
}