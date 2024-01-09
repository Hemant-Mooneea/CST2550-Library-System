/*
    library_functions.cpp
    Author: M00935155
    Created:08/01/24
    Updated:08/01/24
*/

#include "library_system.cpp"
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
            std::cout << "Name cannot contain numbers \n";
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
    checkFilePath has the user input a path an checks if a file is found there.
    It then checks if the file has a csv extension and warns the user if the
    wrong file is input
    @param: none
    @return: the path where the csv file is located
*/
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
            bookData[count] = word;
            count++;
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

        switch (option)
        {
            case 1:
                newLibrarian.addMember();
                displayLatestMember();
                confirmInput();
                break;
            case 2:
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
            case 3:
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
            case 4:
                memberID = checkMemberID();
                if (memberID != 0)
                {
                    newLibrarian.displayBorrowedBooks(memberID);
                    confirmInput();
                }
                break;
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