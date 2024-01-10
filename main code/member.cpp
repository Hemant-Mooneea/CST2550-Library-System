/*
    member.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#include "member.h"
#include "book.h"
Member::Member(int memberId, std::string name, std::string address, 
std::string email)
{
    
    this->memberId = memberId;
    setEmail(email);
    setAddress(address);
    setName(name);

}
std::string Member::getMemberID()
{   
    // Converting memberId to string since method returns string
    return std::to_string(this->memberId);
}

std::vector<Book>& Member::getBooksBorrowed()
{
    return this->booksLoaned;
}

void Member::setBooksBorrowed(Book book)
{   
    this->booksLoaned.push_back(book);
}