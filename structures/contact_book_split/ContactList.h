#ifndef _CONTACTLIST_H_
#define _CONTACTLIST_H_

#include"MyUtils.h"
#include"PersonalCard.h"
#include"ContactList.h"

struct ContactList
{
	struct PersonalCard Contacts[MAX_CONTACTS_COUNT];
};

const struct PersonalCard* Find(const struct ContactList *Cl, const char *FindStr);

void FindContacts(struct ContactList* Cl);

void AddContact(struct ContactList* Cl);

void EditContact(struct ContactList* Cl);

void DeleteContact(struct ContactList* Cl);

#endif
