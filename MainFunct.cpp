// ////Read review.txt into Review allReviews[MAX_REVIEWS]; int reviewN;
// Read hotels/users similarly
// Then for each hotel, call hotel.addReview(review) to attach matching reviews into the hotel’s owned array.

// FYI im doing a friend function in hotel.h for generating report, so if needed u can 
//call that function in main or other files, but i will not implement any friend function in main.cpp

#include <iostream>
#include <string>
#include <fstream>

#include "review.h"
#include "travelor.h"
#include "hotel.h"
#include "TravelAgency.h"
using namespace std;

int main() {
    string jibet = "Jibet Hotel";
    Hotel h1(jibet);
    generateReport(h1); // Call the friend function to generate the report for h1

    string agencyName = "Global Explorer";
    TravelAgency agency(agencyName);
    agency.readFile(); // Call the readFile function to load data from files (currently a placeholder)
    agency.menu(); // Call the menu function to display options to the user

    return 0;
}