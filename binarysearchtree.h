#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include<iostream>
#include<utility>
#include<string>
using namespace std;

// Contact structure to store contact details
struct Contact {
    string name;
    string phone;
    string email;

    Contact(){}     //Default constructor - it is used to create a new node in the add function without any arguments

/*
    Move() function - an utility function that converts lvalue(left side of the assignment operator) into rvalue(right side of the assignment operator)
                      to transfer the ownership of resources and optimize the performance
*/
    Contact(string name, string phone, string email) {
        this->name = move(name);
        this->phone = move(phone);
        this->email = move(email);
    }
};

// Node structure for BST
struct Node {
    Contact contact;
    Node* left;
    Node* right;

    Node(Contact contact) {
        this->contact = move(contact);
        this->left = NULL;
        this->right = NULL;
    }
};

class AddressBook{
    public:
        AddressBook(string&);
        ~AddressBook();
        void addContact(Contact&);
        void searchContact(string&);
        void updateContact(string&, Contact&);
        void deleteContact(string&);
        void displayAllContacts();

    private:
        Node* root;
        string filename;
};

#endif // BINARYSEARCHTREE_H_INCLUDED
