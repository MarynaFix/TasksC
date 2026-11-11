#include "customer.h"

int Customer::next_id = 1;

Customer::Customer(
    const std::string& name, const std::string& surname)
    : m_name(name)
    , m_surname(surname)
    , m_id(next_id++)
{
}
std::string Customer::getName() const { return m_name; }
std::string Customer::getSurname() const { return m_surname; }
int Customer::getId() const { return m_id; }
int Customer::getNextId() { return next_id; }

void Customer::setNextId(int number)
{
    next_id = number;
}

Customer::Customer(std::string name, std::string surname, int id)
    : m_name(name)
    , m_surname(surname)
    , m_id(id)
{
}
