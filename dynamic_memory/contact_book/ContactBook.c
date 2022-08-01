#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"MyUtils.h"
#include"PersonalCard.h"
#include"ContactList.h"

enum ActionCodes
{
	AC_FIND_CONTACT = 1, AC_ADD_CONTACT, AC_EDIT_CONTACT, AC_DELETE_CONTACT, AC_EXIT, AC_MENU
};

void Fill(struct ContactList *Cl)
{
	Cl->Contacts = calloc(3, sizeof(struct PersonalCard));
	if(NULL == Cl->Contacts)
	{
		perror("Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	Cl->ContactsCount = 3;
	PersonalCardSetup(&(Cl->Contacts[0]), "Ivanov", "Ivan", "Ivanovich", "+79011234567", "ivanov@mailserver.com");
	PersonalCardSetup(&(Cl->Contacts[1]), "Petrov", "Ivan", "Sergeevich", "+79011234568", "petrov@mailserver.com");
	PersonalCardSetup(&(Cl->Contacts[2]), "Sidorov", "Eugeny", "Nikolaevich", "+79011234569", "sidorov@mailserver.com");
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

	if(NULL == fgets(buf, STRING_MAX_LEN, stdin))
	{
		perror("Input error!\n");
		exit(EXIT_FAILURE);
	}


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

int main()
{
	struct ContactList Cl;

	ContactListInit(&Cl);

	Fill(&Cl);

	int choice = AC_EXIT;

	while(1)
	{
		choice = Menu();
		if(AC_EXIT == choice) break;
		if(AC_FIND_CONTACT == choice) FindContacts(&Cl);
		if(AC_ADD_CONTACT == choice) AddContact(&Cl);
		if(AC_EDIT_CONTACT == choice) EditContact(&Cl);
		if(AC_DELETE_CONTACT == choice) DeleteContact(&Cl);
	}
	ContactListDestroy(&Cl);
	return 0;
}
