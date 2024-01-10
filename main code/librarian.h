/*
    librarian.h
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#ifndef _LIBRARIAN_H_
#define _LIBRARIAN_H_
#include "person.h"
#include <string>
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
#endif