#include "library_system.h"

// Global Variable used for storage of books
std::vector<Book> libraryBooks;
// Global Variable used for storage of members
std::vector<Member> libraryMembers;
// Global Variable used for new memberID
int memberIDCounter = 0;


// Methods for Class Person
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

// Methods for Librarian Class
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
    // Delcaring member info
    std::string name, address, email;
    std::cout << "Enter Member Details: \n";
    // Performing data valdiation on each member info
    name = validateName();
    address = validateAddress();
    email = validateEmail();
    // Creating a new member object for the new member using their info
    Member newMember(memberIDCounter, name, address, email);
    // Storing the new member oject in a vector
    libraryMembers.push_back(newMember);
}
void Librarian::issueBook(int memberID, int bookID)
{   
    // Decrement memberID and bookID since vector starts at index 0
    memberID --;
    bookID --;
    Date dueDate = libraryBooks[bookID].getDueDate();
    // dueDate.day == 0 means that it is available to be borrowed
    if (dueDate.day != 0)
    {
        std::cout << "This book is not available!\n";
        return;
    }
    /*
    Setting a dueDate 3 days in the future to a book in the vector by calling
    the getDate function with parameter "Three Days"
    */
    libraryBooks[bookID].setDueDate(getDate("Three Days"));
    // Adding the book object to the booksLoaned vector of a specific member
    libraryMembers[memberID].setBooksBorrowed(libraryBooks[bookID]);
    // Confirmation message that a book has been issued
    std::cout << "Book has been issued!\n";
}
void Librarian::returnBook(int memberID, int bookID)
{
    // Decrement memberID and bookID since vector starts at index 0
    memberID --;
    bookID --;
    Book tempBook;
    // Vector which points towards the address of a member's bookLoaned vector
    std::vector<Book>& borrowedBooks 
    = libraryMembers[memberID].getBooksBorrowed();
    // Checking if the member has any book borrowed using the size of the vector
    if (borrowedBooks.size() == 0)
    {
        std::cout << "Member has no books borrowed!\n";
        return;
    }

    // Iterating throughtout the member's bookLoaned vector
    for (int i = 0; i < borrowedBooks.size(); i++)
    {   // Checking if the member borrowed a book with that bookID
        if (libraryBooks[bookID].getbookID() == borrowedBooks[i].getbookID())
        {   
            // Copying the book object which we want to return
            tempBook = libraryBooks[bookID];
            /*
                Pushing the book object at the last position in the vector which
                allows for easy retrieval of the book's data since we can access 
                the last index of the vector
            */     
            borrowedBooks.push_back(tempBook);
            // Calculating fines, if any
            this->calcFine(memberID);
            // Removing the extra tempBook object since it is uneeded
            borrowedBooks.pop_back();

            libraryBooks[bookID].returnBook();
            // Removing the returned book from member's bookLoaned vector
            borrowedBooks.erase(borrowedBooks.begin() + i);
            return;
        }
    }
    std::cout << "Member did not borrow that book!\n";
}
void Librarian::displayBorrowedBooks(int memberID)
{
    // Decrement memberID since vector starts at index 0
    memberID --;
    std::vector <Book> currentMemberBooks;
    Date dueDate;

    std::cout << "Books borrowed by " + libraryMembers[memberID].getName() <<
    std::endl;
    
    currentMemberBooks = libraryMembers[memberID].getBooksBorrowed();
    // Checking if member borrowed any book based on the vector size
    if(currentMemberBooks.size() == 0)
    {
        std::cout << "Member has no books borrowed!\n";
        return;
    }
    // Iterating the vector and outputing all book borrowed and their due dates
    for (int i = 0; i < currentMemberBooks.size(); i++)
    {   
        dueDate = currentMemberBooks[i].getDueDate();
        std::cout << currentMemberBooks[i].getbookName() +"\n" +
        "Date Of Return: " + dueDate.dateFormatted << std::endl;
    }
}
void Librarian::calcFine(int memberID)
{   
    // Obtaining today's date
    Date currentDate = getDate("Today");
    // Obtaining last book in the vector
    Book tempBook = libraryMembers[memberID].getBooksBorrowed().back();
    // Obtaining the due date of the book we need
    Date dueDate = tempBook.getDueDate();
    // Variable to store the difference in days between 2 dates
    int differenceInDays = getDifferenceInDays(currentDate, dueDate);
    // If the difference in days is <= 0 then due date has NOT been exceeded
    if (differenceInDays <= 0 )
    {
        std::cout << "Book returned on time, no fines!\n";
    }  
    else
    {   
        std::cout << "Fines are due: £" + differenceInDays << std::endl;
    }
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
    // Converting memberId to string since method returns string
    return std::to_string(this->memberId);
}

