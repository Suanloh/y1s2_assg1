#include "hotel.h"
#include <iostream>
using namespace std;

void generateReport(const Hotel& hotel){
    cout << "Hotel Name: " << hotel.hotelName << endl;
    cout << "Average Rating: " << hotel.averageRating() << endl;
    cout << "Total Reviews: " << hotel.reviewCount << endl;
    cout << "Reviews:" << endl;

    for(int i = 0; i < hotel.reviewCount; i++){
        cout << "Review ID: " << hotel.rv[i].getReviewID() 
             << ", Rating: " << hotel.rv[i].getRate() 
             << ", Comment: " << hotel.rv[i].getComment() 
             << ", Hotel Name: " << hotel.rv[i].getHotelName() 
             << endl;
    }
}
//this is the generating report function, you can call it in main or other files
// but i will not implement any friend function in main.cpp