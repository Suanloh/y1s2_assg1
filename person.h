#ifndef PERSON_H//base class
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;

class Person{
    protected: 
    /*use for slicing problem, if we use private, the derived class cannot access the data member of the base class, 
    but if we use protected, the derived class can access the data member of the base class, but other class cannot access the 
    data member of the base class*/
    
        string userID;
        string username;
    
    public:
        Person ():userID(""), username(""){};
        Person (const string &userID, const string &username):userID(userID), username(username){};

        string getUserID() const{
            return userID;
        };
        string getUsername() const{
            return username;
        };
};

#endif