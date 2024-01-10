/*
    person.h
    Author: M00935155
    Created: 09/01/24
    Updated: 10/01/24
*/
#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
class Person
{
    private:
        std::string name;
        std::string address;
        std::string email;
    public:
        std::string getName();
        void setName(std::string name);
        std::string getAddress();
        void setAddress(std::string address);
        std::string getEmail();
        void setEmail(std::string email);
};
#endif
