#pragma once
#include "book/book.h"
#include "customer/customer.h"
#include <optional>
#include <string>
#include <vector>
class Loan {
private:
    int m_customerId;
    std::string m_isbn;
    std::string m_startTime;
    int m_duration;

    public:
    Loan(int customerId, std::string isbn, std::string startTime, int duration);
    static const int DefaultDuration = 28;

    Loan(const Customer& customer, const Book& book, const std::string& startTime);

    int getCustomerId() const;
    std::string getIsbn() const;
    std::string getStartTime() const;
    int getDuration() const;

  
};