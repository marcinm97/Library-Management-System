#pragma once
#ifndef library
#define library
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
#include <functional>
#include "book.h"
#include "customer.h"

class Library {
public:
	Library();
private:
	static std::string s_binaryPath;
	bool lookupBook(const std::string& author, const std::string& title, Book* bookPtr = nullptr) const;
	bool lookupCustomer(const std::string& name, const std::string& address,
		Customer* customerPtr = nullptr) const;
	void addBook();
	void deleteBook();
	void listBooks();
	void addCustomer();
	void deleteCustomer();
	void listCustomers();
	void borrowBook();
	void reserveBook();
	void returnBook();
	void load();
	void save();
public:
	static std::map<int, Book> s_bookMap;
	static std::map<int, Customer> s_customerMap;
	static std::map<int, int> bookLoanMap;
	static std::map<int, std::set<int>> bookReservationSetMap;

	static std::map<int, std::set<int>> customerLoanSetMap;
	static std::map<int, std::set<int>> customerReservationSetMap;
};




#endif // !library
