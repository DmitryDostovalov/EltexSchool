#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"MyUtils.h"
#include"PersonalCard.h"
#include"ContactList.h"

void Fill(struct ContactList *Cl)
{
	Cl->Contacts = calloc(3, sizeof(struct PersonalCard));
	Cl->ContactsCount = 3;
	PersonalCardSetup(&(Cl->Contacts[0]), "Ivanov", "Ivan", "Ivanovich", "+79011234567", "ivanov@mailserver.com");
	PersonalCardSetup(&(Cl->Contacts[1]), "Petrov", "Ivan", "Sergeevich", "+79011234568", "petrov@mailserver.com");
	PersonalCardSetup(&(Cl->Contacts[2]), "Sidorov", "Eugeny", "Nikolaevich", "+79011234569", "sidorov@mailserver.com");
}

int main()
{
	struct ContactList Cl;
	ContactListInit(&Cl);

	Fill(&Cl);

	printf("List of contacts: \n");
	for(int i = 0; i < Cl.ContactsCount; ++i)
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

	printf("Find testing. Match for \"@mailserver\"\n");
	Find(NULL, NULL); // reset find
	Pc = NULL;
	count = 0;
	while(NULL != (Pc = Find(&Cl, "@mailserver")))
	{
		PersonalCardPrint(Pc);
		printf("\n");
		count++;
	}
	printf("Find: %d contacts\n\n", count);

	printf("Find testing. Match for \"\"\n");
	Find(NULL, NULL); // reset find
	Pc = NULL;
	count = 0;
	while(NULL != (Pc = Find(&Cl, "")))
	{
		PersonalCardPrint(Pc);
		printf("\n");
		count++;
	}
	printf("Find: %d contacts\n\n", count);

	ContactListDestroy(&Cl);
	return 0;
}
