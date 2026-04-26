#ifndef PERSON_H//base class
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;

class Person{
    private:
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