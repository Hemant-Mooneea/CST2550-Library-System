/*
    utilities.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#include "utilities.h"

// Global Variable used for storage of books
std::vector<Book> libraryBooks;
// Global Variable used for storage of members
std::vector<Member> libraryMembers;
// Global Variable used for new memberID
int memberIDCounter = 0;

/*
    hasAlpha checks if there are any non alphabet found within a string
    @param: the string to be tested
    @return: a boolean to represent if the string has any alphabet in it
*/
bool hasAlpha(std::string str) 
{
    std::regex regexPattern("[^a-zA-Z]");
    return !std::regex_search(str, regexPattern);
}
/* 
    hasNonDigits checks if there are anything but digits within a string
    @param: the string to be tested
    @return: a boolean to represent if the string has non-digits characters
*/
bool hasNonDigits(std::string str) 
{
    bool check;
    for (int i = 0; i < static_cast<int>(str.length()); i++) 
    {
        check = isdigit(str[i]);
        if (!check)
        {
            return true; 
        }
    }
    return false;
}
/*
     hasWhiteSpaces checks whether the user input nothing in a field
     @param: the string to be tested
     @return: a boolean representing whether the string has whitespaces or not
*/
bool hasWhiteSpaces(std::string str)
{   
    //iterates throughtout the string to check if all characters are spaces
    bool check = std::all_of(str.begin(),str.end(),isspace);
    return check;
}
/*
     hasAtSign checks if the string contains an @ sign
     @param: the string to be tested
     @return: a boolean which represents whether the string has an @ sign or not
*/
bool hasAtSign(std::string str)
{
    for (int i = 0; i < static_cast<int>(str.length()); i++) 
    {
        if (str[i] == '@')
        {
            return true; 
        }
    }
    return false;
}
/*
    validateName allows the user to input a string and loops until the following
    are met:
    -no number in the string
    -non empty string was input
    @param: none
    @return: the name of a person 
*/
std::string validateName()
{   
    std::string name;
    bool doesAlpha;
    bool doesWhitespaces;
    bool exitLoop;
    do
    {
        doesAlpha = true;
        doesWhitespaces = false;
        exitLoop = true;

        std::cout << "Enter Your Name: ";
        std::getline(std::cin,name);
        
        //checks for whitespaces such as "    "
        doesWhitespaces = hasWhiteSpaces(name);
        //checks if name has any non-alphabet
        doesAlpha = hasAlpha(name);
        
        if (doesWhitespaces or name.length() == 0)
        {
            std::cout << "Name cannot be blank \n";
            exitLoop = false;
        }
        else if (!doesAlpha)
        {
            std::cout << "Name can only contain alphabets \n";
            exitLoop = false;
        }
    } while (!exitLoop);

    return name;

}
/*
    validateAddress allows the user to input a string and loops until the 
    following are met:
    -a non empty string was input
    @param: none
    @return: a person's address
*/
std::string validateAddress()
{   
    std::string address;
    bool doesWhitespaces;
    do
    {
        std::cout << "Enter Your Address: ";
        std::getline(std::cin, address);
        
        //checks for whitespaces such as "    "
        doesWhitespaces = hasWhiteSpaces(address);

        if (doesWhitespaces or address.length() == 0)
        {
            std::cout << "Name cannot be blank \n";
        }
    } while (doesWhitespaces);

    return address;
}
/*
    validateEmail allows the user to input a string and loops until the 
    following are met:
    -a non empty string is input
    -string contains an @ sign
    @param: none
    @return: a person's email address
*/
std::string validateEmail()
{
    std::string email;
    bool doesContainAtSign;
    bool doesWhitespaces;
    bool exitLoop;
    do
    {
        doesContainAtSign = true;
        doesWhitespaces = false;
        exitLoop = true;

        std::cout << "Enter Your Email: ";
        std::getline(std::cin,email);
        
        //checks for whitespaces such as "    "
        doesWhitespaces = hasWhiteSpaces(email);
        //checks if name has digits
        doesContainAtSign = hasAtSign(email);
        
        if (doesWhitespaces or email.length() == 0)
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
/*
    validateNumbers allows the user to input an integer and loops until the 
    following are met:
    -a non empty string was input
    -an integer was input
    @param: the integer we are trying to validate(e.g MemberID, StaffID)
    @return: an integer which represents what was input in the parameter
*/
int validateNumbers(std::string type)
{   
    int number;
    std::string tempNumber;
    bool doesWhitespaces;
    bool doesDigits;
    bool exitLoop;
    do
    {
        doesDigits = false;
        doesWhitespaces = false;
        exitLoop = true;

        std::cout << "Enter Your " + type + " :";
        std::getline(std::cin, tempNumber);

        //checks for whitespaces such as "    "
        doesWhitespaces = hasWhiteSpaces(tempNumber);
        //checks for non digits 
        doesDigits = hasNonDigits(tempNumber);
        if (doesWhitespaces or tempNumber.length() == 0)
        {
            std::cout << type +" cannot be blank \n";
            exitLoop = false;
        }
        else if (doesDigits)
        {   
            std::cout << type + " can only contain numbers \n";
            exitLoop = false;
        }

    } while (!exitLoop);
    // converting string to integer
    number = std::stoi(tempNumber);
    return number;
}
/*
    getDifferenceInDays uses time_point structures to convert 2 dates into 
    seconds based on their year, month and day 
    It then substracts those seconds and convert them into days which represents
    the number of days between 2 dates
    @params:
            currentDate: today's date
            dueDate: the due date of a book
    @return: the difference between currentDate and dueDate in integer form
*/
int getDifferenceInDays(Date currentDate, Date dueDate)
{   
    const int SECONDSTODAYS = 60 * 60 * 24;
    // define time_point structures for specific dates   
    struct tm currentDateTm = {};
    currentDateTm.tm_year = currentDate.year - 1900;
    currentDateTm.tm_mon = currentDate.month - 1;
    currentDateTm.tm_mday = currentDate.day;

    struct tm dueDateTm = {};
    dueDateTm.tm_year = dueDate.year - 1900;
    dueDateTm.tm_mon = dueDate.month - 1;
    dueDateTm.tm_mday = dueDate.day;

    // convert currentDate to time_t
    time_t currentDateTime = mktime(&currentDateTm);
    // convert dueDate to time_t
    time_t dueDateTime = mktime(&dueDateTm);
    // get difference in seconds between current time and due time
    double difference = difftime(currentDateTime, dueDateTime);
    // convert seconds to days
    int days = difference / SECONDSTODAYS;
    
    return days;
}
/*
    getDate is used to obtain a specific date using ctime
    @param: type can only be two input "Today" or "Three days" which represents
            which date the system needs to access.
    @return: a date structure containing either today's date or the date in 3
             days time 
*/
Date getDate(std::string type)
 {
    const int SECONDSINTHREEDAYS = 259200;
    // obtain today's current time 
    std::time_t currentTime;

    if (type == "Today") 
    {
        currentTime = std::time(nullptr);
    } 
    else if (type == "Three Days") 
    {   
        // Adding 3 days worth of seconds into today's date
        currentTime = std::time(nullptr) + SECONDSINTHREEDAYS;
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