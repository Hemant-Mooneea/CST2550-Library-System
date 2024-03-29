/*
    library_system.cpp
    Author: M00935155
    Created:19/12/23
    Updated:09/01/24
*/

#include "library_system.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Global Variable used for storage of books
std::vector<Book> libraryBooks;
// Global Variable used for storage of members
std::vector<Member> libraryMembers;
// Global Variable used for new memberID
int memberIDCounter = 0;

// function declaration to avoid referencing errors
std::string validateName();
std::string validateEmail();
std::string validateAddress();
int getDifferenceInDays(Date currentDate, Date dueDate);
int checkBookID();
int checkMemberID();
Date getDate(std::string type);



// Methods for Class Person
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

// Methods for Librarian Class
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
    // Increasing the counter to prevent duplicate memberID
    memberIDCounter ++;
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string name, address, email;
    std::cout << "Enter Member Details: \n";
    // Performing data validation on each member info
    name = validateName();
    address = validateAddress();
    email = validateEmail();
    // Creating a new member object for the new member using their info
    Member newMember(memberIDCounter, name, address, email);
    libraryMembers.push_back(newMember);
}
void Librarian::issueBook(int memberID, int bookID)
{   
    // Decrement memberID and bookID since vector starts at index 0
    memberID --;
    bookID --;
    Date dueDate = libraryBooks[bookID].getDueDate();
    // dueDate.day == 0 means that it is available to be borrowed
    if (dueDate.day != 0)
    {
        std::cout << "This book is not available!\n";
        return;
    }
    libraryBooks[bookID].setDueDate(getDate("Three Days"));
    // Adding the book object to the booksLoaned vector of a specific member
    libraryMembers[memberID].setBooksBorrowed(libraryBooks[bookID]);
    std::cout << "Book has been issued!\n";
}
void Librarian::returnBook(int memberID, int bookID)
{
    // Decrement memberID and bookID since vector starts at index 0
    memberID --;
    bookID --;
    Book tempBook;
    // Vector which points towards the address of a member's bookLoaned vector
    std::vector<Book>& borrowedBooks 
    = libraryMembers[memberID].getBooksBorrowed();
    // Checking if the member has any book borrowed using the size of the vector
    if (static_cast<int>(borrowedBooks.size()) == 0)
    {
        std::cout << "Member has no books borrowed!\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(borrowedBooks.size()); i++)
    {   // Checking if the member borrowed a book with that bookID
        if (libraryBooks[bookID].getbookID() == borrowedBooks[i].getbookID())
        {   
            // Copying the book object which we want to return
            tempBook = libraryBooks[bookID];
            /*
                Pushing the book object at the last position in the vector which
                allows for easy retrieval of the book's data since we can access 
                the last index of the vector
            */     
            borrowedBooks.push_back(tempBook);
            // Calculating fines, if any
            this->calcFine(memberID);
            // Removing the extra tempBook object since it is uneeded
            borrowedBooks.pop_back();

            libraryBooks[bookID].returnBook();
            // Removing the returned book from member's bookLoaned vector
            borrowedBooks.erase(borrowedBooks.begin() + i);
            return;
        }
    }
    std::cout << "Member did not borrow that book!\n";
}
void Librarian::displayBorrowedBooks(int memberID)
{
    // Decrement memberID since vector starts at index 0
    memberID --;
    std::vector <Book> currentMemberBooks;
    Date dueDate;

    std::cout << "Books borrowed by " + libraryMembers[memberID].getName() <<
    std::endl;
    
    currentMemberBooks = libraryMembers[memberID].getBooksBorrowed();
    // Checking if member borrowed any book based on the vector size
    if(static_cast<int>(currentMemberBooks.size()) == 0)
    {
        std::cout << "Member has no books borrowed!\n";
        return;
    }
    // Iterating the vector and outputing all book borrowed and their due dates
    for (int i = 0; i < static_cast<int>(currentMemberBooks.size()); i++)
    {   
        dueDate = currentMemberBooks[i].getDueDate();
        std::cout << currentMemberBooks[i].getbookName() +"\n" +
        "BookID: " + currentMemberBooks[i].getbookID() + "\n" +
        "Date Of Return: " + dueDate.dateFormatted  << std::endl;
    }
}
void Librarian::calcFine(int memberID)
{   
    Date currentDate = getDate("Today");
    // Obtaining last book in the vector
    Book tempBook = libraryMembers[memberID].getBooksBorrowed().back();
    Date dueDate = tempBook.getDueDate();
    int differenceInDays = getDifferenceInDays(currentDate, dueDate);
    // If the difference in days is <= 0 then due date has NOT been exceeded
    if (differenceInDays <= 0 )
    {
        std::cout << "Book returned on time, no fines!\n";
    }  
    else
    {   
        std::cout << "Fines are due: £" + differenceInDays << std::endl;
    }
}
int Librarian::getStaffID()
{
    return this->staffId;
}
void Librarian::setStaffID(int staffID)
{
    this->staffId = staffID;
}
int Librarian::getSalary()
{
    return this->salary;
}
void Librarian::setSalary(int salary)
{
    this->salary = salary;
}
//Methods for Member Class
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

// Methods for Book Class
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
    // Setting the book's borrower to empty string
    this->borrower.setName("");
    this->borrower.setAddress("");
    this->borrower.setEmail("");
    // Setting the book's return date to 0
    emptyDate.year = 0;
    emptyDate.day = 0;
    emptyDate.month = 0;
    emptyDate.dateFormatted = "";
    // Setting the book's due date variables to 0, meaning that it is available
    setDueDate(emptyDate);

}
void Book::borrowBook(Member borrower, Date dueDate)
{
    this->borrower = borrower;
    setDueDate(dueDate);
}
