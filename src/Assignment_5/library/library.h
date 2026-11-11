#pragma once
#include "book/book.h"
#include "customer/customer.h"
#include "loan/loan.h"
#include <optional>
#include <string>
#include <vector>

enum class LendResult {
    Success,
    CustomerNotFound,
    BookNotFound,
    NoCopiesAvailable
};

enum class ReturnResult {
    Success,
    LoanNotFound
};

enum class AddResult {
    Success,
    AlreadyExists
};

class Library {
private:
    std::vector<Book> m_books;
    std::vector<Customer> m_customers;
    std::vector<Loan> m_loans;

public:
    Library(const std::vector<Book>& books, const std::vector<Customer>& customers, const std::vector<Loan>& loans);

    LendResult lendBook(int customerId, const std::string& isbn);
    ReturnResult returnBook(int customerId, const std::string& isbn);

    const std::vector<Book>& getBooks() const { return m_books; }
    const std::vector<Customer>& getCustomers() const { return m_customers; }
    const std::vector<Loan>& getLoans() const { return m_loans; }

    bool saveToDirectory(const std::string& directoryPath);
    AddResult addCustomer(const Customer& newCustomer);
    AddResult addBook(const Book& newBook);

    std::string customerToCsv(const Customer& c) const;
    std::string bookToCsv(const Book& b) const;
    std::string loanToCsv(const Loan& l) const;

    std::optional<Customer> customerFromCsv(const std::vector<std::string>& fields);
    std::optional<Loan> loanFromCsv(const std::vector<std::string>& fields);
    std::optional<Book> bookFromCsv(const std::vector<std::string>& fields);
};