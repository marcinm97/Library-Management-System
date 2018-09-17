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