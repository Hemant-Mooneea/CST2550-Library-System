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

};

class Book
{
    public:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        Date dueDate;
        Member borrower;
    private:
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
