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

    string adminPassword = "admin123"; // Added for Encapsulation demonstration

public:
    TravelAgency(): agencyName(""), hotelCount(0), travelerCount(0){}
    TravelAgency(const string& name): agencyName(name), hotelCount(0), travelerCount(0){}
    void menu();
    void SummarizeReviewsMenu();
    void ManageTravelerProfileMenu();
    void TopPickMatcherMenu();
    void DebugMenu();

    bool readFile(); 
    bool saveFile();

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
}; // <-- IF THIS SEMICOLON IS MISSING, EVERYTHING BREAKS

void TravelAgency::menu() {
    cout << "\nWelcome to " << agencyName << " Travel Agency!" << endl;
    
    // Load files once as per requirements
    if (!readFile()) {
        cout << "Error loading data files. Exiting..." << endl;
        return; 
    }

    bool running = true;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Please select an option:" << endl;
        print_symbol('=', 34);
        cout << "1. Summarize all reviews for a specific hotel." << endl;
        cout << "2. Manage Traveler Profile" << endl;
        cout << "3. Top-Pick Matcher (Best Hotel)" << endl;
        cout << "4. Debug Menu (Admin Only)" << endl; // Optional debug menu for testing internal state
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        // CRASH-PROOF VALIDATION
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n'); 
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue; 
        }
        
        cout << endl;
        switch (choice) {
            case 1:
                SummarizeReviewsMenu();
                break;
            case 2:
                ManageTravelerProfileMenu();
                break;
            case 3:
                TopPickMatcherMenu();
                break;
            case 4:
                DebugMenu(); // Call the debug menu
                break;
            case 5:
                cout << "Saving data..." << endl;
                saveFile();
                cout << "Thank you for using " << agencyName << " Travel Agency. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (running);
}

bool TravelAgency::readFile() {
    // ---------- LOAD TRAVELERS (Smart Path + 2D Array) ----------
    ifstream tFile("C:\\user.txt");
    
    if (!tFile) {
        cout << "Error: Cannot find user.txt.\n";
        return false; 
    } 

    string tData[MAX_TRAVELERS][7];
    travelerCount = 0;

    while (travelerCount < MAX_TRAVELERS && getline(tFile, tData[travelerCount][0], '\t')) {
        getline(tFile, tData[travelerCount][1], '\t');
        getline(tFile, tData[travelerCount][2], '\t');
        getline(tFile, tData[travelerCount][3], '\t');
        getline(tFile, tData[travelerCount][4], '\t');
        getline(tFile, tData[travelerCount][5], '\t');
        getline(tFile, tData[travelerCount][6], '\n'); 

        int score = stoi(tData[travelerCount][6]);

        travelers[travelerCount] = Travelor(
            tData[travelerCount][0], tData[travelerCount][1], tData[travelerCount][2],
            tData[travelerCount][3], tData[travelerCount][4], tData[travelerCount][5], score
        );
        travelerCount++;
    }
    tFile.close();
    cout << "Travelers loaded: " << travelerCount << endl;

    // ---------- LOAD REVIEWS & DISCOVER HOTELS ----------
    ifstream rFile("C:\\review.txt");

    if (!rFile) {
        cout << "Error: Cannot find review.txt.\n";
        return false;
    }

    const int MAX_ALL_REVIEWS = 500; 
    string rData[MAX_ALL_REVIEWS][4];
    int rCount = 0;
    hotelCount = 0; 

    while (rCount < MAX_ALL_REVIEWS && getline(rFile, rData[rCount][0], '\t')) {
        getline(rFile, rData[rCount][1], '\t'); 
        getline(rFile, rData[rCount][2], '\t'); 
        getline(rFile, rData[rCount][3], '\n'); 

        int rate = stoi(rData[rCount][1]);
        string currentHotelName = rData[rCount][3];

        Review rev(rData[rCount][0], rate, rData[rCount][2], currentHotelName);

        int hIndex = findhotelIndexByName(currentHotelName);
        
        if (hIndex == -1) { 
            if (hotelCount < MAX_HOTELS) {
                hotels[hotelCount] = Hotel(currentHotelName);
                hIndex = hotelCount; 
                hotelCount++;        
            } else {
                cout << "Max hotels reached, skipping new hotel.\n";
                break; 
            }
        }
        
        hotels[hIndex].addReview(rev);
        rCount++;
    }
    rFile.close();
    cout << "Reviews loaded: " << rCount << " (Discovered " << hotelCount << " Hotels)\n";
    cout << "\nAll data loading completed.\n";
    return true;
}

