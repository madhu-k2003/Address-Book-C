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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

// Checks if number is only digits and exactly 10 characters
int valid_number(const char *number, int num_len)
{
	for(int i=0; number[i] != '\0'; i++)
	{
		if(!isdigit(number[i]))
		{
			printf("Number must be digit only\n");
			return 0;
		}
	}

	if(strlen(number) != num_len)
	{
		printf("Invalid Number: Number must be 10 digit\n");
		return 0;
	}
	return 1;
}
// Checks if phone already exists in the address book
int number_exist(const AddressBook *addressBook, const char *number)
{
	for(int i=0; i < addressBook->contactCount; i++)
	if(strcmp(addressBook->contacts[i].phone, number)==0)
		return 1;
	
	return 0;
}
// Validates email: must contain '@', end with '.com', and no uppercase/space
int valid_mail(char *mail, int len)
{
	if(len < 5)
	{
		printf("\nInvalid E-mail: Too Short\n");
		return 0;
	}
	int at_index = -1;
	for(int i=0; i<len; i++)
	{
		if(isspace(mail[i]))
		{
			printf("\nInvalid E-mail: It contains whitespace\n");
			return 0;
		}
		if(isupper(mail[i]))
		{
			printf("\nInvalid E-mail: It contains Upper letters\n");
			return 0;
		}

		if(mail[i] == '@')
		{
			if(at_index != -1)
			{
				printf("\nInvalid E-mail: More than 1 '@' symbol\n");
				return 0;
			}

			at_index = i;
		}
			
	}
	if(at_index == -1 || at_index >= len -2)
	{
		printf("\nInvalid Email: '@' must be followed by domain name\n");
		return 0;
	}
	int valid_before_at = 0;
	for (int i = 0; i < at_index; i++) 
        {
            if (isalnum(mail[i])) 
	    {
	       valid_before_at = 1;
	       break;
            }
       }
       if (!valid_before_at) 
       {
	   printf("\nInvalid E-mail: No alphanumeric characters before '@'\n");
	   return 0;
       }
	if(!isalnum(mail[at_index + 1]))
	{
		printf("\nInvalid Email: Character after '@' must be alphanumeric\n");
		return 0;
	}

	if(strcmp(mail + len - 4,".com")!=0)
	{
		printf("\nInvalid Email: Must end with '.com'\n");
		return 0;
	}
	int dotcom_seen = 0;
	for (int i = 0; i < len - 4; i++) 
	{
	   if (strncmp(&mail[i], ".com", 4) == 0) 
	   {
              dotcom_seen++;
	      if (dotcom_seen > 0) 
	      {
		      printf("\nInvalid E-mail: '.com' appears more than once\n"); 
       		      return 0;
	      }
           }
	}
	return 1;
}
// Checks if email already exists in the address book
int mail_exist(const AddressBook *addressBook, const char *mail)
{
	for(int i=0; i < addressBook->contactCount; i++)
	if(strcmp(addressBook->contacts[i].email, mail)==0)
		return 1;
	
	return 0;
}

//Checks the Name in addressbook if name exist print contact Details or contact not found
int search_name(AddressBook *addressBook, char *name)
{
	int found = 0;
	for(int i=0; i < addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].name, name)==0)
		{
			if(found == 0)
			printf("\nContact found\n");
			printf("Name : %s\n",addressBook->contacts[i].name);
			printf("Phone : %s\n",addressBook->contacts[i].phone);
			printf("Email ID : %s\n",addressBook->contacts[i].email);
			found = 1;
		}
	}
	if(!found)
	printf("Contact not found\n");
	return 0;
}

int search_phone(AddressBook *addressBook, char *phone)
{
	for(int i=0; i < addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].phone, phone)==0)
		{
			printf("Contact found\n");
			printf("Name : %s\n",addressBook->contacts[i].name);
			printf("Phone : %s\n",addressBook->contacts[i].phone);
			printf("Email ID : %s\n",addressBook->contacts[i].email);
			return 1;
		}
	}
	printf("Contact not found\n");

	return 0;
}

int search_email(AddressBook *addressBook, char *mail)
{
	for(int i=0; i < addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].email, mail)==0)
		{
			printf("\nContact found\n");
			printf("Name : %s\n",addressBook->contacts[i].name);
			printf("Phone : %s\n",addressBook->contacts[i].phone);
			printf("Email ID : %s\n",addressBook->contacts[i].email);
			return 1;
		}
	}
	printf("Contact not found With that E-mail\n");
	return 0;
}

