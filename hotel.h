#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include "Review.h"
using namespace std;

class Hotel {
private:
    string hotelName;

    int reviewCount;
    int totalRate;

public:
    Hotel():hotelName(""), reviewCount(0), totalRate(0){};
    Hotel(const string& hotelName):hotelName(hotelName), reviewCount(0), totalRate(0){};

    string getHotelName() const{
        return hotelName;
    };

    void addReview(const Review& r){};   // updates totals if review matches this hotel
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
};

#endif