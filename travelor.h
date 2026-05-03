#ifndef TRAVELOR_H
#define TRAVELOR_H
#include <string>
#include <iostream>
#include <iomanip>
#include "person.h"
using namespace std;


class Travelor:public Person{
    private:
        string state;
        string email;
        string userLevel;
        int score;  
    
    public:
        Travelor ():Person(), state(""), email(""), userLevel(""), score(0){};
        Travelor (const string &userID, const string &username, const string &state, 
            const string &email, const string &userLevel, int score)
            :Person(userID, username), state(state), email(email), userLevel(userLevel), score(score){};

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
        void setUsername(const string &username){
            this->username = username;
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
        void printProfile()const ;
        void editprofile();// return true if edit successfully, otherwise return false
};
void Travelor::printProfile()const {
    cout<<"Travelor Profile:\n============================================="<<endl;
    cout<<"UserID: "<<getUserID()<<endl;
    cout<<"Username: "<<getUsername()<<endl;
    cout<<"State: "<<getState()<<endl;
    cout<<"Email: "<<getEmail()<<endl;
    cout<<"User Level: "<<getUserLevel()<<endl;
    cout<<"Score: "<<getScore()<<endl;
}

void Travelor::editprofile(){
    bool exitSub = false;
    while (!exitSub) {
        cout << "\n=============================================" << endl;
        cout << setw(28) << "Edit Profile Sub-Menu" << endl;
        cout << "=============================================" << endl;
        cout << "1. Edit username\n2. Edit state\n3. Edit email\n4. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        cout << endl;
        switch (subChoice) {
            case 1:{
                cout << "Enter new User Name: ";
                string newUsername;
                cin >> newUsername;
                setUsername(newUsername);
            }
                break;

            case 2:{
                cout << "Enter new state: ";
                string newState;
                cin >> newState;
                setState(newState);
            } break;
            case 3:{
                cout << "Enter new email: ";
                string newEmail;
                cin >> newEmail;
                setEmail(newEmail);

            }break;
            
            case 4:{
                exitSub = true;
            }break;
            default:{
                cout << "Invalid option. Please try again." << endl;
                continue;}

            }
    }
}

#endif