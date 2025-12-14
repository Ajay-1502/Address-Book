
#include <stdio.h>
#include "contact.h"

#define RESET "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);

    do
    {
        // ---------- Menu Header ---------- //
        printf("\n%s=====================================%s\n", CYAN, RESET);
        printf("%s        📒 ADDRESS BOOK MENU         %s\n", YELLOW, RESET);
        printf("%s=====================================%s\n", CYAN, RESET);

        // ---------- Menu Options ---------- //

        printf("%s1.%s Create Contact\n", GREEN, RESET);
        printf("%s2.%s Search Contact\n", GREEN, RESET);
        printf("%s3.%s Edit Contact\n", GREEN, RESET);
        printf("%s4.%s Delete Contact\n", GREEN, RESET);
        printf("%s5.%s List All Contacts\n", GREEN, RESET);
        printf("%s6.%s Save and Exit\n", GREEN, RESET);

        printf("\n%sEnter your choice ➜ %s", BLUE, RESET);
        scanf("%d", &choice);

        printf("\n");

        switch (choice)
        {
        case 1:
            printf("%s--- Create Contact --- %s\n", MAGENTA, RESET);
            createContact(&addressBook);
            break;

        case 2:
            printf("%s--- Search Contact --- %s\n", MAGENTA, RESET);
            searchContact(&addressBook);
            break;

        case 3:
            printf("%s--- Edit Contact --- %s\n", MAGENTA, RESET);
            editContact(&addressBook);
            break;

        case 4:
            printf("%s--- Delete Contact --- %s\n", MAGENTA, RESET);
            deleteContact(&addressBook);
            break;

        case 5:
            printf("%s--- Contact List --- %s\n", MAGENTA, RESET);
            listContacts(&addressBook);
            break;

        case 6:
            // saveContactsToFile(&addressBook);
            printf("%sSaving data and exiting... 👋%s\n", YELLOW, RESET);
            break;

        default:
            printf("%s❌ Invalid choice! Please try again.%s\n", RED, RESET);
        }

    } while (choice != 6);

    // ---------- Final Exit Message ---------- //
    printf("%sThank you for using Address Book! 😊%s\n", CYAN, RESET);

    return 0;
}
