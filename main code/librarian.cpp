/*
    librarian.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 11/01/24
*/
#include "librarian.h"
#include "book.h"
#include "member.h"
#include "date.h"
#include "utilities.h"

#include <iostream>
#include <vector>
/*
    Constructor for Librarian object
    @params:
            staffID: ID of the librarian
            Name: Name of the librarian
            address: Address of the librarian
            email: Email of the librarian
            salary: Salary of the librarian
    @return: none
*/
Librarian::Librarian(int staffID, std::string name, std::string address,
std::string email, int salary)
{
    this->staffId = staffID;
    this->salary = salary;
    setName(name);
    setAddress(address);
    setEmail(email);
}
/*
    addMember allows the librarian to add new members to the library by taking
    their information and validating them. The method also assigns them a 
    memberID which is incremented by one for each new member.
    @param: none
    @return: none
*/
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
/*
    issueBook allows the librarian to issue a book to a member. It checks the
    availabiltiy of a book by seeing if it has a due date and displays an 
    error message if unavailable. The method then sets the due date of the book
    which is 3 days from the current date using the getDate() function.
    @param:
            memberID: the memberID of the member who wants to borrow a book
            bookID: the bookID of the book which the member wants to borrow
    @return: none     
*/
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
/*
    returnBook allows a member to return a book. It checks if the member 
    borrowed any books and displays an error message if not.
    
    The method then checks if the member borrowed a book with the bookID which
    is passed as parameter and displays and error message if not.
    
    Additionally, the method removes the book from the member's borrowedBooks
    vector

    @param:
            memberID: the memberID of the member who wants to return a book
            bookID: the bookID of the book which the member wants to return
    @return: none   
*/
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
/*
    displayBorrowedBooks allows the librarian to view all the borrowed books of
    a member.
    It checks if the member borrowed any books and displays an error message if 
    not.
    The method displays the book name, bookID and due date of all of the books
    borrowed by the member 

    @param: the memberID of the member whom we want to display all of their
            borrowed books
    @return: none   
*/
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
/*
    calcFine is used to calculate fines when a member returns a book.
    The method makes use of the te getDifferenceInDays function to obtain the 
    number of days between today and the dueDate of the book which the member
    wants to return and displays the fines if any
    @param: the memberID of the member whom we want to calculate fines
    @return: none
*/
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
/*
    Getter for staffID
    @param: none
    @return: the staffID of a librarian
*/
int Librarian::getStaffID()
{
    return this->staffId;
}
/*
    Setter for staffID
    @param: the staffID of the librarian
    @return: none
*/
void Librarian::setStaffID(int staffID)
{
    this->staffId = staffID;
}
/*
    Getter for salary
    @param: none
    @return: the salary of a librarian
*/
int Librarian::getSalary()
{
    return this->salary;
}
/*
    Setter for salary
    @param: the salary of the librarian
    @return: none
*/
void Librarian::setSalary(int salary)
{
    this->salary = salary;
}