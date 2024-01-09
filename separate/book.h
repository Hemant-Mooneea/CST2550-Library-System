#ifndef _BOOK_H_
#define _BOOK_H_
#include <string>
#include "date.h"

class Member;

class Book
{
    private:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        Date dueDate;
        Member* borrower;
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
        void borrowBook(Member* borrower, Date dueDate);
};
#endif