#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include "review.h"
#include "person.h"
using namespace std;

const int MAX_REVIEW_HOTELS = 200;
class Hotel {
private:
    string hotelName;
    double budget;
    int reviewCount;
    int totalRate;

    Review rv [MAX_REVIEW_HOTELS];

public:
    Hotel():hotelName(""), reviewCount(0), totalRate(0){};
    Hotel(const string& hotelName):hotelName(hotelName), reviewCount(0), totalRate(0){};

    string getHotelName() const{
        return hotelName;
    };

    // add review to the hotel, in array
    void addReview(const Review& r){ 
        if(reviewCount >= MAX_REVIEW_HOTELS){
            return;
        }
        rv[reviewCount] = r;
        reviewCount++;
        totalRate += r.getRate();
    };  

    int getReviewCount() const{
        return reviewCount;
    };
    double averageRating() const{
        if(reviewCount == 0){
            return 0.0;
        }
        return static_cast<double>(totalRate) / reviewCount;
    };

    // Operator overloading requirement
    bool operator>(const Hotel& rhs) const {
        double a = this->averageRating();
        double b = rhs.averageRating();
        const double EPS = 1e-9;

        if (a - b > EPS) return true;
        if (b - a > EPS) return false;

        if (this->reviewCount != rhs.reviewCount)
            return this->reviewCount > rhs.reviewCount;

        return this->hotelName > rhs.hotelName;
    }
    
    //friend function, declare inside MF
    friend void generateReport(const Hotel& h);

    void showUserReview(const Person& p) const {
        // URGENT: This need to be recheck again!
    bool found = false;

    for (int i = 0; i < reviewCount; i++) {
        if (rv[i].getReviewID() == p.getUserID()) {
            found = true;
            cout << "Hotel: " << hotelName
                 << " | ReviewID: " << rv[i].getReviewID()
                 << " | Rating: " << rv[i].getRate()
                 << " | Comment: " << rv[i].getComment()
                 << "\n";
        }
    }

    if (!found) {
        cout << "No reviews by user " << p.getUserID()
             << " for hotel " << hotelName << ".\n";
    }
}
};

// this friend function should put in hotel.h, not hotel.cpp. I dunno why but it will cause error if i put it in hotel.cpp, so i just put it here.

#endif