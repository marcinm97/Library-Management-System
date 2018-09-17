#include "library.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <ctime>
#include <cmath>
#include <fstream>
#include <new>
#include <valarray>
#include <cfloat>
#include <exception>
#include <set>
#include <map>
#include <list>
#include <initializer_list>

std::string Library::s_binaryPath("Library.bin");
std::map<int, Book> Library::s_bookMap;
std::map<int, Customer> Library::s_customerMap;
using namespace std;
Library::Library() {
	load();

	bool quit = false;
	while (!quit) {
		std::cout << "1. Add Book" << std::endl
			<< "2. Delete Book" << std::endl
			<< "3. List Books" << std::endl
			<< "4. Add Customer" << std::endl
			<< "5. Delete Customer" << std::endl
			<< "6. List Customers" << std::endl
			<< "7. Borrow Book" << std::endl
			<< "8. Reserve Book" << std::endl
			<< "9. Return Book" << std::endl
			<< "0. Quit" << std::endl
			<< ": ";
		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			addBook();
			break;
		case 2:
			deleteBook();
			break;
		case 3:
			listBooks();
			break;
		case 4:
			addCustomer();
			break;
		case 5:
			deleteCustomer();
			break;
		case 6:
			listCustomers();
			break;
		case 7:
			borrowBook();
			break;
		case 8:
			reserveBook();
			break;
		case 9:
			returnBook();
			break;
		case 0:
			quit = true;
			break;
		}
		std::cout << std::endl;
	}
	save();
}

bool Library::lookupBook(const std::string& author, const std::string& title, Book* bookPtr) const {
	for (const auto& object : s_bookMap) {
		const Book& books = object.second;
		if ((books.author() == author) && (books.title() == title)) {
			if (bookPtr)
				*bookPtr = books;
			return true;
		}
	}
	return false;
}

bool Library::lookupCustomer(const std::string& author, const std::string& title, Customer* customerPtr) const {
	for (const auto& object : s_customerMap) {
		const Customer& customers = object.second;
		if ((customers.name() == author) && (customers.address() == title)) {
			if (customerPtr)
				*customerPtr = customers;
			return true;
		}
	}
	return false;
}

void Library::addBook(void) {
	string author;
	cout << "Author: ";
	cin >> author;
	string title;
	cout << "Title: ";
	cin >> title;
	if (lookupBook(author, title)) {
		cout << endl << "The book "" << title << "" by "
			<< author << " already exists." << endl;
		return;
	}
	Book books(author, title);
	s_bookMap[books.bookId()] = books;
	cout << endl << "Added: " << books << endl;
}

void Library::deleteBook() {
	string author;
	cout << "Author: ";
	cin >> author;
	string title;
	cout << "Title: ";
	cin >> title;
	Book books;
	if (!lookupBook(author, title, &books)) {
		cout << endl << "There is no book "" << title << "" by "
			<< "author " << author << "." << endl;
		return;
	}
	for (auto entry : s_customerMap) {
		Customer& customers = entry.second;
		customers.returnBook(books.bookId());
		customers.unreserveBook(books.bookId());
		s_customerMap[customers.id()] = customers;
	}
	s_bookMap.erase(books.bookId());
	cout << endl << "Deleted." << endl;
}


void Library::listBooks(void) {
	if (s_bookMap.empty()) {
		cout << "No books." << endl;
		return;
	}
	for (auto& entry : s_bookMap) {
		const Book& books = entry.second;
		cout << books << endl;
	}
}

void Library::addCustomer(void) {
	string name;
	cout << "Name: ";
	cin >> name;
	string address;
	cout << "Address: ";
	cin >> address;
	if (lookupCustomer(name, address)) {
		cout << endl << "A customer with name " << name
			<< " and address " << address << " already exists."
			<< endl;
		return;
	}
	Customer customers(name, address);
	s_customerMap.insert({customers.})
	s_customerMap[customers.id()] =i customers;
	cout << endl << "Added." << endl;
}


void Library::deleteCustomer(void) {
	string name;
	cout << "Name: ";
	cin >> name;
	string address;
	cout << "Address: ";
	cin >> address;
	Customer customers;
	if (!lookupCustomer(name, address, &customers)) {
		cout << endl << "There is no customer with name " << name
			<< " and address " << address << "." << endl;
		return;
	}
	if (customers.hasBorrowed()) {
		cout << "Customer " << name << " has borrowed at least "
			<< "one book and cannot be deleted." << endl;
		return;
	}
	
	for (auto entry : s_bookMap) {
		Book& books = entry.second;
		books.unreserveBookation(customers.id());
		s_bookMap[books.bookId()] = books;
	}
	cout << endl << "Deleted." << endl;
	s_customerMap.erase(customers.id());
}