bool TravelAgency::saveFile() {
    // ---------- SAVE TRAVELERS ----------
    string tPath = "user.txt";
    ifstream checkT(tPath);
    if (!checkT) { tPath = "../user.txt"; checkT.open(tPath); }
    if (!checkT) { tPath = "../../user.txt"; }
    if (checkT) checkT.close();

    ofstream tFile(tPath);
    if (!tFile) {
        cout << "Error: Cannot open user.txt for saving.\n";
        return false;
    }

    for (int i = 0; i < travelerCount; i++) {
        tFile << travelers[i].getUserID() << '\t'
              << travelers[i].getUsername() << '\t'
              << travelers[i].getCountry() << '\t'
              << travelers[i].getState() << '\t'
              << travelers[i].getEmail() << '\t'
              << travelers[i].getUserLevel() << '\t'
              << travelers[i].getScore() << '\n';
    }
    tFile.close();

    // ---------- SAVE REVIEWS ----------
    string rPath = "C:\\review.txt";
    ifstream checkR(rPath);
    if (!checkR) { rPath = "../review.txt"; checkR.open(rPath); }
    if (!checkR) { rPath = "../../review.txt"; }
    if (checkR) checkR.close();

    ofstream rFile(rPath);
    if (!rFile) {
        cout << "Error: Cannot open review.txt for saving.\n";
        return false;
    }

    for (int i = 0; i < hotelCount; i++) {
        for (int j = 0; j < hotels[i].getReviewCount(); j++) {
            Review rev = hotels[i].getReview(j); 
            rFile << rev.getReviewID() << '\t'
                  << rev.getRate() << '\t'
                  << rev.getComment() << '\t'
                  << rev.getHotelName() << '\n';
        }
    }
    rFile.close();

    cout << "Data saved successfully." << endl;
    return true;
}

