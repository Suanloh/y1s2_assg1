#ifndef TRAVELOR_H
#define TRAVELOR_H
#include <string>
#include <iostream>
#include "person.h"
using namespace std;


class Travelor:public Person{
    private:
        string country;
        string state;
        string email;
        string userLevel;
        int score;  
    
    public:
        Travelor ():Person(), country(""), state(""), email(""), userLevel(""), score(0){};
        Travelor (const string &userID, const string &username, const string &country, const string &state, 
            const string &email, const string &userLevel, int score)
            :Person(userID, username), country(country), state(state), email(email), userLevel(userLevel), score(score){};

        string getCountry() const{
            return country;
        };
        string getState() const{
            return state;
        };
        string getEmail() const{
            return email;
        };
        string getUserLevel() const{
            return userLevel;
        };
        int getScore() const{
            return score;
        };

        void setCountry(const string &country){
            this->country = country;
        };
        void setState(const string &state){
            this->state = state;
        };
        void setEmail(const string &email){
            this->email = email;
        };
        void setUserLevel(const string &userLevel){
            this->userLevel = userLevel;
        };
        void setScore(int score){
            if(score < 0){
                this->score = 0;
            } 
            else this->score = score;
        };

        //shower function for traveler profile
        void printProfile()const {};
};
void Travelor::printProfile()const {
    cout<<"UserID: "<<getUserID()<<endl;
    cout<<"Username: "<<getUsername()<<endl;
    cout<<"Country: "<<getCountry()<<endl;
    cout<<"State: "<<getState()<<endl;
    cout<<"Email: "<<getEmail()<<endl;
    cout<<"User Level: "<<getUserLevel()<<endl;
    cout<<"Score: "<<getScore()<<endl;
}

#endif