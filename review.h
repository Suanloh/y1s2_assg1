#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include <iostream>
#include "person.h"
using namespace std;

class Review {
private:
    string reviewID;
    int rate;            // from review.txt
    string comment;
    string hotelName;

public:
    Review():reviewID(""), rate(0), comment(""), hotelName(""){};
    Review(const string& rvID,
           int rt,
           const string& cm,
           const string& htName)
           :reviewID(rvID), rate(rt), comment(cm), hotelName(htName){};

    string getReviewID() const{
        return reviewID;
    };
    int getRate() const{
        return rate;
    };
    string getComment() const{
        return comment;
    };
    string getHotelName() const{
        return hotelName;
    };

    void setRate(int rate){
        if(rate < 0){
            this->rate = 0;
        } 
        else if(rate > 5){
            this->rate = 5;
        }
        else this->rate = rate;
    };
    
};

#endif