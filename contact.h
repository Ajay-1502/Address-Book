#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

/* typedef is a keyword used to create new data type names and aliases for existing types.
In this case , we are defining a new data type called 'Contact' & addressbook which is a structure that holds information about a contact and addressbook.
I am using typedef here to simplify the syntax when declaring variables of this structure type later in the code.*/

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// AddressBook is the structure that holds an array of contacts and the count of current contacts
// Here AddressBook is used as a database to store multiple contacts
typedef struct
{
    Contact contacts[100]; // Array to hold multiple contacts, each contact has name, phone, email
    int contactCount;
} AddressBook;

// Function declarations
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
