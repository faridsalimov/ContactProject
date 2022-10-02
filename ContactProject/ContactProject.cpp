#include <iostream>
#include <Windows.h>
#include "Functions.h"

using namespace std;

void main() {
	while (true)
	{
		setcolor(15, 0);
		Menu();

		int select = 0;
		cin >> select;
		system("cls");

		if (select == 1) {
			if (contact->count == 0) {
				setAlert(4, new char[100]{ "Not found contacts." });
			}
			else {
				showAllContacts(*contact);
				contactSelectMenu(*contact);
			}
		}

		else if (select == 2) {
			auto newcontact = newContact();
			addNewContact(*contact, *newcontact);
		}

		else if (select == 3) {
			if (contact->count == 0) {
				setAlert(4, new char[100]{ "Not found contacts." });
			}
			else {
				searchContact(*contacts, *contact);
			}
		}

		else if (select == 4) {
			setcolor(10, 0);
			cout << "GOODBYE!" << endl;
			setcolor(15, 0);
			break;
		}

		else {
			setAlert(4, new char[100] {"Invilad Select!"});
		}
	}
}