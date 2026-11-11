#include "libraryFactory.h"
#include "utils/utils.h"
#include <iostream>
std::optional<Library> LibraryFactory::createLibrary(const std::string& directoryPath)
{
    std::string path = directoryPath;
    if (!path.empty() && path.back() != '/' && path.back() != '\\') {
        path += "/";
    }
    std::vector<Book> books;
    std::vector<Customer> customers;
    std::vector<Loan> loans;

    Library library({}, {}, {});

    books.clear();
    customers.clear();
    loans.clear();

    bool booksLoaded = loadData(path + "books.csv", books,
        [&library](const std::vector<std::string>& f) { return library.bookFromCsv(f); });
    bool customersLoaded = loadData(path + "customers.csv", customers,
        [&library](const std::vector<std::string>& f) { return library.customerFromCsv(f); });
    bool loansLoaded = loadData(path + "loans.csv", loans,
        [&library](const std::vector<std::string>& f) { return library.loanFromCsv(f); });

    if (booksLoaded && customersLoaded && loansLoaded) {

        return Library(books, customers, loans);

    } else {

        std::cerr << "One or more files can't be opened" << std::endl;
        return std::nullopt;
    }
}
