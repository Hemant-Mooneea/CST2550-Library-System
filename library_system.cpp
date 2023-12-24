#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "library_system.h"

//Methods for Class Person
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

//Methods for Librarian Class
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

}
void Librarian::issueBook(int memberID, int bookID)
{

}
void Librarian::returnBook(int memberID, int bookID)
{

}
void Librarian::displayBorrowedBooks(int memberID)
{

}
void Librarian::calcFine(int memberID)
{

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
    //converting memberId to string since method returns string
    std::string memberIdString = std::to_string(this->memberId);
    return memberIdString;
}

std::vector<Book *> Member::getBooksBorrowed()
{
    return this->booksLoaned;
}

void Member::setBooksBorrowed(Book* book)
{
    this->booksLoaned.push_back(book);
}
//Methods for Book Class
Book::Book(int bookID, std::string bookName, std::string authorFirstName, 
std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
}
std::string Book::getbookID()
{
    //converting bookID to string since method returns string
    std::string bookIDString = std::to_string(this->bookID);
    return bookIDString;
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

}
void Book::borrowBook(Member borrower, Date dueDate)
{

}

bool hasDigits(std::string str)
{
    bool check;
    for (int i = 0; i < str.length(); i++)  
    {
        check = isdigit(str[i]);
        if (check)
        {
            return false;
        }
    }
    return true;
}
bool hasNonDigits(std::string str) 
{
    bool check;
    for (int i = 0; i < str.length(); i++) 
    {
        check = isdigit(str[i]);
        if (!check)
        {
            return true; 
        }
    }
    return false;
}

bool hasWhiteSpaces(std::string str)
{   
    //iterates throughtout the string to check for a space
    bool check = std::all_of(str.begin(),str.end(),isspace);
    return check;
}
bool hasAtSign(std::string str)
{
    bool check;
    for (int i = 0; i < str.length(); i++) 
    {
        if (str[i] == '@')
        {
            return true; 
        }
    }
    return false;
}
std::string validateName()
{   
    std::string name;
    bool doesNameDigits;
    bool doesNameWhitespaces;
    bool exitLoop;
    do
    {
        doesNameDigits = true;
        doesNameWhitespaces = false;
        exitLoop = true;

        std::cout << "Enter Your Name: ";
        std::cin >> name;
        
        //checks for whitespaces such as "    "
        doesNameWhitespaces = hasWhiteSpaces(name);
        //checks if name has digits
        doesNameDigits = hasDigits(name);
        
        if (doesNameWhitespaces or name.length() == 0)
        {
            std::cout << "Name cannot be blank \n";
            exitLoop = false;
        }
        else if (!doesNameDigits)
        {
            std::cout << "Name cannot contain numbers \n";
            exitLoop = false;
        }
    } while (!exitLoop);

    return name;

}
std::string validateAddress()
{   
    std::string address;
    bool doesNameWhitespaces;
    do
    {
        std::cout << "Enter Your Address: ";
        std::cin >> address;
        
        //checks for whitespaces such as "    "
        doesNameWhitespaces = hasWhiteSpaces(address);

        if (doesNameWhitespaces or address.length() == 0)
        {
            std::cout << "Name cannot be blank \n";
        }
    } while (doesNameWhitespaces);

    return address;
}
std::string validateEmail()
{
    std::string email;
    bool doesContainAtSign;
    bool doesNameWhitespaces;
    bool exitLoop;
    do
    {
        doesContainAtSign = true;
        doesNameWhitespaces = false;
        exitLoop = true;

        std::cout << "Enter Your Email: ";
        std::cin >> email;
        
        //checks for whitespaces such as "    "
        doesNameWhitespaces = hasWhiteSpaces(email);
        //checks if name has digits
        doesContainAtSign = hasAtSign(email);
        
        if (doesNameWhitespaces or email.length() == 0)
        {
            std::cout << "Email cannot be blank \n";
            exitLoop = false;
        }
        else if (!doesContainAtSign)
        {
            std::cout << "Email needs @ sign \n";
            exitLoop = false;
        }
    } while (!exitLoop);
    return email;
}

int validateNumbers(std::string type)
{   
    int number;
    std::string tempNumber;
    bool doesNameWhitespaces;
    bool doesNameDigits;
    bool exitLoop;
    do
    {
        doesNameDigits = false;
        doesNameWhitespaces = false;
        exitLoop = true;

        std::cout << "Enter Your " + type + " :";
        std::cin >> tempNumber;

        //checks for whitespaces such as "    "
        doesNameWhitespaces = hasWhiteSpaces(tempNumber);
        //checks for non digits 
        doesNameDigits = hasNonDigits(tempNumber);
        if (doesNameWhitespaces or tempNumber.length() == 0)
        {
            std::cout << type +" cannot be blank \n";
            exitLoop = false;
        }
        else if (doesNameDigits)
        {   
            std::cout << type + " can only contain numbers \n";
            exitLoop = false;
        }

    } while (!exitLoop);
    number = std::stoi(tempNumber);
    return number;
}

Librarian createNewLibrarian(Librarian newLibrarian)
{
    std::string name, address, email;
    int salary, staffID;
    std::cout << "Welcome Librarian! \n";
    name = validateName();
    address = validateAddress();
    email = validateEmail();
    salary = validateNumbers("Salary");
    staffID = validateNumbers("StaffID");

    newLibrarian.setName(name);
    newLibrarian.setAddress(address);
    newLibrarian.setEmail(email);
    newLibrarian.setSalary(salary);
    newLibrarian.setStaffID(staffID);

    return newLibrarian;
}

int main()
{
    Librarian newLibrarian;
    newLibrarian = createNewLibrarian(newLibrarian);
    return 1;

}