void TravelAgency::SummarizeReviewsMenu() {
    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Property Deep-Dive Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. View Hotel Summary & Reviews" << endl;
        cout << "2. Write a New Review" << endl; // NEW OPTION ADDED HERE
        cout << "3. Back to main menu" << endl;
        int subChoice;
        
        if (!(cin >> subChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        cout << endl;
        
        switch (subChoice) {
            case 1: {
                cout << "Enter hotel name: ";
                string hotelName;
                cin.ignore(1000, '\n'); 
                getline(cin, hotelName);
                
                int tempInd = findhotelIndexByName(hotelName);
                if (tempInd == -1){
                    cout << "Hotel not found. Please check the spelling and try again.\n";
                }
                else {
                    generateReport(hotels[tempInd]);
                }
                break;
            }
            case 2: {
                cout << "--- Write a New Review ---\n";
                
                // 1. Identify the Traveler (Authentication)
                cout << "First, please verify your identity to post a review.\n";
                int tInd = findTravelorIndex();
                if (tInd == -1) {
                    cout << "Traveler not found. You must be a registered user to write a review.\n";
                    break;
                }

                // 2. Identify the Hotel
                cout << "Enter the exact name of the hotel you want to review: ";
                string hName;
                cin.ignore(1000, '\n');
                getline(cin, hName);

                // 3. Hotel Discovery (Create it if it doesn't exist!)
                int hInd = findhotelIndexByName(hName);
                if (hInd == -1) {
                    if (hotelCount < MAX_HOTELS) {
                        hotels[hotelCount] = Hotel(hName);
                        hInd = hotelCount;
                        hotelCount++;
                        cout << "(New hotel '" << hName << "' discovered and added to the system!)\n";
                    } else {
                        cout << "Max hotels reached. Cannot add a new hotel.\n";
                        break;
                    }
                }

                // 4. Get Review Details with Crash-Proof Validation
                int rating;
                cout << "Enter your rating (1 to 5): ";
                while (!(cin >> rating) || rating < 1 || rating > 5) {
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number between 1 and 5: ";
                }

                string comment;
                cout << "Enter your comment: ";
                cin.ignore(1000, '\n');
                getline(cin, comment);

                // 5. Create and Attach Review
                // We use the authenticated traveler's ID to tag the review
                Review newRev(travelers[tInd].getUserID(), rating, comment, hName);
                hotels[hInd].addReview(newRev);

                cout << "\nSUCCESS! Your review for " << hName << " has been submitted.\n";
                cout << "(It will be permanently saved to review.txt when you exit the program).\n";
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

void TravelAgency::ManageTravelerProfileMenu() {
    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Manage Traveler Profile" << endl;
        print_symbol('=', 34);
        cout << "1. View profile" << endl;
        cout << "2. Edit profile" << endl;
        cout << "3. Back to main menu" << endl;
        int subChoice;
        if (!(cin >> subChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        cout << endl;
        switch (subChoice) {
            case 1:{
                cout << "=============================================" << endl;
                int ind = findTravelorIndex();
                if (ind == -1){
                    cout<<"User not found, please check the info."<<endl;
                    break;
                }
                travelers[ind].printProfile();
                cout << "\n--- Authored Reviews ---\n";
                for (int i = 0; i < hotelCount; i++) {
                    hotels[i].showUserReview(travelers[ind]);
                }
                break;
            }
            case 2:{
                cout << "=============================================" << endl;
                int ind = findTravelorIndex();
                if (ind == -1) { cout << "User not found\n"; break; }
                travelers[ind].printProfile();
                travelers[ind].editprofile();
                break;
            }
            case 3:{
                exitSub = true;
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (!exitSub);
}

void TravelAgency::TopPickMatcherMenu() {
    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Top Rated Hotel Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. Find the Best Overall Hotel" << endl;
        cout << "2. Back to main menu" << endl;
        int subChoice;
        
        if (!(cin >> subChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        cout << endl;

        switch (subChoice) {
            case 1: {
                if (hotelCount == 0) {
                    cout << "No hotels available. Please ensure data is loaded.\n";
                    break;
                }

                int bestHotelIndex = 0; 
                for (int i = 1; i < hotelCount; i++) {
                    if (hotels[i] > hotels[bestHotelIndex]) {
                        bestHotelIndex = i;
                    }
                }

                cout << "\n===== TOP RATED HOTEL RESULT =====\n";
                cout << "Best Hotel     : " << hotels[bestHotelIndex].getHotelName() << endl;
                cout << "Average Rating : " << fixed << setprecision(2) << hotels[bestHotelIndex].averageRating() << " / 5.0" << endl;
                cout << "Total Reviews  : " << hotels[bestHotelIndex].getReviewCount() << endl;
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

void TravelAgency::DebugMenu() {
    string inputPwd;
    cout << "\n--- ADMIN AUTHENTICATION ---\n";
    cout << "Enter admin password: ";
    cin >> inputPwd;

    // Encapsulation check: comparing input to the private variable
    if (inputPwd != adminPassword) {
        cout << "Access Denied. Incorrect password. Returning to main menu...\n";
        return; // Kick them out immediately
    }

    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "System Debug Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. View Hotel Array Extracted from review.txt" << endl;
        cout << "2. Back to main menu" << endl;
        int subChoice;
        
        if (!(cin >> subChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        cout << endl;

        switch (subChoice) {
            case 1: {
                if (hotelCount == 0) {
                    cout << "The hotel array is currently empty. (Did the files load?)\n";
                } else {
                    cout << "--- HOTELS DISCOVERED IN MEMORY (" << hotelCount << "/" << MAX_HOTELS << ") ---\n";
                    for (int i = 0; i < hotelCount; i++) {
                        cout << "[" << i << "] " << hotels[i].getHotelName() 
                             << " -> (Total Reviews Attached: " << hotels[i].getReviewCount() << ")\n";
                    }
                }
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

void print_symbol(char symbol, int count) {
    for (int i = 0; i < count; i++) {
        cout << symbol;
    }
    cout << endl;
}

#endif // TRAVELAGENCY_H