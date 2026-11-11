#pragma once
#include "library/library.h"
#include <string>
class ConsoleInterface {
private:
    Library& m_library;
    std::string m_pathString;

public:
    ConsoleInterface( Library& library, const std::string& pathString);
    void printCustomers() const;
    void printBooks() const;
    void printLoans() const;
    int run();
};