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
    /* string jibet = "Jibet Hotel";
    Hotel h1(jibet);
    generateReport(h1); // Call the friend function to generate the report for h1
    */
    // my IDE is very weak ah, I use heap to create the TravelAgency object to avoid stack overflow, but in real life we can just create it on stack
    string agencyName = "Global Explorer";
    TravelAgency* agency = new TravelAgency(agencyName); 
    agency->menu(); 

    delete agency; // Don't forget to free the memory!

    return 0;
}