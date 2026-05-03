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
    int reviewCount;
    int totalRate;

    Review rv[MAX_REVIEW_HOTELS];

public:
    Hotel():hotelName(""), reviewCount(0), totalRate(0){};
    Hotel(const string& hotelName):hotelName(hotelName), reviewCount(0), totalRate(0){};

    string getHotelName() const{
        return hotelName;
    }

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
    }

    // ADDED: Allows TravelAgency to access reviews for saving the file
    Review getReview(int index) const {
        return rv[index];
    }

    double averageRating() const{
        if(reviewCount == 0){
            return 0.0;
        }
        return static_cast<double>(totalRate) / reviewCount;
    }

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

    // Displays all reviews for this hotel sorted from 5-star down to 1-star
    void displayTopSortedReviews() const {
        if (reviewCount == 0) {
            cout << "No reviews for this hotel yet.\n";
            return;
        }

        // Create a temporary array to sort without modifying the original data
        Review sortedRv[MAX_REVIEW_HOTELS];
        for (int i = 0; i < reviewCount; i++) {
            sortedRv[i] = rv[i];
        }

        // Simple Bubble Sort 
        for (int i = 0; i < reviewCount - 1; i++) {
            for (int j = 0; j < reviewCount - i - 1; j++) {
                if (sortedRv[j].getRate() < sortedRv[j + 1].getRate()) {
                    Review temp = sortedRv[j];
                    sortedRv[j] = sortedRv[j + 1];
                    sortedRv[j + 1] = temp;
                }
            }
        }

        // Print the sorted reviews
        cout << "\n--- All Reviews (Sorted by Highest Rating) ---\n";
        for (int i = 0; i < reviewCount; i++) {
            cout << "Rating: " << sortedRv[i].getRate() << "/5"
                 << " | User: " << sortedRv[i].getReviewID()
                 << " | Comment: " << sortedRv[i].getComment() << "\n";
        }
    }
};

#endif