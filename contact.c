#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>
#define CONTACT_H
#define SORT_BY_NAME 1


void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    Contact temp;//Temporary variable for swapping contacts

    for (int i = 0; i < addressBook->contactCount - 1; i++)//outer loop for sorting
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)//compare element at pos i with element after i means i+1
        {
            if (sortCriteria == SORT_BY_NAME)//check which sorting method is requested
            {
                if (strcmp(addressBook->contacts[i].name,
                           addressBook->contacts[j].name) > 0)//compares two names in list
                {
                    temp = addressBook->contacts[i];//swap contacts
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }
    }
    for(int i = 0; i < addressBook -> contactCount; i++)//to print the contact list
    {
        printf("%-15s\t ",addressBook -> contacts[i].name);
        printf("%-15s\t ",addressBook -> contacts[i].phone);
        printf("%s\t\n",addressBook -> contacts[i].email);
    }  
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
int isname(AddressBook *addressBook, char *name)
{ 
    for(int i = 0; name[i] != '\0'; i++) 
    { 
        if(!isalpha(name[i]) && name[i] != ' ')//Allows alphabets and space
            return 0; 
    } 
    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        if(strcasecmp(addressBook->contacts[i].name, name) == 0)//Duplicate check
            return 0; 
    }
            return 1;//if valid
}

int isphone(AddressBook *addressBook, char *phone)
{
    if(strlen(phone) != 10)//ph no must be 10 digits
        return 0;

    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
            return 0;
    }
    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)//Duplicate check
            return 0; 
    }
            return 1;
}

