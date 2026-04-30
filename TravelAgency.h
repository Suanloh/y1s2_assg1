#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "hotel.h"
#include "person.h"
using namespace std;

class TravelAgency {
private:
    string agencyName;
    int hotelCount;

public:
    TravelAgency(){}
    TravelAgency(const string& name): agencyName(name), hotelCount(0){}
    void Menu();
    void SummarizeReviewsMenu();
    void ManageTravelerProfileMenu();
    void SearchReviewsMenu();
    void TopTravelersMenu();


};

void TravelAgency::Menu() {
    bool running = true;
    do {
        cout << "Welcome to " << agencyName << " Travel Agency!" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. Summarize all reviews for a specific hotel." << endl;
        cout << "2. Manage Traveler Profile" << endl;
        cout << "3. Search reviews" << endl;
        cout << "4. Top Travelers" << endl;
        cout << "5. Exit" << endl;

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
                cin >> hotelName;
                // Add logic to summarize reviews for the hotel
                generateReport(Hotel(hotelName)); 
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
            case 1:
                // Placeholder: Implement view profile
                cout << "Viewing profile..." << endl;
                // Add logic to display traveler profile
                break;
            case 2:
                // Placeholder: Implement edit profile
                cout << "Editing profile..." << endl;
                // Add logic to edit traveler profile
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
            case 1: {
                // Placeholder: Implement search by hotel
                cout << "Enter hotel name to search: ";
                string hotelName;
                cin >> hotelName;
                // Add logic to search reviews by hotel
                break;
            }
            case 2: {
                // Placeholder: Implement search by rating
                cout << "Enter rating to search: ";
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