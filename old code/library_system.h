/*
    library_system.h
    Author: M00935155
    Created:16/12/23
    Updated:09/01/24
*/
#ifndef _LIBRARY_SYSTEM_H_
#define _LIBRARY_SYSTEM_H_

#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

// class declarations to avoid referencing errors
class Book;
class Person;
class Librarian;
class Member;

// global variables definitions
extern std::vector<Book> libraryBooks;
extern std::vector<Member> libraryMembers;
extern int memberIDCounter;

struct Date 
{
    //unsigned used to prevent negative numbers
    unsigned year;
    unsigned month;
    unsigned day;
    std::string dateFormatted;
};

class Person
{
    private:
        std::string name;
        std::string address;
        std::string email;
    public:
        std::string getName();
        void setName(std::string name);
        std::string getAddress();
        void setAddress(std::string address);
        std::string getEmail();
        void setEmail(std::string email);
};

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

class Librarian : public Person
{ 
    private:
        int staffId;
        int salary;
    public:
        Librarian() = default; 
        Librarian(int staffID, std::string name, std::string address,
        std::string email, int salary);
        void addMember();
        void issueBook(int memberID, int bookID);
        void returnBook(int memberID, int bookID);
        void displayBorrowedBooks(int memberID);
        void calcFine(int memberID);
        int getStaffID();
        void setStaffID(int staffID);
        int getSalary();
        void setSalary(int salary);
};
class Book
{
    private:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        Date dueDate;
        Member borrower;
    public:
        Book() = default;
        Book(int bookID, std::string bookName, std::string authorFirstName,
        std::string authorLastName);
        std::string getbookID();
        std::string getbookName();
        std::string getAuthorFirstName();
        std::string getAuthorLastName();
        Date getDueDate();
        void setDueDate(Date dueDate);      
        void returnBook();
        void borrowBook(Member borrower, Date dueDate);
};
#endif