std::vector<Book>& Member::getBooksBorrowed()
{
    return this->booksLoaned;
}

void Member::setBooksBorrowed(Book book)
{   
    this->booksLoaned.push_back(book);
}

// Methods for Book Class
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
    // Converting bookID to string since method returns string
    return std::to_string(this->bookID);
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
    // Creating a temporary Date object
    Date emptyDate;
    // Setting the book's borrower to empty string
    this->borrower.setName("");
    this->borrower.setAddress("");
    this->borrower.setEmail("");
    // Setting the book's return date to 0
    emptyDate.year = 0;
    emptyDate.day = 0;
    emptyDate.month = 0;
    emptyDate.dateFormatted = "";
    // Setting the book's due date variables to 0, meaning that it is available
    setDueDate(emptyDate);

}
void Book::borrowBook(Member borrower, Date dueDate)
{
    this->borrower = borrower;
    setDueDate(dueDate);
}
// hasDigits checks if there are any digits within a string
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
// hasNonDigits checks if there are anything but digits within a string
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
// hasWhiteSpaces checks whether the user input nothing in a field
bool hasWhiteSpaces(std::string str)
{   
    //iterates throughtout the string to check if all characters are spaces
    bool check = std::all_of(str.begin(),str.end(),isspace);
    return check;
}
// hasAtSign checks if the string contains an @ sign
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
/*
    validateName returns a string variable which goes through the following 
    checks:
    -checks for any number in the string
    -checks if nothing was input
*/
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
/*
    validateAddress returns a string variable which goes through the following
     checks:
    -checks if nothing was input
*/
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
/*
    validateEmail returns a string variable which goes through the following 
    checks:
    -checks if nothing was input
    -checks if an @ sign is present in the string
*/
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
/*
    validateNumbers has a parameter string which represents what number is being 
    validated e.g: type can be "MemberID", "Salary"
    It returns an Integer variable which goes through the following checks:
    -checks if nothing was input
    -checks if anything other than a number is the string
    It converts the string variable used to hold perform string manipulation 
    into an integer at the end
*/
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
    // converting string to integer
    number = std::stoi(tempNumber);
    return number;
}
/*
    checkFilePath has the user input a path an checks if a file is found there.
    It then checks if the file has a csv extension and warns the user if the
    wrong file is input
*/
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
    extractBookData has two parameters an array of type string and a string line
    
    The function is used to breakdown a line of text into different strings 
    
    The string is cut short when a comma is found in line which is then stored
    in the array based on an index which is incremented everytime somethng is 
    stored.

    Some books have " " in their titles which indicates that their title have
    a comma in them. As such if statements check for " " for each word.
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
    It stores the librarian's information using setters.
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
/*
    checkMemberID checks if the memberID input by a user exists in the 
    libraryMembers vector.
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
/*
    getDifferenceInDays has 2 Date parameters, currentDate which is Today's Date 
    and dueDate which is the due date of a book object
    The functions uses time_point structures to convert these dates into seconds
    based on their year, month and day 
    It then substracts those seconds and convert them into days which represents
    the number of days between 2 dates
*/
int getDifferenceInDays(Date currentDate, Date dueDate)
{   
    const int SECONDSTODAYS = 60 * 60 * 24;
    // define time_point structures for specific dates   
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
    double difference = difftime(currentDateTime, dueDateTime);
    // convert seconds to days
    int days = difference / SECONDSTODAYS;
    
    return days;
}
/*
    getDate has a string parameter, type, which is used to obtain the date
    The type parameter can take two values "Today" or "Three Days" which based
    on those values return appropriate dates.
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
// confirmInput is used to obtain user confirmation after a change
void confirmInput()
{   
    std::string confirm;
    std::cout << "Type OK to continue \n";
    std::cin >> confirm;
}
// displayLatestMember outputs every detail about the newest member
void displayLatestMember()
{
    int lastIndex = libraryMembers.size() - 1;
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