#pragma once
#ifndef customer
#define customer
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

class Customer {
private:
	int m_customerId;
	std::string m_name, m_address;
	std::set<int> m_loanSet, m_reservationSet;
public:
	Customer() {}
	Customer(const std::string& name, const std::string& address) : m_name(name), m_address(address)
	, m_customerId(++MaxCustomerId) {}
	void read(std::ifstream& inStream);
	void write(std::ofstream& outStream) const;
	void borrowBook(int bookId);
	void reserveBook(int bookId);
	void returnBook(int bookId);
	void unreserveBook(int bookId);
	bool hasBorrowed() const { return !m_loanSet.empty(); }
	const std::string& name() const { return m_name; }
	const std::string& address() const { return m_address; }
	int id() const { return m_customerId; }
	static int MaxCustomerId;
	friend std::ostream& operator<<(std::ostream& outStream,
		const Customer& customers);

};


#endif // !customer