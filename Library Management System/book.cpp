#include "book.h"
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

int Book::MaxBookId = 0;

Book::Book(const std::string& author, const std::string& title):m_bookId(MaxBookId++),
m_author(author), m_title(title) {}

void Book::write(std::ofstream& outStream) const { // saving datas to file
	outStream.write((char*)&m_bookId, sizeof m_bookId);
	outStream << m_author << std::endl;
	outStream << m_title << std::endl;

	outStream.write((char*)&m_borrowed, sizeof m_borrowed);
	outStream.write((char*)&m_customerId, sizeof m_customerId);

	{ int reservationListSize = m_reservationList.size();
	outStream.write((char*)&reservationListSize, sizeof reservationListSize);
	for (auto id : m_reservationList)
		outStream.write((char*)&id, sizeof id);
	}
}

void Book::read(std::ifstream& inStream) { // reading datas from file
	inStream.read((char*)&m_bookId, sizeof m_bookId);
	std::getline(inStream, m_author);
	std::getline(inStream, m_title);
	inStream.read((char*)& m_borrowed, sizeof m_borrowed);
	inStream.read((char*)& m_customerId, sizeof m_customerId);

	{ int reservationListSize;
	inStream.read((char*)&reservationListSize,
		sizeof reservationListSize);
	for (int count = 0; count < reservationListSize; ++count) {
		int customerId;
		inStream.read((char*)&customerId, sizeof customerId);
		m_reservationList.push_back(customerId);
		}
	}
}

void Book::borrowBook(int customerId) {
	m_borrowed = true;
	m_customerId = customerId;
}

int Book::reserveBook(int customerId) {
	m_reservationList.push_back(customerId);
	return m_reservationList.size();  // return how many people reserved the book
}

void Book::returnBook() {
	m_borrowed = false;
}

void Book::unreserveBookation(int customerId) {
	m_reservationList.remove(customerId);
}

std::ostream& operator<<(std::ostream& outStream, const Book& books) {
	outStream << """ << book.m_title << "" by " << books.m_author;

	if (books.m_borrowed) {
		outStream << std::endl << " Borrowed by: "
			<< Library::s_customerMap[books.m_customerId].name()
			<< ".";
	}
	if (!books.m_reservationList.empty()) {
		outStream << std::endl << " Reserved by: ";
		bool first = true;
		for (int customerId : books.m_reservationList) {
			outStream << (first ? "" : ",")
				<< Library::s_customerMap[customerId].name();
			first = false;
		}
		outStream << ".";
	}
	return outStream;
}