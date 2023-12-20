#include <iostream>
#include <vector>
#include "library_system.h"

std::string Person::getName()
{
    return this->name;
}
std::string Person::getEmail()
{
    return this->email;
}
std::string Person::getAddress()
{
    return this->address;
}
void Person::setName(std::string name)
{
    this->name = name;
}
void Person::setEmail(std::string email)
{
    this->email = email;
}
void Person::setAddress(std::string address)
{
    this->address = address;
}

Librarian::Librarian(int staffID, std::string name, std::string address,
std::string email, int salary)
{
    this->staffId = staffID;
    this->salary = salary;
    setName(name);
    setAddress(address);
    setEmail(email);
}
void Librarian::addMember()
{

}
void Librarian::issueBook(int memberID, int bookID)
{

}
void Librarian::returnBook(int memberID, int bookID)
{

}
void Librarian::displayBorrowedBooks(int memberID)
{

}
void Librarian::calcFine(int memberID)
{

}
int Librarian::getStaffID()
{

}
int Librarian::setStaffID()
{

}
int Librarian::getSalary()
{

}
void Librarian::setSalary(int salary)
{
    
}

Member::Member(int memberId, std::string name, std::string address, std::string email)
{
}

std::string Member::getMemberID()
{
    return std::string();
}

std::vector<Book *> Member::getBooksBorrowed()
{
    return std::vector<Book *>();
}

void Member::setBooksBorrowed(Book book)
{
}
