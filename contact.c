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

void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria A-Z using bubble sort

    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {

            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
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

    // Load contacts from file during initialization (After files)
    // loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
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
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
}
