#include "customer.h"
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


int Customer::MaxCustomerId = 0;

void Customer::read(std::ifstream& inStream) {
	inStream.read((char*)&m_customerId, sizeof m_customerId);
	std::getline(inStream, m_name);
	std::getline(inStream, m_address);
	{ int loanSetSize;
	inStream.read((char*)&loanSetSize, sizeof loanSetSize);
	for (int count = 0; count < loanSetSize; ++count) {
		int bookId;
		inStream.read((char*)&bookId, sizeof bookId);
		m_loanSet.insert(bookId);
	}
	}
	{ int reservationListSize;
	inStream.read((char*)&reservationListSize,
		sizeof reservationListSize);
	for (int count = 0; count < reservationListSize; ++count) {
		int bookId;
		inStream.read((char*)&bookId, sizeof bookId);
		m_loanSet.insert(bookId);
	}
	}
}

void Customer::write(std::ofstream& outStream) const {
	outStream.write((char*)&m_customerId, sizeof m_customerId);
	outStream << m_name << std::endl;
	outStream << m_address << std::endl;
	{ int loanSetSize = m_loanSet.size();
	outStream.write((char*)&loanSetSize, sizeof loanSetSize);
	for (int bookId : m_loanSet) {
		outStream.write((char*)&bookId, sizeof bookId);
	}
	}
	{ int reservationListSize = m_reservationSet.size();
	outStream.write((char*)&reservationListSize,
		sizeof reservationListSize);
	for (int bookId : m_reservationSet) {
		outStream.write((char*)&bookId, sizeof bookId);
	}
	}
}

void Customer::borrowBook(int bookId) {
	m_loanSet.insert(bookId);
}

void Customer::reserveBook(int bookId) {
	m_reservationSet.insert(bookId);
}

void Customer::returnBook(int bookId) {
	m_loanSet.erase(bookId);
}
void Customer::unreserveBook(int bookId) {
	m_reservationSet.erase(bookId);
}

std::ostream& operator<<(std::ostream& outStream, const Customer& customers) {
	outStream << customers.m_customerId << ". " << customers.m_name
		<< ", " << customers.m_address << ".";
	if (!customers.m_loanSet.empty()) {
		outStream << std::endl << " Borrowed books: ";
		bool first = true;
		for (int bookId : customers.m_loanSet) {
			outStream << (first ? "" : ",")
				<< Library::s_bookMap[bookId].author();
			first = false;
		}
	}
	if (!customers.m_reservationSet.empty()) {
		outStream << std::endl << " Reserved books: ";
		bool first = true;
		for (int bookId : customers.m_reservationSet) {
			outStream << (first ? "" : ",")
				<< Library::s_bookMap[bookId].title();
			first = false;
		}
	}
	return outStream;
}






