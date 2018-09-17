#pragma once
#ifndef book
#define book
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
#include "library.h"

class Book {
private:
	std::string m_author, m_title;
	int m_bookId;
	bool m_borrowed = false;
	int m_customerId;
	std::list<int> m_reservationList;
public:
	Book() {}
	Book(const std::string& author, const std::string& title);
	const std::string& author() { return m_author; }
	const std::string& title() { return m_title; }
	void read(std::ifstream& inStream);
	void write(std::ofstream& outStream) const;
	void borrowBook(int customerId);
	int reserveBook(int customerId);
	void returnBook();
	void unreserveBookation(int customerId);
	int bookId() const { return m_bookId; }
	bool borrowed() const { return m_borrowed; }
	int customerId() const { return m_customerId; }
	std::list<int>& reservationList() { return m_reservationList; }
	friend std::ostream& operator<<(std::ostream& outStream, const Book& books);
	
	static int MaxBookId;
	~Book() {}

};


#endif // !book
