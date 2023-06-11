#include "binarysearchtree.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main() {
    string filename = "contacts.txt";   // Name of the file
    AddressBook addressBook(filename);  // Create an object
    char choice;
    string name, phone, email;

// do-while is used because user input is taken inside the loop
    do {
        cout << "Address Book Application" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Search Contact" << endl;
        cout << "3. Update Contact" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Display All Contacts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                cout << "Enter name: ";
                cin.ignore();               // To flash stream for getline function
                getline(cin, name);
                cout << "Enter phone: ";
                getline(cin, phone);
                cout << "Enter email: ";
                getline(cin, email);
                Contact contact(name, phone, email);
                addressBook.addContact(contact);
                break;
            }
            case '2': {
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, name);
                addressBook.searchContact(name);
                break;
            }
            case '3': {
                cout << "Enter name to update: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new phone: ";
                getline(cin, phone);
                cout << "Enter new email: ";
                getline(cin, email);
                Contact newContact(name, phone, email);
                addressBook.updateContact(name, newContact);
                break;
            }
            case '4': {
                cout << "Enter name to delete: ";
                cin.ignore();
                getline(cin, name);
                addressBook.deleteContact(name);
                break;
            }
            case '5': {
                addressBook.displayAllContacts();
                break;
            }
            case '6':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
        cout << endl;
    } while (choice != '6');

    return 0;
}
