#include "binarysearchtree.h"
#include "fstream"

Node* add(Node* node, Contact& contact) {
    if (node == NULL) {
        return new Node(contact);
    }

    if (contact.name < node->contact.name) {
        node->left = add(node->left, contact);
    } else if (contact.name > node->contact.name) {
        node->right = add(node->right, contact);
    }

    return node;
}

void loadContactsFromFile(Node*& root, string& filename) {
    ifstream file(filename);    //ifstream - Input file Stream from fstream
    if (file.is_open()) {       // member function of ifstream and ofstream
        string name, phone, email;
        while (getline(file, name) && getline(file, phone) && getline(file, email)) {
            Contact contact(name, phone, email);
            root = add(root, contact);
        }
        file.close();
    } else {
        cout << "Unable to open file for loading contacts." << endl;
    }
}

AddressBook::AddressBook(string& file)
{
    root = NULL;
    filename = file;

    loadContactsFromFile(root, filename);
}

void saveInOrder(Node* node, ofstream& file) {  //ifstream - Output file Stream from fstream
    if (node == NULL) {
        return;
    }

    saveInOrder(node->left, file);
    file << node->contact.name << endl;
    file << node->contact.phone << endl;
    file << node->contact.email << endl;
    saveInOrder(node->right, file);
}

void saveContactsToFile(Node*& root, string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        saveInOrder(root, file);
        file.close();
    } else {
        cout << "Unable to open file for saving contacts." << endl;
    }
}

void destroyBST(Node* node) {
    if (node == NULL) {
        return;
    }

    destroyBST(node->left);
    destroyBST(node->right);
    delete node;
}

AddressBook::~AddressBook()
{
    saveContactsToFile(root, filename);
    destroyBST(root);
}

void AddressBook::addContact(Contact& contact)
{
    root = add(root, contact);
    cout << "Contact added successfully." << endl;
}

Node* srch(Node* node, string& name) {
    if (node == NULL || node->contact.name == name) {
        return node;
    }

    if (name < node->contact.name) {
        return srch(node->left, name);
    } else {
        return srch(node->right, name);
    }
}

void AddressBook::searchContact(string& name) {
    Node* result = srch(root, name);
    if (result) {
        cout << "Name: " << result->contact.name << endl;
        cout << "Phone: " << result->contact.phone << endl;
        cout << "Email: " << result->contact.email << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}

void AddressBook::updateContact(string& name, Contact& newContact) {
    Node* result = srch(root, name);
    if (result) {
        result->contact = newContact;
        cout << "Contact updated successfully." << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}

Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* rmv(Node* node, string& name) {
    if (node == NULL) {
        return node;
    }

    if (name < node->contact.name) {
        node->left = rmv(node->left, name);
    } else if (name > node->contact.name) {
        node->right = rmv(node->right, name);
    } else {
        if (node->left == NULL) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMin(node->right);
        node->contact = temp->contact;
        node->right = rmv(node->right, temp->contact.name);
    }

    return node;
}

void AddressBook::deleteContact(string& name) {
    root = rmv(root, name);
}

void displayInOrder(Node* node) {
    if (node == NULL) {
        return;
    }

    displayInOrder(node->left);
    cout << "Name: " << node->contact.name << endl;
    cout << "Phone: " << node->contact.phone << endl;
    cout << "Email: " << node->contact.email << endl;
    cout << endl;
    displayInOrder(node->right);
}

void AddressBook::displayAllContacts() {
    displayInOrder(root);
}
