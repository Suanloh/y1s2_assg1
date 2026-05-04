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

void generateReport(const Hotel& h){
    cout << "Hotel Name: " << h.hotelName << endl;
    cout << "Average Rating: " << h.averageRating() << endl;
    cout << "Total Reviews: " << h.reviewCount << endl;
    cout << "Reviews:" << endl;

    for(int i = 0; i < h.reviewCount; i++){
        cout << "Review ID: " << h.rv[i].getReviewID() 
             << ", Rating: " << h.rv[i].getRate() 
             << ", Comment: " << h.rv[i].getComment() 
             // << ", Hotel Name: " << h.rv[i].getHotelName() paiseh, already know hotel name
             << endl;
    }
}

int main() {
    // ===== 1) Create some travelers (from your user.txt format) =====
    // Travelor t1("U001", "Ali", "Selangor", "ali@gmail.com", "Silver", 1200);
    // Travelor t2("U004", "Nur Aisyah", "Sabah", "aisyah.sabah@hotmail.com", "Silver", 3400);

    // cout << "=== Traveler profile test ===\n";
    // t1.printProfile();   // matches your current travelor.h signature
    // cout << "-----------------------------\n";
    // t2.printProfile();

    // // ===== 2) Create a hotel =====
    // Hotel h1("Grand Imperial Hotel");

    // // ===== 3) Create reviews (from your review.txt format) =====
    // // review.txt line: U001  5  Excellent service and clean room  Grand Imperial Hotel
    // Review r1("U001", 5, "Excellent service and clean room", "Grand Imperial Hotel");
    // Review r2("U004", 4, "Nice location but the room is small", "Grand Imperial Hotel");
    // Review r3("U001", 3, "Average breakfast, staff friendly", "Grand Imperial Hotel");

    // // Attach reviews to the hotel (this is what readFile() would normally do)
    // h1.addReview(r1);
    // h1.addReview(r2);
    // h1.addReview(r3);

    // // ===== 4) Test generateReport(friend) =====
    // cout << "\n=== generateReport(h1) test ===\n";
    // generateReport(h1);

    // // ===== 5) Test showUserReview (if you implemented Option A: Review has getUserID) =====
    // // If your Review class still uses getReviewID() to store userID, adjust accordingly.
    // cout << "\n=== showUserReview tests ===\n";
    // cout << "[Reviews by U001]\n";
    // h1.showUserReview(t1);

    // cout << "\n[Reviews by U004]\n";
    // h1.showUserReview(t2);

    // ===== 6) Optional: start TA menu (will only work if TA has data loaded/hardcoded) =====
    TravelAgency* ta = new TravelAgency("TestAgency");
    ta->menu();

    return 0;
}