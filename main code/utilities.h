/*
    utilities.h
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#ifndef UTILITIES_H
#define UTILITIES_H

#include "date.h"
#include "book.h"
#include "member.h"
#include <iostream>
#include <regex>
#include <vector>

extern std::vector<Book> libraryBooks;
extern std::vector<Member> libraryMembers;
extern int memberIDCounter;

bool hasAlpha(std::string str);
bool hasNonDigits(std::string str);
bool hasWhiteSpaces(std::string str);
bool hasAtSign(std::string str);
std::string validateName();
std::string validateAddress();
std::string validateEmail();
int validateNumbers(std::string type);
int getDifferenceInDays(Date currentDate, Date dueDate);
Date getDate(std::string type);

#endif // UTILITIES_H
