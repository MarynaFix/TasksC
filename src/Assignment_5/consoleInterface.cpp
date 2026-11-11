#include "consoleInterface.h"
#include "./customer/customer.h"
#include "./library/library.h"
#include "./libraryFactory/libraryFactory.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

ConsoleInterface::ConsoleInterface( Library& library, const std::string& pathString)
    : m_library(library)
    , m_pathString(pathString)
{
}

void ConsoleInterface::printCustomers() const
{
    std::cout << "\n--- Current Customers ---\n";
    for (const auto& c : m_library.getCustomers()) {
        std::cout << "ID: " << c.getId() << " | " << c.getName() << " " << c.getSurname() << "\n";
    }
    std::cout << "\n";
}

void ConsoleInterface::printBooks() const
{
    std::cout << "\n--- Current Books ---\n";
    for (const auto& b : m_library.getBooks()) {
        std::cout << "ISBN: " << b.getIsbn() << " | \"" << b.getTitle()
                  << "\" by " << b.getAuthor()
                  << " (Available: " << b.getAvailable() << "/" << b.getTotal() << ")\n";
    }
    std::cout << "\n";
}

void ConsoleInterface::printLoans() const
{
    std::cout << "\n--- Active Loans ---\n";
    for (const auto& l : m_library.getLoans()) {
        std::cout << "Customer ID: " << l.getCustomerId()
                  << " | Book ISBN: " << l.getIsbn()
                  << " | Date: " << l.getStartTime() << "\n";
    }
    std::cout << "\n";
}

int ConsoleInterface::run()
{
    int option = -1;

    std::cout << "\nLibrary\n";
    std::cout << "Select an option:\n";
    std::cout << "Add new customer 1\n";
    std::cout << "Add new book 2\n";
    std::cout << "To borrow a book 3\n";
    std::cout << "To return a book 4\n";
    std::cout << "Exit 0\n";
    std::cin >> option;

    if (!std::cin) {
        if (std::cin.eof()) {
            return 0;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number from the menu.\n";
        return -1;
    }

    switch (option) {
    case 1: {
        std::string name;
        std::string surname;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter customer's name: ";
        std::getline(std::cin, name);
        std::cout << "Enter customer's surname: ";
        std::getline(std::cin, surname);

        Customer customer(name, surname);
        AddResult result = m_library.addCustomer(customer);

        if (result == AddResult::AlreadyExists) {
            std::cerr << "Error: Customer with this ID already exists.\n";
            return -1;
        }
        if (result == AddResult::Success) {

            std::cout << " Customer added to library database.\n";
            return 1;
        }
        return -1;
    }
    case 2: {
        std::string title;
        std::string author;
        std::string isbn;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter book's title: ";
        std::getline(std::cin, title);
        std::cout << "Enter book's author: ";
        std::getline(std::cin, author);
        std::cout << "Enter ISBN: ";
        std::cin >> isbn;

        std::cout << "Do you want to enter the total quantity? (1 - yes, 2 - no): ";
        int choiceTotal = 0;
        std::cin >> choiceTotal;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 or 2.\n";
            return -1;
        }

        Book book(title, author, isbn);
        if (choiceTotal == 1) {
            int totalNum = 0;
            std::cout << "Enter total quantity: ";
            std::cin >> totalNum;
            if (!std::cin || totalNum < 1) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Quantity must be a positive number.\n";
                return -1;
            }
            book.setTotal(totalNum);
            book.setAvailable(totalNum);
        } else if (choiceTotal != 2) {
            std::cout << "Please enter 1 or 2.\n";
            return -1;
        }

        AddResult result = m_library.addBook(book);

        if (result == AddResult::Success) {
            std::cout << "Book added to a library database.\n";
            return 2;
        }
        if (result == AddResult::AlreadyExists) {

            std::cerr << "Error: This book is already in the library.\n";
            return -1;
        }
        return -1;
    }
    case 3: {
        int customerId;
        std::string bookIsbn;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter customer id: ";
        std::cin >> customerId;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Customer ID must be a number.\n";
            return -1;
        }

        std::cout << "Enter book's ISBN: ";
        std::cin >> bookIsbn;

        LendResult result = m_library.lendBook(customerId, bookIsbn);

        switch (result) {

        case LendResult::Success:
            std::cout << "Book successfully lent to customer.\n";
            return 3;

        case LendResult::BookNotFound:
            std::cout << "Error: Book with ISBN " << bookIsbn << " not found.\n";
            return -1;

        case LendResult::CustomerNotFound:
            std::cout << "Error: Customer with ID " << customerId << " not found.\n";
            return -1;
        case LendResult::NoCopiesAvailable:
            std::cout << "Error: No available copies of this book.\n";
            return -1;
        }
        break;
    }

    case 4: {
        int customerId;
        std::string isbn;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter customer ID for return: ";
        std::cin >> customerId;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Customer ID must be a number.\n";
            return -1;
        }

        std::cout << "Enter book's ISBN for return: ";
        std::cin >> isbn;

        ReturnResult result = m_library.returnBook(customerId, isbn);
        switch (result) {
        case ReturnResult::LoanNotFound:
            std::cerr << "Error: Active loan for this customer and book not found.\n";
            return -1;

        case ReturnResult::Success:
            std::cout << "Book successfully returned.\n";
            return 4;
        }

        break;
    }
    case 0:
        std::cout << "Goodbye!\n";
        return 0;
    default:
        std::cout << "Invalid option!\n";
        return -1;
    }

    return -1;
}