/*
    member.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 11/01/24
*/
#include "member.h"
#include "book.h"
/*
    Constructor for Member object
    @params:
            memberId: ID of a member
            name: Name of the member
            address: Address of the member
            email: Email of the member
    @return: none
*/
Member::Member(int memberId, std::string name, std::string address, 
std::string email)
{
    
    this->memberId = memberId;
    setEmail(email);
    setAddress(address);
    setName(name);

}
/*
    Getter for a member's ID
    @param: none
    @return: a member's ID
*/
std::string Member::getMemberID()
{   
    // Converting memberId to string since method returns string
    return std::to_string(this->memberId);
}
/*
    Getter for a member's book borrowed
    @param: none
    @return: a vector containing all of the books borrowed by a member
*/
std::vector<Book>& Member::getBooksBorrowed()
{
    return this->booksLoaned;
}
/*
    setBooksBorrowed adds a book object to a member's vector which contains all
    of the book they borrowed
    @param: A Book object
    @return: none
*/
void Member::setBooksBorrowed(Book book)
{   
    this->booksLoaned.push_back(book);
}