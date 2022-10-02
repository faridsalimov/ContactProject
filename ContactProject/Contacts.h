#pragma once

struct Contacts {
	char* name;
	char* phone;
};

struct Contact {
	Contacts** contacts;
	int count = 0;
};