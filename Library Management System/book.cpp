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

void Book::write(std::ofstream& outStream) const {
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

std::ostream& operator<<(std::ostream& outStream, const Book& books) {

}