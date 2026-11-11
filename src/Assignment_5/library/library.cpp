#include "library.h"
#include "utils/utils.h"
#include <algorithm>

LendResult Library::lendBook(int customerId, const std::string& isbn)
{
    std::vector<Customer>::iterator customerIt = std::find_if(m_customers.begin(), m_customers.end(), [customerId](const Customer& c) { return c.getId() == customerId; });
    if (customerIt == m_customers.end()) {

        return LendResult::CustomerNotFound;
    }
    std::vector<Book>::iterator bookIt = std::find_if(m_books.begin(), m_books.end(), [&isbn](const Book& b) { return b.getIsbn() == isbn; });

    if (bookIt == m_books.end()) {

        return LendResult::BookNotFound;
    }
    if (bookIt->getAvailable() <= 0) {

        return LendResult::NoCopiesAvailable;
    }
    bookIt->setAvailable(bookIt->getAvailable() - 1);
    std::string today = getTodayDateString();
    Loan newLoan(*customerIt, *bookIt, today);
    m_loans.push_back(newLoan);

    return LendResult::Success;
}

ReturnResult Library::returnBook(int customerId, const std::string& isbn)
{
    auto loanIt = std::find_if(m_loans.begin(), m_loans.end(),
        [customerId, &isbn](const Loan& l) {
            return l.getCustomerId() == customerId && l.getIsbn() == isbn;
        });
    if (loanIt == m_loans.end()) {

        return ReturnResult::LoanNotFound;
    }
    auto bookIt = std::find_if(m_books.begin(), m_books.end(),
        [&isbn](const Book& b) { return b.getIsbn() == isbn; });

    if (bookIt != m_books.end()) {
        bookIt->setAvailable(bookIt->getAvailable() + 1);
    }
    m_loans.erase(loanIt);

    return ReturnResult::Success;
}

Library::Library(const std::vector<Book>& books, const std::vector<Customer>& customers, const std::vector<Loan>& loans)
    : m_books(books)
    , m_customers(customers)
    , m_loans(loans)
{
}
bool Library::saveToDirectory(const std::string& directoryPath)
{
    std::string path = directoryPath;
    if (!path.empty() && path.back() != '/' && path.back() != '\\') {
        path += "/";
    }
    bool success = true;

    if (!saveData(path + "books.csv", m_books, [this](const Book& b) { return bookToCsv(b); })) {

        success = false;
    }
    if (!saveData(path + "customers.csv", m_customers, [this](const Customer& c) { return customerToCsv(c); })) {

        success = false;
    }
    if (!saveData(path + "loans.csv", m_loans, [this](const Loan& l) { return loanToCsv(l); })) {

        success = false;
    }
    return success;
}
AddResult Library::addCustomer(const Customer& newCustomer)
{
    auto it = std::find_if(m_customers.begin(), m_customers.end(),
        [&newCustomer](const Customer& c) { return c.getId() == newCustomer.getId(); });
    if (it != m_customers.end()) {

        return AddResult::AlreadyExists;
    }

    m_customers.push_back(newCustomer);

    return AddResult::Success;
}
AddResult Library::addBook(const Book& newBook)
{
    auto it = find_if(m_books.begin(), m_books.end(),
        [&newBook](const Book& b) { return b.getIsbn() == newBook.getIsbn(); });
    if (it != m_books.end()) {

        return AddResult::AlreadyExists;
    }

    m_books.push_back(newBook);

    return AddResult::Success;
}

std::string Library::customerToCsv(const Customer& c) const
{
    return c.getName() + "|" + c.getSurname() + "|" + std::to_string(c.getId());
};

std::string Library::bookToCsv(const Book& b) const
{
    return b.getTitle() + "|" + b.getAuthor() + "|" + b.getIsbn() + "|" + std::to_string(b.getTotal()) + "|" + std::to_string(b.getAvailable());
};
std::string Library::loanToCsv(const Loan& l) const
{
    return std::to_string(l.getCustomerId()) + "|" + l.getIsbn() + "|" + l.getStartTime() + "|" + std::to_string(l.getDuration());
};

std::optional<Customer> Library::customerFromCsv(const std::vector<std::string>& fields)
{

    if (fields.size() != 3) {
        return std::nullopt;
    };

    try {
        int id = std::stoi(fields[2]);
        if (id >= Customer::getNextId()) {
            Customer::setNextId(id + 1);
        }
        return Customer(fields[0], fields[1], id);
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<Loan> Library::loanFromCsv(const std::vector<std::string>& fields)
{
    if (fields.size() != 4) {
        return std::nullopt;
    };
    try {
        int customerId = std::stoi(fields[0]);
        int duration = std::stoi(fields[3]);

        return Loan(customerId, fields[1], fields[2], duration);
    } catch (...) {
        return std::nullopt;
    }
};
std::optional<Book> Library::bookFromCsv(const std::vector<std::string>& fields)
{
    if (fields.size() != 5)
        return std::nullopt;

    try {
        int total = std::stoi(fields[3]);
        int available = std::stoi(fields[4]);

        if (total < 0 || available < 0 || available > total) {
            return std::nullopt;
        }

        Book book(fields[0], fields[1], fields[2]);
        book.setTotal(total);
        book.setAvailable(available);
        return book;
    } catch (...) {
        return std::nullopt;
    }
}
