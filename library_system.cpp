#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <sstream>
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
    //iterates throughtout the string to check if all characters are spaces
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
std::string checkFilePath()
{
    std::string filePath;
    bool checkFile;
    do
    {
        std::cout << "Input the path to the Books file:\n";
        std::cin >> filePath;
        checkFile = std::filesystem::exists(filePath);  
        if (!checkFile) 
        {
            std::cout << "File does not exist at path: " + filePath + "\n";
        } 
    } while (!checkFile);
    return filePath;
}
void extractBookData(std::string bookData[], std::string line)
{   
    int count;
    std::string word = ""; 
    std::string tempWord = "";

    // used for breaking words 
    std::stringstream s(line);

    bool isWordComplete = true;

    count = 0;
    // seperates each word by using the comma and loops across each word
    while (std::getline(s, word, ',')) 
    { 
        /*
        The following  2 ifs statement are put into place to check for Books
        which have commas in their title.
        */

        /* 
        checking if the first part of the string is " which in the csv file 
        indicates that a string contains a comma within it
        */
        if (word[0] == '"' || isWordComplete == false) 
        {
            tempWord = tempWord + word + ',';
            isWordComplete = false;
        }
        /* 
        checking if the last part of the string is "  meaning that the string is 
        complete
        */
        if (word[word.length() - 1] == '"')
        {   
            // remove the extra comma
            tempWord.erase(tempWord.length() - 1); 
            word = tempWord;
            isWordComplete = true;
        }
        
        if (isWordComplete)
        {
            //removing "" from book titles which have them
            if (word[0] == '"') 
            {
                word.erase(word.begin());
                word.erase(word.end() - 1);
                
            }
            bookData[count] = word;
            count++;
        }
    } 
}
void readBookFile(std::vector<Book>& libraryBooks)
{
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string filePath = checkFilePath();

    std::ifstream file;
    file.open(filePath);
    std::string line, word, bookData[5];

    //getting the first line which does not contain book information
    std::getline(file, line);
    //while loop continues until it reaches end of file
    while (std::getline(file, line)) 
    {
        extractBookData(bookData, line);
        /*Book data in the index are as follows:
        0 : BookID(being converted to integer using stoi)
        1: BookName
        3: Author First Name
        4: Author LastName 
        */
        Book newBook(stoi(bookData[0]),bookData[1],bookData[3],bookData[4]);
        libraryBooks.push_back(newBook);
    }
    file.close();
}
Librarian createNewLibrarian()
{   
    Librarian newLibrarian;
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
Member createMember(int memberID)
{  
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string name, address, email;
    std::cout << "Enter Member Details: \n";
    name = validateName();
    address = validateAddress();
    email = validateEmail();
    Member newMember(memberID, name, address, email);
    return newMember;

}
int findMemberIndex(std::vector<Member>& libraryMembers)
{
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";

    std::string memberName;
    while (true)
    {
        std::cout << "Enter member name (Type EXIT to go back): ";
        std::cin >> memberName;

        if (memberName == "EXIT") 
        {
            return -1; 
        }

        bool found = false;
        for (int i = 0; i < libraryMembers.size(); i++) 
        {
            if (libraryMembers[i].getName() == memberName) 
            {
                return i;
            }
        }

        std::cout << "Member Not Found!\n";
    }
    return -1;
}
int findBookIndex(std::vector<Book>& libraryBooks)
{   
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";

    std::string bookName;
    while (true)
    {
        std::cout << "Enter book name (Type EXIT to go back): ";
        std::cin >>  bookName;

        if (bookName == "EXIT") 
        {
            return -1; 
        }

        bool found = false;
        for (int i = 0; i < libraryBooks.size(); i++) 
        {
            std::cout << libraryBooks[i].getbookName() << std::endl;
            if (libraryBooks[i].getbookName() == bookName) 
            {
                return i;
            }
        }

        std::cout << "Book Not Found!\n";
    }
    return -1;
}
void giveBook(std::vector<Member>& libraryMembers, 
std::vector<Book>& libraryBooks)
{
    int memberIndex, bookIndex;
    memberIndex = findMemberIndex(libraryMembers);
    if (memberIndex == -1)
    {
        return;
    }
    bookIndex = findBookIndex(libraryBooks);
    if (bookIndex == -1)
    {
        return;
    }

    
    
}
void giveBackBook()
{

}
void outputBorrowedBook()
{

}

int librarianMenu(std::vector<Member>& libraryMembers, 
std::vector<Book>& libraryBooks)
{   
    char choice = '9';
    int memberIDCounter = 0;
    std::string confirm;
    Member newMember;
    do
    {
        // ANSI escape sequence for clearing the screen
        std::cout << "\x1B[2J\x1B[H";
        std::cout << "Enter a number to choose an option \n";
        std::cout << "[1] Add a member \n";
        std::cout << "[2] Issue a book to a member \n";
        std::cout << "[3] Return a book \n";
        std::cout << "[4] Display all books borrowed by any individual member \n";
        std::cout << "[0] Exit \n";
        std::cout << "Option: ";
        std::cin >> choice;
        switch (choice)
        {
            case '1':
                memberIDCounter ++;
                newMember = createMember(memberIDCounter);
                libraryMembers.push_back(newMember);
                std::cout << "===New Member Details===\n";
                std::cout << "Name: " + newMember.getName() + "\n";
                std::cout << "MemberID: " + newMember.getMemberID() + "\n";
                std::cout << "Address: " + newMember.getAddress() + "\n";
                std::cout << "Email: " + newMember.getEmail() + "\n";
                std::cout << "Type OK to continue \n";
                std::cin >> confirm;
                break;
            case '2':
                giveBook(libraryMembers, libraryBooks);
                break;
            case '3':
                giveBackBook();
                break;
            case '4':   
                outputBorrowedBook();
                break;
        }

    } while (choice != '0');
    return 0;
}
int main()
{

    Librarian newLibrarian;
    std::vector<Book> libraryBooks;
    std::vector<Member> libraryMembers;
    //newLibrarian = createNewLibrarian();
    readBookFile(libraryBooks);
    librarianMenu(libraryMembers, libraryBooks);
    return 1;
}