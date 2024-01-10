/*
    book.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#include "book.h"
#include "member.h"

Book::Book(int bookID, std::string bookName, std::string authorFirstName, 
std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
    this->returnBook();
}
std::string Book::getbookID()
{
    // Converting bookID to string since method returns string
    return std::to_string(this->bookID);
}

std::string Book::getbookName()
{
    return this->bookName;
}
std::string Book::getAuthorFirstName()
{
    return this->authorFirstName;
}
std::string Book::getAuthorLastName()
{
    return this->authorLastName;
}
Date Book::getDueDate()
{
    return this->dueDate;
}
void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}
void Book::returnBook()
{
    // Creating a temporary Date object
    Date emptyDate;
    // Setting the book's return date to 0
    emptyDate.year = 0;
    emptyDate.day = 0;  
    emptyDate.month = 0;
    emptyDate.dateFormatted = "";
    // Setting the book's due date variables to 0, meaning that it is available
    setDueDate(emptyDate);

}
void Book::borrowBook(Member* borrower, Date dueDate)
{
    this->borrower = borrower;
    setDueDate(dueDate);
}
