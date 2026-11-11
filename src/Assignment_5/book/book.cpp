#include "book.h"
Book::Book(const std::string& title, const std::string& author, const std::string& isbn)
    : m_title(title)
    , m_author(author)
    , m_isbn(isbn)
    , m_total(1)
    , m_available(1)

{
}
const std::string& Book::getTitle() const { return m_title; }
const std::string& Book::getAuthor() const { return m_author; }
const std::string& Book::getIsbn() const { return m_isbn; }
int Book::getTotal() const { return m_total; }
int Book::getAvailable() const { return m_available; }

void Book::setTotal(int number)
{
    m_total = number;
}
void Book::setAvailable(int number)
{
    m_available = number;
}