//Here it print the Contacts List after Sucessfully Saved to file
void listContacts(AddressBook *addressBook) 
{
	if(addressBook->contactCount ==0)
	{
		printf("No contact avaliable\n");
		return ;
	}

	printf("\n------------Contact List----------------\n");
	for(int i=0; i < addressBook->contactCount; i++)
	{
	printf("Contact %d :\n",i+1);
        printf("Name : %s\n", addressBook->contacts[i].name);
	printf("Phone : %s\n", addressBook->contacts[i].phone);
	printf("E-mail : %s\n", addressBook->contacts[i].email);
	printf("\n");
	}
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
  //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Creates and adds a new contact to the address book
void createContact(AddressBook *addressBook)
{

    	printf("\nEnter the name : ");
	while (getchar() != '\n');
   	scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);


  
    char number[11];
     while(1)    // Repeatedly prompt until a valid, unique number is entered
     {
	     printf("Enter the Mobile Number : ");
	     scanf(" %s",number);
	     
	     if(!valid_number(number,10))continue;	     //Validate number format and length
	     
	     if(number_exist(addressBook, number)) 	// Check for duplicate phone numbers
	     {
		     printf("Number Already Exists\n");
		     continue;
		}
	     break;
     }
      // Save validated phone number
     strcpy(addressBook->contacts[addressBook->contactCount].phone, number);
	
    char mail[40]; 
    while(1) 	// Repeatedly prompt until a valid, unique email is entered
    {
	    printf("Enter Mail-ID : ");
	    scanf(" %[^\n]",mail);
	    int mail_len = strlen(mail);

	    if(!valid_mail(mail,mail_len))continue;       // Validate email format

	  if(mail_exist(addressBook,mail))	// Check for duplicate email
	     {
		    printf("E-mail Already Exists\n");
		    continue;
	     }
	    break;
}
 	strcpy(addressBook->contacts[addressBook->contactCount].email,mail);	 // Save validated email
	addressBook->contactCount++;    // Increment contact count after successful entry
	
	int i = addressBook->contactCount - 1;
  	printf("\n_______contact Saved Sucessfully_______\n");  // Print confirmation and contact details

	printf("Name : %s\n",addressBook->contacts[i].name);
	printf("Phone : %s\n",addressBook->contacts[i].phone);
	printf("E-mail ID : %s\n",addressBook->contacts[i].email);
}

