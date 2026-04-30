#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "hotel.h"
// TODO: person.h needs to have the following attributes to support readFile():
//       - country, state, email, userLevel, score (getters and setters)
//       - Constructor: Person(userID, username, country, state, email, userLevel, score)
#include "person.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_HOTELS = 10;
const int MAX_TRAVELERS = 10;

class TravelAgency {
private:
    string agencyName;
    int hotelCount;
    int travelerCount;
    Hotel hotels[MAX_HOTELS];
    Person travelers[MAX_TRAVELERS];

public:
    void menu();
    void SummarizeReviewsMenu();
    void ManageTravelerProfileMenu();
    void SearchReviewsMenu();
    void TopTravelersMenu();
    void readFile();
    void saveFile();
    TravelAgency(){}
    TravelAgency(const string& name): agencyName(name), hotelCount(0), travelerCount(0){}

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
            case 1:
                cout << "TODO: Implement hotel review summary" << endl;
                break;
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
            case 1:
                cout << "TODO: Implement view profile" << endl;
                break;
            case 2:
                cout << "TODO: Implement edit profile" << endl;
                break;
            case 3:
                exitSub = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
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
            case 1:
                cout << "TODO: Implement search by hotel" << endl;
                break;
            case 2:
                cout << "TODO: Implement search by rating" << endl;
                break;
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
                cout << "TODO: Implement top travelers sorting" << endl;
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