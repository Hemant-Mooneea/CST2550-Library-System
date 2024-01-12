/*
    library_main.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 12/01/24
*/
#include "librarian.h"
#include "utilities.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>


std::string checkFilePath()
{
    std::string filePath;
    bool checkFile;
    do
    {
        std::cout << "Input the path to the Books file:\n";
        std::getline(std::cin, filePath);
        checkFile = std::filesystem::exists(filePath);  
        if (!checkFile) 
        {
            std::cout << "File does not exist at path: " + filePath + "\n";
        }
        else
        {
            int len = filePath.length();
            if (len >= 3) 
            {
                std::string lastThree = filePath.substr(len - 3);
                if (lastThree != "csv")
                {
                    std::cout << "System only accept .csv files \n";
                    checkFile = false;
                }
            } 
            else 
            {   
                std::cout << "System only accept .csv files \n";
                checkFile = false;
            }
        }
    } while (!checkFile);
    return filePath;
}
/*
    extractBookData is used to breakdown a line of text into different strings 
    The string is cut short when a comma is found in line which is then stored
    in the array based on an index which is incremented everytime somethng is 
    stored.
    @params:
            bookData: an array of string used to store the information of the
                      book based on its index(e.g index 0 stores bookid)    
            line: a string which is a line from the csv file which will be used
                  to extract from
    @return: none
*/
void extractBookData(std::vector<std::string>& bookData, std::string line)
{   
    std::string word = ""; 
    std::string tempWord = "";

    // used for breaking words 
    std::stringstream s(line);

    bool isWordComplete = true;

    // seperates each word by using the comma and loops across each word
    while (std::getline(s, word, ',')) 
    { 
        /* 
            checking if the first character of the string is " which in the csv 
            file indicates that a string contains a comma within it
        */
        if (word[0] == '"' || isWordComplete == false) 
        {
            tempWord = tempWord + word + ',';
            isWordComplete = false;
        }
        /* 
            checking if the last character of the string is "  meaning that the 
            string is complete
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
            bookData.push_back(word);
        }
    } 
}
/*
    readBookFile is the function responsible for intialising the libraryBooks
    vector with book objects using the data from the csv file
    It makes use of the checkFilePath function to verify the path of the file 
    and the extractBookData function to break down the data of each book to be 
    stored 
    @param: none
    @return: none
*/
void readBookFile()
{
    // ANSI escape sequence for clearing the screen
    std::cout << "\x1B[2J\x1B[H";
    std::string filePath = checkFilePath();

    std::ifstream file;
    file.open(filePath);
    std::string line, word;

    //getting the first line which contains book information
    std::getline(file, line);
    //while loop continues until it reaches end of file
    while (std::getline(file, line)) 
    {
        // Clear the bookData vector for each line
        std::vector<std::string> bookData;
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
/*
    createNewLibrarian allows for the librarian to enter their user information
    and stores that information into a temporary Librarian object.
    It makes use of the validateName, validateAddress, validateEmail and
    validateNumbers function to ensure proper data validation.
    @param: none
    @return: a Librarian object which will initialise the main librarian object
*/
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
/*
    checkBookID checks if the bookID input by a user exists in the libraryBooks
    vector.
    @param: none
    @return: an integer which represent a valid BookID found in the library
*/
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
        std::getline(std::cin, inputBookID);

        if (inputBookID == "0")
        {
            break;
        }

        for (int i = 0 ; i < static_cast<int>(libraryBooks.size()); i++)
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
/*
    checkMemberID checks if the memberID input by a user exists in the 
    libraryMembers vector.
    @param: none
    @return: an integer which represents a valid MemberID of the library
*/
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
        std::getline(std::cin, inputMemberID);
        if (inputMemberID == "0")
        {
            break;
        }

        for (int i = 0 ; i < static_cast<int>(libraryMembers.size()); i++)
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
/*
    confirmInput is used to obtain user confirmation after a change
    @param: none
    @return: none
*/  
void confirmInput()
{   
    std::string confirm;
    std::cout << "Type OK to continue \n";
    std::getline(std::cin, confirm);
}
/*
    displayLatestMember outputs every detail about the newest member
    @param: none
    @return: none
*/
void displayLatestMember()
{
    int lastIndex = static_cast<int>(libraryMembers.size()) - 1;
    std::cout << "===New Member Details===\n";
    std::cout << "Name: " + libraryMembers[lastIndex].getName() + "\n";
    std::cout << "MemberID: " + libraryMembers[lastIndex].getMemberID() + "\n";
    std::cout << "Address: " + libraryMembers[lastIndex].getAddress() + "\n";
    std::cout << "Email: " + libraryMembers[lastIndex].getEmail() + "\n";
}
/*
    displayMenuOptions output all the Librarian's options namely:
    -Adding New members
    -Issuing a book to a member
    -Returning a book
    -Displaying all books borrowed by a member
    @param: none
    @return: none
    
*/
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
/*
    librarianMenu is where the librarian is able to input a number corresponding
    to what action they would like to perform
    displayMenuOptions() is called to show the librarian what choices they have
    validation of memberID and bookID is carried out by checkMemberID and 
    checkBookID to ensure no errors arise.
    Based on their choice another function is called to perform that task
    @param: A librarian object which is used to access the Librarian Methods
    @return: none
*/
void librarianMenu(Librarian newLibrarian)
{   
    int option;
    int memberID, bookID;
    Member newMember;
    do
    {   
        displayMenuOptions();
        option = validateNumbers("Option");

        if (option == 1) 
        {
            newLibrarian.addMember();
            displayLatestMember();
            confirmInput();
        }   
        else if (option == 2) 
        {
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
        }   
        else if (option == 3) 
        {
            memberID = checkMemberID();
            if (memberID != 0) 
            {
                bookID = checkBookID();
                if (bookID != 0) {
                    newLibrarian.returnBook(memberID, bookID);
                    confirmInput();
                }
            }
        }   
        else if (option == 4) 
        {
            memberID = checkMemberID();
            if (memberID != 0) 
            {
                newLibrarian.displayBorrowedBooks(memberID);
                confirmInput();
            }
        }       

    } while (option != 0);
}
/*
    main program is used to initialise the Librarian object, libraryBooks vector
    and call the librarianMenu function
*/
int main()
{

    Librarian newLibrarian;
    newLibrarian = createNewLibrarian();
    readBookFile();
    librarianMenu(newLibrarian);
    return 1;
}