//Here it Search for Name, Phone , Email in addressbook
void searchContact(AddressBook *addressBook) 
{
	char name[20];
	char phone[11];
	char email[20];
	int option;
	printf("\nsearch By\n");
	printf("1.Name\n2.Phone\n3.E-mailID\n");
	printf("\nEnter your option : ");
	scanf("%d",&option);
	while (getchar() != '\n');


	switch(option)
	{
		case 1:
			printf("Enter Name to Search : ");
			scanf(" %[^\n]",name);
			while (getchar() != '\n');
			search_name(addressBook,name);
			break;
	
		case 2:
			printf("Enter Phone number to Search : ");
			scanf("%s",phone);
			search_phone(addressBook,phone);
			break;

		case 3:
			printf("Enter Email to Search : ");
			scanf("%s",email);
			search_email(addressBook,email);
			break;
		default :
			printf("Invalid Option.");
	}
	
	

}
int find_contact(AddressBook *addressBook);
void editContact(AddressBook *addressBook)  // Edits name, phone, or email of an existing contact
{
	if(addressBook->contactCount == 0)
	{
		printf("Address Book is empty\n");
		return;
	}
	int idx = find_contact(addressBook);
	if(idx < 0)return;

	Contact *c = &addressBook->contacts[idx];

	printf("1.Name : %s\n",c->name);
	printf("2.phone : %s\n",c->phone);
	printf("3.E-mail : %s\n",c->email);
		
	int option;		
	printf("\nEnter which Option to Edit : ");
	scanf("%d",&option);
	while (getchar() != '\n');
	char number[11];
	char mail[40];

	switch(option)
	{
		case 1:
			printf("Enter New Name : ");
			scanf(" %[^\n]",c->name);
			while (getchar() != '\n');
			printf("Name Updated\n.");
			break;
		case 2:
			while(1)
			{	
			printf("Enter New Number : ");
			scanf("%s",number);

			if(!valid_number(number,10)){
			continue;
			}
			
			if(number_exist(addressBook, number)){
				printf("Number Already Exist\n");
				continue;
			}
			strcpy(c->phone,number);
			printf("Number Updated\n.");
			break;
			}break;
		case 3:
			while(1)
			{
			printf("Enter New E-mail : ");
		        scanf("%s",mail);
			int len = strlen(mail);

	       	        if(!valid_mail(mail, len)){
				continue;
			}
			if(mail_exist(addressBook, mail)){
				printf("Already exist\n");
				continue;
			}
		        strcpy(c->email,mail);
	 		printf("E-mail Updated\n.");
			break;
			}break;
		default:
			printf("Invalid option.");
	}
}
 int find_contact(AddressBook *addressBook)	// Finds and returns the index of a contact based on input
{
	int choice;
	char key [30];
	int found_indices[10];
	int found_count = 0;

	printf("\n Select Contact by\n");
	printf("1.Name\n2.Phone\n3.E-mail\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	while (getchar() != '\n');

	if(choice == 1)
	{
	printf("\nEnter name : ");
	while (getchar() != '\n');
	scanf(" %[^\n]",key);


	for(int i=0; i< addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].name,key)==0)
		{
			printf("\nMatch %d :\n", found_count + 1);
			//printf("Index: %d\n",i);
			printf("Name : %s\n", addressBook->contacts[i].name);
			printf("Phone : %s\n", addressBook->contacts[i].phone);
			printf("E-mail : %s\n", addressBook->contacts[i].email);
			found_indices[found_count++] = i;
		}
	}
	}
	else if(choice == 2)
	{
		printf("Enter Phone : ");
		scanf("%s",key);
	for(int i=0; i< addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].phone,key)==0)
		{
			printf("\nMatch %d :\n", found_count + 1);
			//printf("Index: %d\n",i);
			printf("Name : %s\n", addressBook->contacts[i].name);
			printf("Phone : %s\n", addressBook->contacts[i].phone);
			printf("E-mail : %s\n", addressBook->contacts[i].email);
			found_indices[found_count++] = i;
		}
	}
	}
	else if(choice == 3)
	{
		printf("Enter E-mail : ");
		scanf("%s",key);

	for(int i=0; i< addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].email,key)==0)
		{
			printf("\nMatch %d :\n", found_count + 1);
			//printf("Index: %d\n",i);
			printf("Name : %s\n", addressBook->contacts[i].name);
			printf("Phone : %s\n", addressBook->contacts[i].phone);
			printf("E-mail : %s\n", addressBook->contacts[i].email);
			found_indices[found_count++] = i;
		}
	}
	}
	else
	{
		printf("Invalid Option.\n");
		return -1;
	}
	if(found_count == 0)
	{
	  printf("Contact not found\n");
		return -1;
	}
	else if(found_count == 1)
	{
		return found_indices[0];
	}
	else
	{
		int selection;
		printf("\nMultiple contacts found. Enter match number to select (1 - %d): ", found_count);
		scanf("%d", &selection);
		if(selection < 1 || selection > found_count )
		{
			printf("Invalid selection\n");
			return -1;
		}
		return found_indices[selection - 1];
	}

}
// Deletes a selected contact after user confirmation
void deleteContact(AddressBook *addressBook)	
{
	if(addressBook->contactCount == 0)
	{
		printf("Address Book is Empty\n");
			return;
	}
	int idx = find_contact(addressBook);
	if(idx < 0)return;

	Contact *c = &addressBook->contacts[idx];
	printf("\nContact Selected:\n");

	printf("Name : %s\n",c->name);
	printf("Phone : %s\n",c->phone);
	printf("E-mail : %s\n",c->email);

	char confirm;
	printf("\nDelete This Contact?(y/n): ");
	scanf(" %c", &confirm);
	if(confirm != 'y' && confirm != 'Y')
	{
		printf("Deletion Cancelled\n");
		return;
	}

	for(int i = idx; i < addressBook->contactCount - 1; i++)
		addressBook->contacts[i] = addressBook->contacts[i + 1];

	addressBook->contactCount--;
	printf("Contact Deleted Successfully\n");
}
