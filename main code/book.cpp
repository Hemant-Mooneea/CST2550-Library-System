/*
    book.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 11/01/24
*/
#include "book.h"
#include "member.h"
/*
    Constructor for Book object
    @params:
            bookID: ID of the book
            bookName: Name of the book
            authorFirstName: First Name of the author
            authorLastName: Last Name of the author
    @return: none
*/
Book::Book(int bookID, std::string bookName, std::string authorFirstName, 
std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
    this->returnBook();
}
/*
    Getter for bookID
    @param: none
    @return: the bookID of a book
*/
std::string Book::getbookID()
{
    // Converting bookID to string since method returns string
    return std::to_string(this->bookID);
}
/*
    Getter for a book's name
    @param: none
    @return: the name of a book
*/
std::string Book::getbookName()
{
    return this->bookName;
}
/*
    Getter for an author's first name
    @param: none
    @return: the first name of an author
*/
std::string Book::getAuthorFirstName()
{
    return this->authorFirstName;
}
/*
    Getter for an author's last name
    @param: none
    @return: the first last of an author
*/
std::string Book::getAuthorLastName()
{
    return this->authorLastName;
}
/*
    Getter for due date of a book
    @param: none
    @return: the due date of a book
*/
Date Book::getDueDate()
{
    return this->dueDate;
}
/*
    Setter for due date of a book
    @param: the due date of a book
    @return: none
*/
void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}
/*
    returnBook creates an empty date variable which sets the date of everything 
    to zero which indicates that the book has no due date
    @param: none
    @return: none
*/
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
/*
    borrowBook assigns the borrower attribute of a book to a member whilst also 
    setting the due date of the book
    @params: 
            borrower: a pointer to a library member
            dueDate: the due date of the book
    @return: none
*/
void Book::borrowBook(Member* borrower, Date dueDate)
{
    this->borrower = borrower;
    setDueDate(dueDate);
}
