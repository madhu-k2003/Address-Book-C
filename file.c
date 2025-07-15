/*
Description : This is a simple command-line Address Book application written in C. It allows users to:
.Add new contacts
.Edit existing contacts
.Search for contacts
.Delete contacts
.Load and save contacts from a file

Name :  Madhu K
Date : 04/07/2025
*/

#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {

	FILE *fp;
	fp = fopen("contactbook.csv", "w");
	if(fp == NULL)
	{
		printf("ERROR: could not open file for writing\n");
		return;
	}
	fprintf(fp, "#%d\n",addressBook->contactCount);
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	}
	fclose(fp);
	printf("Contacts Saved To File Successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) {

	FILE *fp;
	fp = fopen("contactbook.csv", "r");
	if(fp == NULL)
	{
		printf("ERROR: could not open file to Read\n");
		return ;
	}
	fscanf(fp, "#%d", &addressBook->contactCount);
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		fscanf(fp, " %[^,], %[^,], %[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	}
	fclose(fp);
	printf("contact Loaded from file successfully\n");
}

