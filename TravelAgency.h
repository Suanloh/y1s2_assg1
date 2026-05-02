#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "hotel.h"
// TODO: person.h needs to have the following attributes to support readFile():
//       - country, state, email, userLevel, score (getters and setters)
//       - Constructor: Person(userID, username, country, state, email, userLevel, score)
#include "travelor.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_HOTELS = 50;
const int MAX_TRAVELERS = 100; 

class TravelAgency {
private:
    string agencyName;
    int hotelCount;
    int travelerCount;
    Hotel hotels[MAX_HOTELS];
    Travelor travelers[MAX_TRAVELERS];

public:
    TravelAgency(): agencyName(""), hotelCount(0), travelerCount(0){}
    TravelAgency(const string& name): agencyName(name), hotelCount(0), travelerCount(0){}
    void menu();
    void SummarizeReviewsMenu();
    void ManageTravelerProfileMenu();
    void SearchReviewsMenu();
    void TopTravelersMenu();

    void readFile();
    void saveFile();

    //helper function
    int findhotelIndexByName(const string& name) {
        for (int i = 0; i < hotelCount; i++) {
            if (hotels[i].getHotelName() == name) {
                return i;
            }
        }
        return -1; // Not found
    }

    int findTravelorIndex(){
        cout<<"enter travelor name or travelor user ID?\n 1. user full name \n 2. user ID"<<endl;
            int inputT;
            string inputInfo1;
            cin>> inputT;
            if (inputT ==1){
                cout<<"Enter user name: ";
                cin.ignore();
                getline(cin,inputInfo1);
                for (int i=0;i<travelerCount; i++){
                    if (travelers[i].getUsername()==inputInfo1)return i;
                    else return -1;//notfound
                }
                    }

            else if (inputT ==2){
                cout<<"Enter user ID: ";
                cin.ignore();
                cin>>inputInfo1;
                for(int i=0;i<travelerCount;i++){
                    if (travelers[i].getUserID() == inputInfo1) return i; 
                    else return -1;
                }}
            else {
                cout<<"Invalid input, please try again\n";
                return;
                    }   
    }
};

void TravelAgency::menu() {
    bool running = true;
    do {
        cout << "Welcome to " << agencyName << " Travel Agency!" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. Summarize all reviews for a specific hotel." << endl;
        cout << "2. Manage Traveler Profile" << endl;
        cout << "3. Search reviews" << endl;
        cout << "4. Top Travelers" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                SummarizeReviewsMenu();
                break;
            case 2:
                ManageTravelerProfileMenu();
                break;
            case 3:
                SearchReviewsMenu();
                break;
            case 4:
                TopTravelersMenu();
                break;
            case 5:
                cout << "Thank you for using " << agencyName << " Travel Agency. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (running);
}

void TravelAgency::readFile() {
    // TODO: Implement traveler reading once Person.h is updated
    // Placeholder: Skip traveler file reading
    
    // TODO: Implement review parsing
    // Placeholder: Skip review file reading
    cout << "TODO: Implement file reading for hotels, travelers, and reviews" << endl;
}

void TravelAgency::saveFile() {
    // TODO: Implement save to file once data structure is complete
    // Placeholder: Skip file saving for now
    cout << "TODO: Implement file saving for hotels, travelers, and reviews" << endl;
}

void TravelAgency::SummarizeReviewsMenu() {
    bool exitSub = false;
    do {
        cout << "Summarize Reviews Sub-Menu" << endl;
        cout << "1. Enter hotel name" << endl;
        cout << "2. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        switch (subChoice) {
            case 1: {
                // Placeholder: Implement enter hotel name and summarize reviews
                cout << "Enter hotel name: ";
                string hotelName;
                cin.ignore(1000, '\n'); // Clear input buffer
                getline(cin,hotelName);
                int tempInd = findhotelIndexByName(hotelName);
                if (tempInd == -1){
                    cout<<"Hotel not found, please try again the name\n";
                    return;
                }
                else generateReport(hotels[tempInd]);
                break;
            }
            case 2:
                exitSub = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (!exitSub);
}

void TravelAgency::ManageTravelerProfileMenu() {
    bool exitSub = false;
    do {
        cout << "Manage Traveler Profile Sub-Menu" << endl;
        cout << "1. View profile" << endl;
        cout << "2. Edit profile" << endl;
        cout << "3. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        switch (subChoice) {

            case 1:{
                cout << "TODO: Implement view profile\n=============================================" << endl;
                    int ind = findTravelorIndex();
                    if (ind == -1){
                        cout<<"Invalid info, please check again for the info"<<endl;
                        break;
                    }
                    travelers[ind].printProfile();

                    char choice; bool validchoice=false;
                    while (!validchoice){
                        cout<<"Check for other profile?: (Y/n)"; 
                        cin >> choice;
                        if (choice == 'Y' || choice == 'y') validchoice=true;
                        else if (choice == 'N' || choice == 'n') validchoice = true;
                        else cout<<"Invalid input, please enter Y or N\n";
                    }
                }
                break;

            case 2:{
                cout << "TODO: Implement edit profile\n=============================================" << endl;
                int ind =findTravelorIndex();
                
            }
                break;

            case 3:{
                exitSub = true;
            }
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
        }//end switch
    } while (!exitSub);
}


void TravelAgency::SearchReviewsMenu() {
    bool exitSub = false;
    do {
        cout << "Search Reviews Sub-Menu" << endl;
        cout << "1. Search by hotel" << endl;
        cout << "2. Search by rating" << endl;
        cout << "3. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        switch (subChoice) {
            case 1: {
                // Placeholder: Implement search by hotel
                cout << " TODO Enter hotel name to search: ";
                string hotelName;
                cin >> hotelName;
                // Add logic to search reviews by hotel
                break;
            }
            case 2: {
                // Placeholder: Implement search by rating
                cout << "TODO Enter rating to search: ";
                int rating;
                cin >> rating;
                // Add logic to search reviews by rating
                break;
            }
            case 3:
                exitSub = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (!exitSub);
}

void TravelAgency::TopTravelersMenu() {
    bool exitSub = false;
    do {
        cout << "Top Travelers Sub-Menu" << endl;
        cout << "1. View top travelers" << endl;
        cout << "2. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        switch (subChoice) {
            case 1:
                // Placeholder: Implement view top travelers
                cout << "Displaying top travelers..." << endl;
                // Add logic to display top travelers
                break;
            case 2:
                exitSub = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (!exitSub);
}

#endif // TRAVELAGENCY_H