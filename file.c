#include <stdio.h>  
#include "file.h"      
#include <unistd.h> //Header for usleep() function

//Function to save contacts from address book to a file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;//File pointer

    //Open file in write mode
    if((fp = fopen("contact.csv","w")) == NULL)
    {
        fprintf(stderr,"file not found\n");//Print error if file cannot open
        return; 
    }

    //Write each contact to the file
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp,"%s,%s,%s\n",
                addressBook->contacts[i].name,//Write name
                addressBook->contacts[i].phone,//Write phone
                addressBook->contacts[i].email);//Write email
    }

    //Display saving animation
    for(int i = 0; i < 5; i++)
    {
        printf("saving..........\n");
        fflush(stdout);//Force the output to display immediately
        usleep(100000);//Delay for 0.1 seconds
    }

    printf("\n");
    fclose(fp);//Close the file
}

//Function to load contacts from file to address book
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;//File pointer

    //Open file in read mode
    if((fp = fopen("contact.csv","r")) == NULL)
    {
        fprintf(stderr,"file not found\n");//Error if file not found
        return; 
    }

    //Read contacts from file until end
    while((fscanf(fp,"%[^,],%[^,],%[^\n]\n",
          addressBook->contacts[addressBook->contactCount].name,//Read name
          addressBook->contacts[addressBook->contactCount].phone,//Read phone
          addressBook->contacts[addressBook->contactCount].email) == 3))//Read email
    {
        addressBook->contactCount++;//Increment contact count
    }

    fclose(fp);//Close the file
}
