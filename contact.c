#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function to validate name

int validateName(char name[])
{

    for (int i = 0; name[i] != '\0'; i++)
    {
        // Name should not begin with '.'
        if (name[0] == '.')
        {
            return 0;
        }

        // If current char is valid then check next char
        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ' || name[i] == '.')
        {
            continue;
        }

        // If name has something other than above mentioned char, then its not valid name so return 0
        else
        {
            return 0;
        }
    }
    return 1;
}

// Function to validate phonenumber

int validatePhone(AddressBook *addressBook, char phoneNum[])
{
    int numlen = strlen(phoneNum);

    // Phone num length must be 10, if not return 0
    if (numlen != 10)
    {
        return 0;
    }

    for (int i = 0; phoneNum[i] != '\0'; i++)
    {
        // If current char is valid (digit) then check next char
        if ((phoneNum[i] >= '0' && phoneNum[i] <= '9'))
        {
            continue;
        }
        // If phone number has any other character apart from digits then return 0
        else
        {
            return 0;
        }
    }

    // Run the loop on addressBook to check whether phonenumber is unique
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // comapare each stored phonenum with present phonenum
        if (strcmp(addressBook->contacts[i].phone, phoneNum) == 0)
        {
            printf("Phonenumber already exists,enter new phonenumber\n");
            return 0;
        }
    }

    // If all validations are correct then return 1
    return 1;
}

// Function to validate email

int validateEmail(AddressBook *addressBook, char email[])
{
    // Count number of @
    int emaillen = strlen(email);
    int atCount = 0;

    // Compares whether email ends with .com or .in
    if (!((strcmp(email + emaillen - 4, ".com") == 0) ||
          (strcmp(email + emaillen - 3, ".in") == 0)))
    {
        printf("Invalid email id, enter valid email\n");
        return 0;
    }

    // Email id shouldn't begin with digit,'@' & '.'
    if ((email[0] >= '0' && email[0] <= '9') || email[0] == '@' || email[0] == '.')
    {
        return 0;
    }

    // Last char of email cannot be @ or .
    if (email[emaillen - 1] == '@' || email[emaillen - 1] == '.')
    {
        return 0;
    }

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
        }

        // Check for consecutive dots
        if (i > 0)
        {
            if (email[i] == '.' && email[i - 1] == '.')
            {
                return 0;
            }
        }

        if ((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= '0' && email[i] <= '9') || email[i] == '@' || email[i] == '.' || email[i] == '_')
        {
            continue;
        }

        // If email id has anything apart from above char then it's not valid email
        else
        {
            return 0;
        }
    }

    // Check whether email id has only one @ or not
    if (atCount != 1)
    {
        return 0;
    }

    // Run the loop on addressBook to check whether email id  is unique
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // comapare each stored email with present email
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("Email id already exists,enter new email\n");
            return 0;
        }
    }

    return 1;
}

void search_by_name(AddressBook *addressBook)
{
    char name_str[50];
    Contact sameNames[20];       // Instace of contact to store same names found while searching
    int similarNameContacts = 0; // To track multiple contacts with same names
    printf("Enter name to search:\n");
    scanf(" %[^\n]", name_str);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Comparing addressbook database with user entered name (case insensitive)
        if (strcasecmp(addressBook->contacts[i].name, name_str) == 0)
        {
            printf("Your required contact(s) is/are :\n");
            sameNames[similarNameContacts] = addressBook->contacts[i];
            // We are keeping count of multiple names if any
            similarNameContacts++;

            // Printing matching name contacts(s)
            printf("%d. %s %s %s\n", similarNameContacts, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }

    // If no matching name is found
    if (similarNameContacts == 0)
    {
        printf("No contact found with entererd name\n");
    }

    // If multiple matching names are found
    if (similarNameContacts > 1)
    {
        int contactChoice;
        do
        {
            printf("Enter serial number to select a particular contact :\n");
            scanf("%d", &contactChoice);

            for (int i = 0; i < similarNameContacts; i++)
            {
                if (contactChoice - 1 == i)
                {
                    printf("Your choosen contact is :\n");
                    printf("%d. %s %s %s\n", contactChoice, sameNames[i].name, sameNames[i].phone, sameNames[i].email);
                }
            }
        } while (contactChoice > similarNameContacts);
    }
}

void search_by_phone(AddressBook *addressBook)
{
    char phone_str[15];
    printf("Enter phone number :\n");
    scanf(" %[^\n]", phone_str);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone_str) == 0)
        {
            printf("Your required contact is :\n");
            printf("%d. %s %s %s\n", 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            return;
        }
    }
    printf("No contact is found with given phone number \n");
}

void search_by_email(AddressBook *addressBook)
{
    char email_str[50];
    printf("Enter email id:\n");
    scanf(" %[^\n]", email_str);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email_str) == 0)
        {
            printf("Your required contact is :\n");
            printf("%d. %s %s %s\n", 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            return;
        }
    }
    printf("No contact is found with given email id \n");
}

/*void editName(AddressBook *addressBook)
{

}*/

void deleteByPhone(AddressBook *addressBook)
{
    char phoneNum[15]; // User entered phonenumber
    int found = 0;     // variable to check phonenumber is found or not
    printf("Enter phone number :\n");
    scanf("%s", phoneNum);

    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phoneNum) == 0)
        {
            int j = i;
            for (j = i; j < addressBook->contactCount - 1; j++)
            {
                found = 1;
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            // Decrement the total contactcount so that last element is not considered next time
            addressBook->contactCount--;
            printf("Contact deleted successfully ✅\n");
            break;
        }
    }
    if (found == 0)
    {
        printf("Contact not found ❌\n");
    }
}

