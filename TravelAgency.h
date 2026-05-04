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
    void TopPickMatcherMenu();
    void DebugMenu();
    void updateTravelerLevels();

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
        cout << "Select traveler by:\n 1. User full name \n 2. User ID\n";
        int inputT;
        cin >> inputT;

        while (inputT != 1 && inputT != 2) {
            cout << "Invalid input, please try again\n";
            cin.clear();
            cin.ignore(1000, '\n');
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

void TravelAgency::menu() {
    cout << "\nWelcome to " << agencyName << " Travel Agency!" << endl;
    
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
        cout << "4. System Data Debug Menu" << endl; 
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
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
                DebugMenu();
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
    ifstream tFile("user.txt");
    if (!tFile) {
        cout << "Error: Cannot find user.txt.\n";
        return false; 
    } 

    string tData[MAX_TRAVELERS][6]; 
    travelerCount = 0;
    cout << "Loading travelers from user.txt...\n";
    while (travelerCount < MAX_TRAVELERS && getline(tFile, tData[travelerCount][0], '\t')) {
        getline(tFile, tData[travelerCount][1], '\t');
        getline(tFile, tData[travelerCount][2], '\t');
        getline(tFile, tData[travelerCount][3], '\t');
        getline(tFile, tData[travelerCount][4], '\t');
        getline(tFile, tData[travelerCount][5], '\n');

        int score = stoi(tData[travelerCount][5]); 

        travelers[travelerCount] = Travelor(
            tData[travelerCount][0], tData[travelerCount][1], tData[travelerCount][2],
            tData[travelerCount][3], tData[travelerCount][4], score
        );
        travelerCount++;
    }
    tFile.close();
    cout << "Travelers loaded: " << travelerCount << endl;

    ifstream rFile("review.txt");
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
    updateTravelerLevels();
    cout << "\nAll data loading completed.\n";
    return true;
}

bool TravelAgency::saveFile() {
    string tPath = "user.txt";
    ofstream tFile(tPath);
    if (!tFile) {
        cout << "Error: Cannot open user.txt for saving.\n";
        return false;
    }

    for (int i = 0; i < travelerCount; i++) {
        tFile << travelers[i].getUserID() << '\t'
              << travelers[i].getUsername() << '\t'
              << travelers[i].getState() << '\t'
              << travelers[i].getEmail() << '\t'
              << travelers[i].getUserLevel() << '\t'
              << travelers[i].getScore() << '\n';
    }
    tFile.close();

    string rPath = "review.txt";
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
        cout << "2. Record a New Review" << endl; 
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
                cout << "--- Record a New Review ---\n";
                
                // Admin context: select the user
                cout << "Select the traveler submitting this review:\n";
                int tInd = findTravelorIndex();
                if (tInd == -1) {
                    cout << "Traveler not found in the database. Cannot record review.\n";
                    break;
                }

                cout << "Enter the exact name of the hotel: ";
                string hName;
                cin.ignore(1000, '\n');
                getline(cin, hName);

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

                int rating;
                cout << "Enter rating (1 to 5): ";
                while (!(cin >> rating) || rating < 1 || rating > 5) {
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number between 1 and 5: ";
                }

                string comment;
                cout << "Enter comment: ";
                cin.ignore(1000, '\n');
                getline(cin, comment);

                Review newRev(travelers[tInd].getUserID(), rating, comment, hName);
                hotels[hInd].addReview(newRev);

                int points = 100; 
                int wordCount = 0;
                bool inWord = false;
                for (char c : comment) {
                    if (isspace(c)) {
                        inWord = false;
                    } else if (!inWord) {
                        wordCount++;
                        inWord = true;
                    }
                }
                if (wordCount >= 50) {
                    points += 10; 
                }
                
                travelers[tInd].setScore(travelers[tInd].getScore() + points);
                cout << "\nYay! Points Awarded to " << travelers[tInd].getUsername() << ": +" << points << " points (Total: " << travelers[tInd].getScore() << ")\n";
                
                updateTravelerLevels();

                cout << "SUCCESS! Review recorded.\n";
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
    cout << "\n--- Select Traveler ---\n";
    int ind = findTravelorIndex();
    if (ind == -1) { 
        cout << "User not found. Returning to main menu.\n"; 
        return; 
    }
    cout << "Selected: " << travelers[ind].getUsername() << "\n";

    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "Manage Traveler Profile" << endl;
        print_symbol('=', 34);
        cout << "1. View profile & authored reviews" << endl;
        cout << "2. Edit profile" << endl;
        cout << "3. Back to main menu" << endl;
        int subChoice;
        if (!(cin >> subChoice)) {
            cin.clear(); 
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        cout << endl;
        switch (subChoice) {
            case 1:{
                cout << "=============================================" << endl;
                travelers[ind].printProfile();
                cout << "\n--- Authored Reviews ---\n";
                for (int i = 0; i < hotelCount; i++) {
                    hotels[i].showUserReview(travelers[ind]);
                }
                break;
            }
            case 2:{
                cout << "=============================================" << endl;
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
        cout << setw(28) << "Leaderboards & Rankings" << endl;
        print_symbol('=', 34);
        cout << "1. Find the Best Overall Hotel" << endl;
        cout << "2. View Hotel Rankings" << endl;
        cout << "3. View Top Reviewers" << endl;
        cout << "4. Back to main menu" << endl;
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
            case 2: {
                if (hotelCount == 0) {
                    cout << "No hotels available.\n";
                    break;
                }
                int hotelIndices[MAX_HOTELS];
                for (int i = 0; i < hotelCount; i++) { hotelIndices[i] = i; }
                
                for (int i = 0; i < hotelCount - 1; i++) {
                    for (int j = 0; j < hotelCount - i - 1; j++) {
                        if (!(hotels[hotelIndices[j]] > hotels[hotelIndices[j + 1]])) {
                            int temp = hotelIndices[j];
                            hotelIndices[j] = hotelIndices[j + 1];
                            hotelIndices[j + 1] = temp;
                        }
                    }
                }
                cout << "\n===== HOTEL RANKINGS =====\n";
                for (int i = 0; i < hotelCount; i++) {
                    int idx = hotelIndices[i];
                    cout << (i + 1) << ". " << hotels[idx].getHotelName() 
                         << " - Avg Rating: " << fixed << setprecision(2) 
                         << hotels[idx].averageRating() << "/5.0 (" 
                         << hotels[idx].getReviewCount() << " reviews)\n";
                }
                break;
            }
            case 3: {
                if (travelerCount == 0) {
                    cout << "No travelers available.\n";
                    break;
                }
                int travelerIndices[MAX_TRAVELERS];
                for (int i = 0; i < travelerCount; i++) { travelerIndices[i] = i; }
                
                for (int i = 0; i < travelerCount - 1; i++) {
                    for (int j = 0; j < travelerCount - i - 1; j++) {
                        if (travelers[travelerIndices[j]].getScore() < travelers[travelerIndices[j + 1]].getScore()) {
                            int temp = travelerIndices[j];
                            travelerIndices[j] = travelerIndices[j + 1];
                            travelerIndices[j + 1] = temp;
                        }
                    }
                }
                cout << "\n===== TOP REVIEWERS BY POINTS =====\n";
                for (int i = 0; i < travelerCount && i < 10; i++) {
                    int idx = travelerIndices[i];
                    if (travelers[idx].getScore() > 0) {
                        cout << (i + 1) << ". " << travelers[idx].getUsername() 
                             << " - Points: " << travelers[idx].getScore() << endl;
                    }
                }
                break;
            }
            case 4:
                exitSub = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (!exitSub);
}

void TravelAgency::DebugMenu() {
    // Password check removed per administrative tool scope.
    bool exitSub = false;
    do {
        print_symbol('=', 34);
        cout << setw(28) << "System Debug Sub-Menu" << endl;
        print_symbol('=', 34);
        cout << "1. View Hotel Array Extracted from review.txt" << endl;
        cout << "2. View Traveler Array Extracted from user.txt" << endl;
        cout << "3. Add Points to a Traveler (Test Tier Upgrades)" << endl; // NEW OPTION
        cout << "4. Back to main menu" << endl;
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
            case 2: {
                if (travelerCount == 0) {
                    cout << "The traveler array is currently empty. (Did the files load?)\n";
                } else {
                    cout << "--- TRAVELERS IN MEMORY (" << travelerCount << "/" << MAX_TRAVELERS << ") ---\n";
                    for (int i = 0; i < travelerCount; i++) {
                        cout << "[" << i << "] " << travelers[i].getUsername() 
                            << " (UserID: " << travelers[i].getUserID() 
                            << ", Tier: " << travelers[i].getUserLevel()
                            << ", Score: " << travelers[i].getScore() << ")\n";
                    }
                }
                break;
            }
            case 3: {
                cout << "--- Admin Point Modification ---\n";
                int tInd = findTravelorIndex();
                if (tInd == -1) {
                    cout << "Traveler not found in the database.\n";
                    break;
                }
                
                cout << "\nSelected: " << travelers[tInd].getUsername() 
                     << " (Current Score: " << travelers[tInd].getScore() 
                     << " | Current Tier: " << travelers[tInd].getUserLevel() << ")\n";
                     
                int pointsToAdd;
                cout << "Enter number of points to instantly add: ";
                while (!(cin >> pointsToAdd)) {
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a valid number: ";
                }
                
                // Add the points
                travelers[tInd].setScore(travelers[tInd].getScore() + pointsToAdd);
                cout << "\nSystem forced +" << pointsToAdd << " points to " << travelers[tInd].getUsername() << ".\n";
                
                // Instantly check if this pushed them into a new tier!
                updateTravelerLevels(); 
                
                break;
            }
            case 4:
                exitSub = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (!exitSub);
}

// Evaluates all travelers and upgrades/downgrades their level based on points
void TravelAgency::updateTravelerLevels() {
    for(int i = 0; i < travelerCount; i++) {
        string oldLevel = travelers[i].getUserLevel();
        int points = travelers[i].getScore();
        string newLevel = "Basic";

        if (points >= 10000) newLevel = "Platinum";
        else if (points >= 5000) newLevel = "Gold";
        else if (points >= 1000) newLevel = "Silver";

        // If the level has changed, update it and notify the console!
        if (newLevel != oldLevel) {
            travelers[i].setUserLevel(newLevel);
            cout << "\n[!] TIER UPDATE: " << travelers[i].getUsername() 
                 << " has been changed from " << oldLevel << " to " << newLevel << " Tier!\n";
        }
    }
}

void print_symbol(char symbol, int count) {
    for (int i = 0; i < count; i++) {
        cout << symbol;
    }
    cout << endl;
}

#endif // TRAVELAGENCY_H