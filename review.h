#ifndef REVIEW_H
#define REVIEW_H

#include <string>
using namespace std;

class Review {
private:
    string reviewID;
    int rate;            // from review.txt
    string comment;
    string hotelName;

public:
    Review():reviewID(""), rate(0), comment(""), hotelName(""){};
    Review(const string& reviewID,
           int rate,
           const string& comment,
           const string& hotelName):reviewID(reviewID), rate(rate), comment(comment), hotelName(hotelName){};

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