void deleteByEmail(AddressBook *addressBook)
{
    char email[50]; // User entered email
    int found = 0;  // Variable to check whether email is found or not
    printf("Enter email id :\n");
    scanf("%s", email);

    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            int j = i;
            for (j = i; j < addressBook->contactCount - 1; j++)
            {
                found = 1;
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            // Decrement the total contactcount so that last element is not considered next time
            addressBook->contactCount--;
            printf("Contact deleted successfully ✅\n");
            break;
        }
    }
    if (found = 0)
    {
        printf("Contact not found ❌\n");
    }
}

void deleteByName(AddressBook *addressBook)
{
    char name[50]; // User entered name

    printf("Enter name :\n");
    scanf(" %[^\n]", name);

    int i;
    int sameNameContact = 0; // variable to check if there are multiple contacts with same name

    // Counting  the same name contacts to handle the edge cases properly
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(addressBook->contacts[i].name, name) == 0)
        {
            sameNameContact++;
        }
    }

    if (sameNameContact == 0)
    {
        printf("Contact not found ❌\n");
    }

    else if (sameNameContact == 1)
    {
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasecmp(addressBook->contacts[i].name, name) == 0)
            {
                int j = i;
                for (j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                // Decrement the total contactcount so that last element is not considered next time
                addressBook->contactCount--;
                printf("Contact deleted successfully ✅\n");
                break;
            }
        }
    }

    else
    {
        int choice;

        printf("There are multiple contacts found with the same name\n");

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            // Comparing addressbook database with user entered name (case insensitive)
            if (strcasecmp(addressBook->contacts[i].name, name) == 0)
            {
                // Printing matching name contacts
                printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
        }

        printf("So, Delete By :\n 1.Phone number \n 2.Email\n");
        printf("Enter your choice :\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            deleteByPhone(addressBook);
            break;

        case 2:
            deleteByEmail(addressBook);
            break;

        default:
            printf("Invalid Option\n");
        }
    }
}

// Core logic to handle menu options : Create,Search,Edit,Delete,Save and exit.

void listContacts(AddressBook *addressBook)
{

    printf("All the contacts in the addressbook are :\n");

    // Sort contacts based on the chosen criteria A-Z using bubble sort
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {

            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                // temp variable of type contact so that it can have all 3 name,phone,and email as declared in contacts array
                // Swap entire contact
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files) after user enters ./a.out
    // loadContactsFromFile(addressBook);
    //->open file in r mode
    // validation (NUll or not)
    // Read Contact count (skip #)
    // Read using fscanf() -> reads input from file
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program

    // fopen'w' //frptintf -> prints in file
    // save format -> # 3 (total contact count) -> first line
    // second line start storing contacts (using loop)
    // close the file
    // Delete populate.c and.h not required
}

void createContact(AddressBook *addressBook)
{
    // Take name,phone and email as input and validate before storing in addressbook
    char name_str[50];
    char phone_str[15];
    char email_str[50];

    // Taking name as input and validating it. Run the loop till valid name is not entered
    do
    {
        printf("Enter Name :\n");
        scanf(" %[^\n]", name_str);

    } while (validateName(name_str) != 1);

    // Taking phone as input and validating it. Run the loop till valid phonenum is not entered
    do
    {
        printf("Enter Phone Number :\n");
        scanf(" %[^\n]", phone_str);

    } while (validatePhone(addressBook, phone_str) != 1); // Since addressBook is already a pointer we pass it directly
    // If it was normal structure we would have passed it using &

    // Taking email as input and validating it. Run the loop till valid email is not entered

    do
    {
        printf("Enter email id :\n");
        scanf(" %[^\n]", email_str);
    } while (validateEmail(addressBook, email_str) != 1);

    // Copying name,phone and email after validation to addressbook database
    strcpy(addressBook->contacts[addressBook->contactCount].name, name_str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_str);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email_str);

    printf("Contact created successfully 🎉");
    // Incrementing contactCount in addressbook to track number of contacts added
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int choice;

    do
    {
        printf("1.Search By Name \n");
        printf("2.Search By Phone \n");
        printf("3.Search By Email \n");
        printf("4.Exit \n");

        printf("Enter your choice :\n");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            search_by_name(addressBook);
            break;

        case 2:
            search_by_phone(addressBook);
            break;

        case 3:
            search_by_email(addressBook);
            break;

        case 4:
            break;

        default:
            printf("Invalid Entry\n");
        }
    } while (choice != 4);
}

void editContact(AddressBook *addressBook)
{
    /*int choice;

     searchContact(AddressBook * addressBook);

     printf("What field you want to edit :\n");
     printf("1.Edit Name \n");
     printf("2.Edit Phone \n");
     printf("3.Edit Email \n");
     printf("4.Go to main menu\n");

     printf("Enter your choice :\n");
     scanf(" %d", &choice);

     switch (choice)
     {
     case 1:
         editName(AddressBook * addressBook);
         break;
     case 2:
         editPhone(AddressBook * addressBook);
         break;
     case 3:
         editEmail(AddressBook * addressBook);
         break;
     case 4:
         break;
     }*/
}

void deleteContact(AddressBook *addressBook)
{
    int choice;

    printf("Enter your choice:\n");
    printf("1.Delete by name\n 2.Delete by phone\n 3.Delete by email\n 4.Return to main menu\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        deleteByName(addressBook);
        break;
    case 2:
        deleteByPhone(addressBook);
        break;
    case 3:
        deleteByEmail(addressBook);
        break;
    case 4:
        break;

    default:
        printf("Invalid option:\n");
    }
}
