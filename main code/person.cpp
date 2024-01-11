/*
    person.cpp
    Author: M00935155
    Created: 09/01/24
    Updated: 11/01/24
*/
#include "person.h"
/*
    Getter for a person's name
    @param: none
    @return: the name of a person
*/
std::string Person::getName()
{
    return this->name;
}
/*
    Getter for a person's email
    @param: none
    @return: the email of a person
*/
std::string Person::getEmail()
{
    return this->email;
}
/*
    Getter for a person's address
    @param: none
    @return: the address of a person
*/
std::string Person::getAddress()
{
    return this->address;
}
/*
    Setter for a person's name
    @param: the name of a person
    @return: none
*/
void Person::setName(std::string name)
{
    this->name = name;
}
/*
    Setter for a person's email
    @param: the email of a person
    @return: none
*/
void Person::setEmail(std::string email)
{
    this->email = email;
}
/*
    Setter for a person's address
    @param: the address of a person
    @return: none
*/
void Person::setAddress(std::string address)
{
    this->address = address;
}