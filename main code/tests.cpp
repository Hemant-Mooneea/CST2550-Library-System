/*
    tests.cpp
    Author: M00935155
    Created: 10/01/24
    Updated: 11/01/24
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "book.h"
#include "member.h"
#include "date.h"
#include "librarian.h"
#include "person.h"
#include "utilities.h"

TEST_CASE("test person methods", "[person_methods]")
{
	Person person;
	std::string testName, testEmail, testAddress;
	
	testName = "John Smith";
	testEmail = "Johnsmith102@gmail.com";
	testAddress = "Palma Road, Quatre Bornes";
	
	person.setName(testName);
	person.setEmail(testEmail);
	person.setAddress(testAddress);

	REQUIRE(person.getName() == testName);
	REQUIRE(person.getEmail() == testEmail);
	REQUIRE(person.getAddress() == testAddress);
}

TEST_CASE("test librarian methods", "[librarian_methods]")
{	
	int testStaffID, testSalary;
	std::string testName, testEmail, testAddress;
	
	testStaffID = 102;
	testSalary = 20000;
	testName = "Vince Gilbert";
	testEmail = "Vincegilbert23@gmail.com";
	testAddress = "Royal Road, Pereybere";
	
	Librarian librarian(testStaffID, testName, testAddress, testEmail,
	testSalary);

	REQUIRE(librarian.getName() == testName);
	REQUIRE(librarian.getEmail() == testEmail);
	REQUIRE(librarian.getAddress() == testAddress);
	REQUIRE(librarian.getSalary() == testSalary);
	REQUIRE(librarian.getStaffID() == testStaffID);
}

TEST_CASE("test member methods", "[member_methods]")
{
	int testMemberID;
	std::string testName, testAddress, testEmail;

	testMemberID = 12;
	testName = "Bobby Rich";
	testEmail = "BobbyRich3@gmail.com";
	testAddress = "Louis Pasteur Street, Port Louis";
	
	Member member(testMemberID, testName, testAddress, testEmail);

	REQUIRE(std::stoi(member.getMemberID()) == testMemberID);
	REQUIRE(member.getName() == testName);
	REQUIRE(member.getEmail() == testEmail);
	REQUIRE(member.getAddress() == testAddress);

	int testBookID;
	std::string testBookName, testAuthorFirstName, testAuthorLastName;
	testBookID = 23;
	testBookName = "A Plot for Murder";
	testAuthorFirstName = "Frederic";
	testAuthorLastName = "Brown";

	Book book(testBookID,testBookName,testAuthorFirstName,testAuthorLastName);
	
	member.setBooksBorrowed(book);

	Book getterBook;
	std::vector <Book> memberBooks;
	memberBooks = member.getBooksBorrowed();

	REQUIRE(memberBooks[0].getAuthorFirstName() == book.getAuthorFirstName());
	REQUIRE(memberBooks[0].getAuthorLastName() == book.getAuthorLastName());
	REQUIRE(memberBooks[0].getbookID() == book.getbookID());
	REQUIRE(memberBooks[0].getbookName() == book.getbookName());
}

TEST_CASE("test book methods", "[book_methods]")
{
	int testBookID;
	std::string testBookName, testAuthorFirstName, testAuthorLastName;
	testBookID = 23;
	testBookName = "A Plot for Murder";
	testAuthorFirstName = "Frederic";
	testAuthorLastName = "Brown";
	
	Date testDate;
	testDate.day = 10;
	testDate.month = 2;
	testDate.year = 2024;

	Book book(testBookID,testBookName,testAuthorFirstName,testAuthorLastName);
	
	book.setDueDate(testDate);

	REQUIRE(std::stoi(book.getbookID()) == testBookID);
	REQUIRE(book.getbookName() == testBookName);
	REQUIRE(book.getAuthorFirstName() == testAuthorFirstName);
	REQUIRE(book.getAuthorLastName() == testAuthorLastName);
	
	Date testDateGetter = book.getDueDate();

	REQUIRE(testDateGetter.day == testDate.day);
	REQUIRE(testDateGetter.month == testDate.month);
	REQUIRE(testDateGetter.year == testDate.year);


}
TEST_CASE("test utilities functions", "[utilities_test]")
{
	std::string alphaUpperText, alphaLowerText, numberText, emptyText, 
	atSignText, mixedText;
	
	alphaUpperText = "ASDAS";
	alphaLowerText = "wqeqwe";
	numberText = "123";
	emptyText = "";
	atSignText = "testmail@gmail.com";
	mixedText = "123ABCabc!#$";

	REQUIRE(hasAlpha(alphaUpperText) == true);
	REQUIRE(hasAlpha(alphaUpperText) == true);
	REQUIRE(hasAlpha(numberText) == false);
	REQUIRE(hasAlpha(mixedText) == false);

	REQUIRE(hasNonDigits(numberText) == false);
	REQUIRE(hasNonDigits(mixedText) == true);
	
	REQUIRE(hasAtSign(atSignText) == true);
	REQUIRE(hasAtSign(mixedText) == false);

	REQUIRE(hasWhiteSpaces(emptyText) == true);
	REQUIRE(hasWhiteSpaces(mixedText) == false);

	Date testDate1, testDate2;
	// testing for 1 day difference
	testDate1.day = 10;
	testDate1.month = 10;
	testDate1.year = 2024;

	testDate2.day = 11;
	testDate2.month = 10;
	testDate2.year = 2024;
	
	REQUIRE(getDifferenceInDays(testDate2,testDate1) == 1);
	
	// testing for 1 month difference
	testDate2.day = 10;
	testDate2.month = 11;
	
	REQUIRE(getDifferenceInDays(testDate2,testDate1) == 31);

	// testing for 1 year difference
	testDate2.month = 10;
	testDate2.year = 2025;

	REQUIRE(getDifferenceInDays(testDate2,testDate1) == 365);
	
}