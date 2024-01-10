/*
    member.h
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#ifndef _MEMBER_H_
#define _MEMBER_H_
#include <string>
#include <vector>
#include "person.h"

// Forward declaration of Book class
class Book;

class Member : public Person
{
    private:
        int memberId;
        std::vector <Book> booksLoaned;
    public:  
        Member() = default; 
        Member(int memberId, std::string name, std::string address,
        std::string email);
        std::string getMemberID();
        std::vector <Book>& getBooksBorrowed();
        void setBooksBorrowed(Book book);  
};
#endif