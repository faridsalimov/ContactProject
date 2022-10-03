#pragma once

#include <iostream>
#include <Windows.h>
#include "Contacts.h"

using namespace std;

FILE* file;
Contact* contact = new Contact{};
Contacts* contacts = new Contacts{};
void showAllContacts(const Contact& contact);

void writeFile(char* name, char* phone) {
	fopen_s(&file, "contacts.txt", "a");
	fputs(name, file);
	fputs(" - ", file);
	fputs(phone, file);
	fputs("\n", file);
	fclose(file);
}

void setcolor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

void setAlert(int color, char* text) {
	system("cls");
	setcolor(color, 0);
	cout << "[!] ";
	setcolor(15, 0);
	cout << text << endl << endl;
	cout << "\a";
}

void Menu() {
	cout << "======================" << endl;
	cout << "1. Show All Contacts" << endl;
	cout << "2. Add New Contact" << endl;
	cout << "3. Search Contact" << endl;
	cout << "4. Quit" << endl;
	cout << "======================" << endl;
	cout << "SELECT: ";
}

void showContact(const Contacts& contact) {
	cout << "Name : " << contact.name << endl;
	cout << "Phone : " << contact.phone << endl;
}

void searchContact(Contacts& contacts, Contact& contact) {
	system("cls");
	cout << "======================" << endl;
	cout << "1. Search Name" << endl;
	cout << "2. Search Phone" << endl;
	cout << "3. Back to Home" << endl;
	cout << "======================" << endl;
	cout << "SELECT: ";

	int select = 0;
	cin >> select;

	if (select == 1) {
		system("cls");
		cin.ignore();
		cin.clear();

		cout << "Enter the name: ";
		char* name = new char[100]{};
		cin.getline(name, 100);

		for (int i = 0; i < contact.count; i++)
		{
			if ((*contact.contacts)->name[i] == *name) {
				setAlert(10, new char[100]{ "Contact found." });
			}

			else {
				setAlert(4, new char[100]{ "Contact not found." });
			}
		}
	}

	else if (select == 2) {
		system("cls");
		cin.ignore();
		cin.clear();

		cout << "Enter the phone: ";
		char* phone = new char[100] {};
		cin.getline(phone, 100);

		for (int i = 0; i < contact.count; i++)
		{
			if ((*contact.contacts)->phone[i] == *phone) {
				setAlert(10, new char[100] { "Contact found." });
			}

			else {
				setAlert(4, new char[100] { "Contact not found." });
			}
		}
	}

	else if (select == 3) {
		system("cls");
	}

	else {
		setAlert(4, new char[100]{ "Invilad Select!" });
	}
}

void deleteContact(Contact& contact, int id) {
	auto contacts = new Contacts * [contact.count - 1]{};

	for (int i = 0; i < id; i++)
	{
		contacts[i] = contact.contacts[i];
	}

	for (int i = id; i < contact.count - 1; i++)
	{
		contacts[i] = contact.contacts[i + 1];
	}

	contact.contacts = contacts;
	contact.count--;
	contacts = nullptr;
	setAlert(10, new char[100]{ "The contact has been successfully deleted." });
}

void editTheContact(Contact& contact, Contacts& contacts, int id) {
	int count = contact.count;
	auto newcontacts = new Contacts * [count]{};
	auto editcontacts = new Contacts * [contact.count - 1]{};

	for (int i = 0; i < count; i++)
	{
		newcontacts[i] = contact.contacts[i];
	}

	newcontacts[count] = new Contacts{ contacts };
	contact.contacts = newcontacts;
	newcontacts = NULL;
	contact.count++;

	for (int i = 0; i < id; i++)
	{
		editcontacts[i] = contact.contacts[i];
	}

	for (int i = 0; i < count; i++)
	{
		editcontacts[i] = contact.contacts[i + 1];
	}

	contact.contacts = editcontacts;
	contact.count--;
	editcontacts = nullptr;

	setAlert(10, new char[100]{ "The contact has been successfully edited." });
}

Contacts* editContact() {
	system("cls");
	cin.ignore();
	cin.clear();

	cout << "Enter the new name: ";
	char* name = new char[100]{};
	cin.getline(name, 100);

	cout << "Enter the new phone: ";
	char* phone = new char[100]{};
	cin.getline(phone, 100);

	Contacts* contact = new Contacts{ name, phone };
	return contact;
}

void contactSelectMenu(Contact& contact) {
	cout << "======================" << endl;
	cout << "1. Select Contact" << endl;
	cout << "2. Back to Home" << endl;
	cout << "======================" << endl;
	cout << "SELECT: ";

	int select = 0;
	cin >> select;

	if (select == 1) {
		system("cls");
		showAllContacts(contact);
		int id = 0;
		cout << "======================" << endl;
		cout << "Enter the Contact ID: ";
		cin >> id;
		id--;

		if (id < contact.count) {
			cout << "======================" << endl;
			cout << "1. Edit Contact" << endl;
			cout << "2. Delete Contact" << endl;
			cout << "3. Back to Home" << endl;
			cout << "======================" << endl;
			cout << "SELECT: ";

			int select = 0;
			cin >> select;

			if (select == 1) {
				auto editcontact = editContact();
				editTheContact(contact, *editcontact, id);
			}

			else if (select == 2) {
				deleteContact(contact, id);
			}

			else if (select == 3) {
				system("cls");
			}

			else {
				setAlert(4, new char[100] {"Invilad Select!"});
			}
		}

		else {
			setAlert(4, new char[100] {"Invilad Contact ID!"});
		}
	}

	else if (select == 2) {
		system("cls");
	}

	else {
		setAlert(4, new char[100]{ "Invilad Select!" });
	}
}

void showAllContacts(const Contact& contact) {
	for (int i = 0; i < contact.count; i++)
	{
		cout << "======================" << endl;
		cout << "Contact ID : " << i + 1 << endl;
		showContact(*contact.contacts[i]);
	}
}

Contacts* newContact() {
	cin.ignore();
	cin.clear();

	cout << "Enter the name: ";
	char* name = new char[100] {};
	cin.getline(name, 100);

	cout << "Enter the phone: ";
	char* phone = new char[100] {};
	cin.getline(phone, 100);

	Contacts* contact = new Contacts{ name, phone };
	writeFile(name, phone);
	return contact;
}

void addNewContact(Contact& contact, const Contacts& contacts) {
	int count = contact.count;
	auto newcontacts = new Contacts * [count + 1] {};

	for (int i = 0; i < count; i++)
	{
		newcontacts[i] = contact.contacts[i];
	}

	newcontacts[count] = new Contacts{ contacts };
	contact.contacts = newcontacts;
	newcontacts = NULL;
	contact.count++;

	setAlert(10, new char[100] {"Successfully added new contact!"});
}