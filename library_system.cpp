#include <iostream>
#include <vector>
#include "library_system.h"

//Methods for Class Person
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

//Methods for Librarian Class
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
//Methods for Member Class
Member::Member(int memberId, std::string name, std::string address, 
std::string email)
{

}
std::string Member::getMemberID()
{

}

std::vector<Book *> Member::getBooksBorrowed()
{

}

void Member::setBooksBorrowed(Book book)
{

}
//Methods for Book Class
Book::Book(int bookID, std::string bookName, std::string authorFirstName, 
std::string authorLastName)
{

}
std::string Book::getbookID()
{

}

std::string Book::getbookName()
{

}

std::string Book::getAuthorFirstName()
{

}
std::string Book::getAuthorLastName()
{

}
Date Book::getDueDate()
{

}
void Book::setDueDate(Date dueDate)
{

}
void Book::returnBook()
{

}
void Book::borrowBook(Member borrower, Date dueDate)
{

}

