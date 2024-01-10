/*
    person.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#include "person.h"
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