int isemail(AddressBook *addressBook, char *email)
{
    // check @gmail.com exists at the end
    if (!strstr(email, "@gmail.com"))
        return 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        char c = email[i];

        // allow @ and . also
        if (c == '@' || c == '.')
            continue;

        if (!(islower(c) || isdigit(c) || c == '_'))
            return 0;
    }
    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)//Duplicate check
            return 0; 
    }
            return 1;
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char newvalue[100];//temporary variable for user input

    int i = addressBook->contactCount;  //index for newcontacts

    while(1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", newvalue);//read fullname including spaces

        if(isname(addressBook,newvalue))//to validate the name
            break;
        else
            printf("Invalid name! Enter alphabets only.\n");
    }
    strcpy(addressBook->contacts[i].name, newvalue);//stores name

    while(1)
    {
        printf("Enter phone: ");
        scanf(" %[^\n]", newvalue);//read phone number

        if(isphone(addressBook,newvalue))//to validate phone number
            break;
        else
            printf("Invalid or duplicate phone number.\n");
    }
    strcpy(addressBook->contacts[i].phone, newvalue);//stores phone numbber

    while(1)
    {
        printf("Enter email: ");
        scanf(" %[^\n]", newvalue);//read email

        if(isemail(addressBook,newvalue))//to validate email
            break;
        else
            printf("Invalid or duplicate email.\n");
    }
    strcpy(addressBook->contacts[i].email, newvalue);//stores email

    addressBook->contactCount++;//increment contactcount

    printf("%s\t%s\t%s\n",addressBook->contacts[i].name,
                         addressBook->contacts[i].phone,
                         addressBook->contacts[i].email);
    printf("Contact added successfully!\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int option;//to search contact
    char input[100];//user input to search
    int flag = 0;//to check whether contact found or not
    
    printf("Enter option(1-3)\n");
    printf("1.name\n2.phone\n3.email\n");
    scanf("%d",&option);//read user choice

    switch(option)
    {
        case 1:
        {
        printf("Enter name:\n");
        scanf(" %s",input);//read name
            for(int i = 0; i < addressBook -> contactCount; i++)
            {
            if(strstr(addressBook->contacts[i].name,input) != NULL)//partial match
                {
                    flag = 1;
                    printf("%s\t%s\t%s\t\n",addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        }
        case 2:
        {
        printf("Enter phone:\n");
        scanf("%s", input);//read phone
            for(int i = 0; i < addressBook -> contactCount; i++)
            {
            if(strcmp(addressBook->contacts[i].phone,input) == 0)//exact match
                {
                    flag = 1;
                    printf("%s\t%s\t%s\t\n",addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        }
        case 3:
        {
        printf("Enter email:\n");
        scanf("%s",input);//read email
            for(int i = 0; i < addressBook -> contactCount; i++)
            {
            if(strcmp(addressBook->contacts[i].email,input) == 0)//exact match
                {
                    flag = 1;
                    printf("%s\t%s\t%s\t\n",addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        }
        default:
        printf("invalid choice\n");
        return ;
    }
    if(!flag)//if contact not found
    {
        printf("Contact not found\n");
        return;
    }
}
   
void editContact(AddressBook *addressBook)
{
    int option;//option to search by name/phone/email
    char input[100];//user input to search
    int index = -1;//stores index to edit cntact

    printf("Enter option(1-3)\n");
    printf("1.name\n2.phone\n3.email\n");
    scanf("%d", &option);

    switch(option)
    {
        case 1:
            printf("Enter the name:\n");
            scanf(" %[^\n]", input);//read ame with spaces
            break;

        case 2:
            printf("Enter the phone:\n");
            scanf("%s", input);//read phone number
            break;

        case 3:
            printf("Enter the email:\n");
            scanf("%s", input);//read email
            break;

        default:
            printf("Invalid option\n");
            return;
    }

    int arr[100]; // to store matching indices
    int sl_no = 0;//count of matching contacts

    // Collect all matching contacts 
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if( (option == 1 && strstr(addressBook->contacts[i].name, input) != NULL) ||
            (option == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
            (option == 3 && strcmp(addressBook->contacts[i].email, input) == 0) )
            {
                arr[sl_no++] = i;//stores matching index
            }
    }

    if(sl_no == 0)//if there is no matching
    {
        printf("No contact found\n");
        return;
    }

    if(sl_no == 1)//of only 1 contact matched
    {
        index = arr[0];//directly select the contact
        printf("Only one contact found. Editing directly.\n");
    }
    else
    { //display all matching contacts
        printf("\nMatching Contacts:\n");
        for(int i = 0; i < sl_no; i++)
        {
            int idx = arr[i];
            printf("(%d) %s\t %s\t %s\n",
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int select;
        printf("Enter the serial no you want to edit:\n");
        scanf("%d", &select);

        if(select < 1 || select > sl_no)//validate sl-no
        {
            printf("Invalid serial no\n");
            return;
        }

        index = arr[select - 1];//serial no to actual index
    }

    int choice;
    printf("Enter what you want to edit:\n 1.name\n 2.phone\n 3.email\n");
    scanf("%d", &choice);

    char name[100], phone[100], email[100];

    switch(choice)
    {
        case 1:
            printf("Enter the edited name:\n");
            scanf(" %[^\n]", name);

            if(!isname(addressBook, name))//check for validation
            {
                printf("Invalid or duplicate name.\n");
                return;
            }
            strcpy(addressBook->contacts[index].name, name);//stores updated name
            break;

        case 2:
            printf("Enter the edited phone:\n");
            scanf(" %[^\n]", phone);

            if(!isphone(addressBook, phone))//check for validation
            {
                printf("Invalid or duplicate phone number.\n");
                return;
            }
            strcpy(addressBook->contacts[index].phone, phone);//stored updated phone no
            break;

        case 3:
            printf("Enter the edited email:\n");
            scanf(" %[^\n]", email);

            if(!isemail(addressBook, email))//check for validation
            {
                printf("Invalid or duplicate email.\n");
                return;
            }
            strcpy(addressBook->contacts[index].email, email);//stoes updated email
            break;

        default:
            printf("Invalid option\n");
            return;
    }

    printf("<-------- contact updated successfully! ------->\n");
}

void deleteContact(AddressBook *addressBook)
{
    int option; 
    char input[100]; 
    int index = -1; // index of contact to delete 

    // Ask user how they want to search
    printf("Enter option(1 - 3)\n");
    printf("1.name\n2.phone\n3.email\n");
    scanf("%d", &option);

    // Take input based on selected option
    switch(option)
    {
        case 1:
            printf("Enter the name:\n");
            scanf(" %[^\n]", input);  // read full name including spaces
            break;

        case 2:
            printf("Enter the phone:\n");
            scanf("%s", input); // read phone number
            break;

        case 3:
            printf("Enter the email:\n");
            scanf("%s", input);// read email
            break;

        default:
            printf("Invalid option\n");
            return;
    }

    int arr[100];// array to store matching contact indices
    int count = 0; // no of matched contacts

    // Search contacts based on selected option
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(
            (option == 1 && strstr(addressBook->contacts[i].name, input)) ||   // match name
            (option == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) || // match phone
            (option == 3 && strcmp(addressBook->contacts[i].email, input) == 0)    // match email
          )
            {
                arr[count++] = i;   // store matched contact index
            }
    }

    // If no contacts matched
    if(count == 0)
    {
        printf("Contact not found\n");
        return;
    }

    // If only one contact matched
    if(count == 1)
    {
        printf("only one contact found.delete directly\n");
        index = arr[0]; // directly select the only matched contact
    }
    else
    {
        // Display all matching contacts
        printf("\nMatching Contacts:\n");
        for(int i = 0; i < count; i++)
        {
            int idx = arr[i]; // get actual index from array
            printf("(%d) %s\t%s\t%s\n",
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int select;// user selection to delete contact when there is duplicate
        printf("Enter sl_no to delete: ");
        scanf("%d", &select);

        // Validate selected serial number
        if(select < 1 || select > count)
        {
            printf("Invalid serial number\n");
            return;
        }

        index = arr[select - 1]; // convert serial number to actual index
    }

    char ch;         
    printf("Do you want to delete (y/n): ");
    scanf(" %c", &ch);

    //ask confirmation to delete
    if(ch == 'y' || ch == 'Y')
    {
        // Shift contacts to remove the selected contact
        for(int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--; // decrement after detetion
        printf("Contact deleted successfully\n");
    }
    else
    {
        printf("Delete cancelled\n"); // deletion cancelled by user
    }
}
