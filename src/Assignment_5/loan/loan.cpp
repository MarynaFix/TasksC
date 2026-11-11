#include "loan.h"
Loan::Loan(const Customer& customer, const Book& book, const std::string& startTime)
    : m_customerId(customer.getId())
    , m_isbn(book.getIsbn())
    , m_startTime(startTime)
    , m_duration(DefaultDuration)

{
}
Loan::Loan(int customerId, std::string isbn, std::string startTime, int duration)
    : m_customerId(customerId)
    , m_isbn(isbn)
    , m_startTime(startTime)
    , m_duration(duration)
{
}
int Loan::getCustomerId() const
{
    return m_customerId;
}
std::string Loan::getIsbn() const { return m_isbn; }
int Loan::getDuration() const { return m_duration; }
std::string Loan::getStartTime() const { return m_startTime; }

