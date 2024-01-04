#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include "library_system.h"


// Global Variable used for storage of books
std::vector<Book> libraryBooks;
// Global Variable used for storage of members
std::vector<Member> libraryMembers;
// Global Variable used for new memberID
int memberIDCounter = 0;


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
    // Increasing the counter to prevent duplicate memberID
    memberIDCounter ++;
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    
    std::string name, address, email;
    std::cout << "Enter Member Details: \n";
    name = validateName();
    address = validateAddress();
    email = validateEmail();
    Member newMember(memberIDCounter, name, address, email);
    libraryMembers.push_back(newMember);
}
void Librarian::issueBook(int memberID, int bookID)
{   
    // decrement memberID and bookID since vector starts at index 0
    memberID --;
    bookID --;
    Date dueDate = libraryBooks[bookID].getDueDate();
    if (dueDate.day != 0)
    {
        std::cout << "This book is not available!\n";
        return;
    }
    libraryBooks[bookID].setDueDate(getCurrentDate("Three Days"));
    libraryMembers[memberID].setBooksBorrowed(libraryBooks[bookID]);
    std::cout << "Book has been issued!\n";
}
void Librarian::returnBook(int memberID, int bookID)
{
    // decrement memberID and bookID since vector starts at index 0
    memberID --;
    bookID --;
    Book tempBook;
    std::vector<Book>& borrowedBooks 
    = libraryMembers[memberID].getBooksBorrowed();
    
    if (borrowedBooks.size() == 0)
    {
        std::cout << "Member has no books borrowed!\n";
        return;
    }

    for (int i = 0; i < borrowedBooks.size(); i++)
    {
        if (libraryBooks[bookID].getbookID() == borrowedBooks[i].getbookID())
        {   
            tempBook = libraryBooks[bookID];    
            borrowedBooks.push_back(tempBook);
            this->calcFine(memberID);
            borrowedBooks.pop_back();

            libraryBooks[bookID].returnBook();
            borrowedBooks.erase(borrowedBooks.begin() + i);
            std::cout << "Book has been returned!\n";
            return;
        }
    }
    std::cout << "Member did not borrow that book!\n";
}
void Librarian::displayBorrowedBooks(int memberID)
{
    // decrement memberID since vector starts at index 0
    memberID --;
    std::vector <Book> currentMemberBooks;
    Date dueDate;

    std::cout << "Books borrowed by " + libraryMembers[memberID].getName() <<
    std::endl;
    
    currentMemberBooks = libraryMembers[memberID].getBooksBorrowed();
    
    if(currentMemberBooks.size() == 0)
    {
        std::cout << "Member has no books borrowed!\n";
        return;
    }

    for (int i = 0; i < currentMemberBooks.size(); i++)
    {   
        dueDate = currentMemberBooks[i].getDueDate();
        std::cout << currentMemberBooks[i].getbookName() +"\n" +
        "Date Of Return: " + dueDate.dateFormatted << std::endl;
    }
}
void Librarian::calcFine(int memberID)
{   

    // obtaining today's date
    Date currentDate = getCurrentDate("Today");
    // obtaining last book in the vector
    Book tempBook = libraryMembers[memberID].getBooksBorrowed().back();
    // obtaining the due date of the book we need
    Date dueDate = tempBook.getDueDate();
    int differenceInDays = getDifferenceInDays(currentDate, dueDate);


    
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

std::vector<Book>& Member::getBooksBorrowed()
{
    return this->booksLoaned;
}

void Member::setBooksBorrowed(Book book)
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
    this->returnBook();
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
    Date emptyDate;
    
    this->borrower.setName("");
    this->borrower.setAddress("");
    this->borrower.setEmail("");
    
    emptyDate.year = 0;
    emptyDate.day = 0;
    emptyDate.month = 0;
    emptyDate.dateFormatted = "";
    setDueDate(emptyDate);

}
void Book::borrowBook(Member borrower, Date dueDate)
{
    this->borrower = borrower;
    setDueDate(dueDate);
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
void readBookFile()
{
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string filePath = checkFilePath();

    std::ifstream file;
    file.open(filePath);
    std::string line, word, bookData[5];

    //getting the first line which contains book information
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
int checkBookID()
{
    bool check;
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string inputBookID;
    do
    {   
        check = false;

        std::cout << "Input BookID(Enter 0 to exit): ";
        std::cin >> inputBookID;

        if (inputBookID == "0")
        {
            break;
        }

        for (int i = 0 ; i < libraryBooks.size(); i++)
        {   
            if (inputBookID == libraryBooks[i].getbookID())
            {   
                check = true;
                break;
            }
        }
        if (!check)
        {
            std::cout << "Book Does Not Exist!\n";
        }

    } while (!check);
    return stoi(inputBookID);
}
int checkMemberID()
{   
    bool check;
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string inputMemberID;
    do
    {   
        check = false;

        std::cout << "Input MemberID(Enter 0 to exit): ";
        std::cin >> inputMemberID;
        if (inputMemberID == "0")
        {
            break;
        }

        for (int i = 0 ; i < libraryMembers.size(); i++)
        {   
            if (inputMemberID == libraryMembers[i].getMemberID())
            {
                check = true;
                break;
            }
        }
        if (!check)
        {
            std::cout << "Member Does Not Exist!\n";
        }

    } while (!check);
    return stoi(inputMemberID);
}
void confirmInput()
{   
    std::string confirm;
    std::cout << "Type OK to continue \n";
    std::cin >> confirm;
}
void displayLatestMember()
{
    
    int lastIndex = libraryMembers.size() - 1;
    std::cout << "===New Member Details===\n";
    std::cout << "Name: " + libraryMembers[lastIndex].getName() + "\n";
    std::cout << "MemberID: " + libraryMembers[lastIndex].getMemberID() + "\n";
    std::cout << "Address: " + libraryMembers[lastIndex].getAddress() + "\n";
    std::cout << "Email: " + libraryMembers[lastIndex].getEmail() + "\n";
}
void displayMenuOptions()
{
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "Enter a number to choose an option \n";
    std::cout << "[1] Add a member \n";
    std::cout << "[2] Issue a book to a member \n";
    std::cout << "[3] Return a book \n";
    std::cout << "[4] Display all books borrowed by a member \n";
    std::cout << "[0] Exit \n";
    std::cout << "Option: ";
}

int librarianMenu(Librarian newLibrarian)
{   
    char choice = '9';
    int memberID, bookID;
    Member newMember;
    do
    {   
        displayMenuOptions();
        std::cin >> choice;
        switch (choice)
        {
            case '1':
                newLibrarian.addMember();
                displayLatestMember();
                confirmInput();
                break;
            case '2':
                memberID = checkMemberID();
                if (memberID != 0)
                {
                    bookID = checkBookID();
                    if (bookID != 0)
                    {
                        newLibrarian.issueBook(memberID, bookID);
                        confirmInput();
                    }
                }

                break;
            case '3':
                memberID = checkMemberID();
                if (memberID != 0)
                {
                    bookID = checkBookID();
                    if (bookID != 0)
                    {
                        newLibrarian.returnBook(memberID, bookID);
                        confirmInput();
                    }
                }
                break;
            case '4':
                memberID = checkMemberID();
                if (memberID != 0)
                {
                    newLibrarian.displayBorrowedBooks(memberID);
                    confirmInput();
                }
                break;
        }

    } while (choice != '0');
    return 0;
}
int getDifferenceInDays(Date currentDate, Date dueDate)
{
    // define time_point variables for specific dates   
    struct tm currentDateTm  = {0};
    struct tm dueDateTm  = {0};
    
    currentDateTm.tm_year = currentDate.year - 1900;
    currentDateTm.tm_mon = currentDate.month - 1;
    currentDateTm.tm_mday = currentDate.day;
    
    dueDateTm.tm_year = dueDate.year - 1900;
    dueDateTm.tm_mon = dueDate.month - 1;
    dueDateTm.tm_mday = dueDate.day;

    // convert currentDate to time_t
    time_t currentDateTime = mktime(&currentDateTm);
    // convert dueDate to time_t
    time_t dueDateTime = mktime(&dueDateTm);
    // get difference in seconds between current time and due time
    double difference = difftime(currentDateTime,dueDateTime);
    // convert seconds to days
    int days = difference / (60 * 60 * 24);
    
    return days;
}
Date getCurrentDate(std::string type)
 {
    int secondInThreeDays = 259200;
    std::time_t currentTime;

    if (type == "Today") 
    {
        currentTime = std::time(nullptr);
    } 
    else if (type == "Three Days") 
    {
        currentTime = std::time(nullptr) + secondInThreeDays;
    }

    std::tm* currentDate = std::localtime(&currentTime);

    Date current_date;
    current_date.year = currentDate->tm_year + 1900;
    current_date.month = currentDate->tm_mon + 1;
    current_date.day = currentDate->tm_mday;
    current_date.dateFormatted = std::to_string(current_date.day) + '/' +
                                 std::to_string(current_date.month) + '/' +
                                 std::to_string(current_date.year);
    return current_date;
}

int main()
{

    Librarian newLibrarian;
    newLibrarian = createNewLibrarian();
    readBookFile();
    librarianMenu(newLibrarian);
    return 1;
}