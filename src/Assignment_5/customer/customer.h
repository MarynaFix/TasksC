#pragma once
#include <string>
class Customer {
private:
    static int next_id;
    std::string m_name;
    std::string m_surname;
    int m_id;

    
    public:
    Customer(std::string name, std::string surname, int id);
    Customer(const std::string& name, const std::string& surname);
    std::string getName() const;
    std::string getSurname() const;
    int getId() const;
    static int getNextId();
    static void setNextId(int number);
};