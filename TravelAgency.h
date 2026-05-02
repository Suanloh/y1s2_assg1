#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "hotel.h"
#include "travelor.h"
#include "review.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int MAX_HOTELS = 100;
const int MAX_TRAVELERS = 100;

void print_symbol(char, int); // func prototype

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

    int findTravelorIndex() {
        cout << "enter travelor name or travelor user ID?\n 1. user full name \n 2. user ID\n";
        int inputT;
        cin >> inputT;

        while (inputT != 1 && inputT != 2) {
            cout << "Invalid input, please try again\n";
            cin >> inputT;
        }

        string inputInfo1;

        if (inputT == 1) {
            cout << "Enter user name: ";
            cin.ignore(1000, '\n');
            getline(cin, inputInfo1);

            for (int i = 0; i < travelerCount; i++) {
                if (travelers[i].getUsername() == inputInfo1) return i;
            }
        } else { // inputT == 2
            cout << "Enter user ID: ";
            cin >> inputInfo1;

            for (int i = 0; i < travelerCount; i++) {
                if (travelers[i].getUserID() == inputInfo1) return i;
            }
        }

        return -1;
    }
};
    // int split(string line, string arr[], int maxParts);
  //check for future purpose


void TravelAgency::menu() {
    cout << "\ndebug: Entering menu function in TravelAgency class" << endl;
    cout << "Maximum hotels allowed: " << MAX_HOTELS << endl;
    cout << "Maximum travelers allowed: " << MAX_TRAVELERS << endl;
    cout << endl;
    bool running = true;
    cout << "\nWelcome to " << agencyName << " Travel Agency!" << endl;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Please select an option:" << endl;
        print_symbol('=', 34);
        cout << "1. Summarize all reviews for a specific hotel." << endl;
        cout << "2. Manage Traveler Profile" << endl;
        cout << "3. Search reviews" << endl;
        cout << "4. Top Travelers" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cout << endl;
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

    // ---------- LOAD HOTELS ----------
    ifstream hFile("hotels.txt");

    if (!hFile) {
        cout << "Error: Cannot open hotels.txt\n";
    } else {
        hotelCount = 0;

        string id, name;

        while (hFile >> id >> name) {
            if (hotelCount >= MAX_HOTELS) {
                cout << "Hotel array full\n";
                break;
            }

            hotels[hotelCount] = Hotel(name);
            hotelCount++;
        }

        cout << "Hotels loaded: " << hotelCount << endl;
    }


    // ---------- LOAD TRAVELERS ----------
    ifstream tFile("travelers.txt");

    if (!tFile) {
        cout << "Error: Cannot open travelers.txt\n";
    } else {
        travelerCount = 0;

        string id, name, country, state, email, level;
        int score;

        while (tFile >> id >> name >> country >> state >> email >> level >> score) {
            if (travelerCount >= MAX_TRAVELERS) {
                cout << "Traveler array full\n";
                break;
            }

            // travelers[travelerCount] = Person(id, name);

            travelerCount++;
        }

        cout << "Travelers loaded: " << travelerCount << endl;
    }


    // ---------- REVIEWS ----------
    cout << "Reviews loading not implemented yet\n";

    cout << "\nAll data loading completed.\n";
}

void TravelAgency::saveFile() {
    // TODO: Implement save to file once data structure is complete
    // Placeholder: Skip file saving for now
    cout << "TODO: Implement file saving for hotels, travelers, and reviews" << endl;
}

/* int TravelAgency::split(string line, string arr[], int maxParts) {
    int count = 0;
    string temp = "";

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '\t') {
            if (count < maxParts) {
                arr[count++] = temp;
                temp = "";
            }
        } else {
            temp += line[i];
        }
    }

    if (count < maxParts) {
        arr[count++] = temp;
    }

    return count;
}
*/
void TravelAgency::SummarizeReviewsMenu() {
    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Summarize Reviews Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. Enter hotel name" << endl;
        cout << "2. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        cout << endl;
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
        print_symbol('=', 34);
        cout << setw(28) << "Manage Traveler Profile Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. View profile" << endl;
        cout << "2. Edit profile" << endl;
        cout << "3. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        cout << endl;
        switch (subChoice) {

            case 1:{
                cout << "Implement view profile\n=============================================" << endl;
                    int ind = findTravelorIndex();
                    if (ind == -1){
                        cout<<"Invalid info, please check again for the info"<<endl;
                        break;
                    }
                    travelers[ind].printProfile();
                    travelers[ind].showUserReview(travelers[ind]);

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
                cout << "Implement edit profile\n=============================================" << endl;
                int ind = findTravelorIndex();
                if (ind == -1) { cout << "User not found\n"; break; }
                travelers[ind].printProfile();
                travelers[ind].editprofile();
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
        print_symbol('=', 34);
        cout << setw(28) << "Search Reviews Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. Search by hotel" << endl;
        cout << "2. Search by rating" << endl;
        cout << "3. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        cout << endl;
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
}//no done yet

void TravelAgency::TopTravelersMenu() {
    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Top Travelers Sub-Menu" << endl;
        print_symbol('=', 34)
        ;
        cout << "1. View top travelers" << endl;
        cout << "2. Back to main menu" << endl;
        int subChoice;
        cin >> subChoice;
        cout << endl;
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

void print_symbol(char symbol, int count) {
    for (int i = 0; i < count; i++) {
        cout << symbol;
    }
    cout << endl;
}


#endif // TRAVELAGENCY_H