#pragma once
#include <optional>
#include <string>
#include <vector>
class Book {
private:
    std::string m_title;
    std::string m_author;
    std::string m_isbn;
    int m_total;
    int m_available;

public:
    Book(const std::string& title, const std::string& author, const std::string& isbn);

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
    int getTotal() const;

    int getAvailable() const;
    void setTotal(int number);
    void setAvailable(int number);
};