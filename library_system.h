#ifndef _LIBRARY_SYSTEM_H_
#define _LIBRARY_SYSTEM_H_
    
#include <string>
#include <vector>
#include <date.h>

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
        std::vector <Book*> booksLoaned;
    public:  
        Member(int memberId, std::string name, std::string address,
        std::string email);
        std::string getMember();
        std::vector <Book*> getBooksBorrowed();
        void setBooksBorrowed(Book book;);  
        
};
class Librarian : public Person
{ 
    private:
        int staffId;
        int salary;
    public:
        Librarian(int staffID, std::string name, std::string address,
        std::string email, int salary);
        void addMember();
        void issueBook(int memberID, int bookID);
        void returnBook(int memberID, int bookID);
        void displayBorrowedBooks(int memberID);
        void calcFine(int memberID);
        int getStaffID();
        int setStaffID();
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
        Book(int bookID, std::string bookName, std::string authorFirstName,
        std::string authorLastName);
        std::string getbookID();
        std::string getbookName();
        std::string getAuthorFirstName();
        std::string getAuthorLastName();
        Date getDueDate();
        void setDueDate(dueDate date);  
        void returnBook();
        void borrowBook(Member borrower, dueDate Date)
};
#endif
