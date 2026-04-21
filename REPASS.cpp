#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MAX_REVIEWS = 1000;
const int MAX_USERS = 500;
int readline(fstream &file){
    int count=0;
    string temp;
    while (getline(file, temp)){
        count++;
    }
    file.clear();
    file.seekg(0, ios::beg);
    return count;
}

void loaduserdata(fstream &file, string userID[], string userName[], string country[],
                  string stateName[], string email[], string membership[],
                  int points[],int numberOfUsers){
                int code=0;
                while(getline(file, userID[code],'\t')){
                    getline(file, userName[code],'\t');
                    getline(file, country[code], '\t');        
                    getline(file, stateName[code], '\t');
                    getline(file, email[code], '\t');
                    getline(file, membership[code], '\t');
                    file >> points[code]; 
                    file.ignore(); // to ignore the newline character after points
                      code++;
                          if (code>=numberOfUsers){
                                  break;
                          }
                }
file.clear();
file.seekg(0, ios::beg);
}

void loadreviewdata(fstream &file, string reviewID[], int rating[],
                    string reviewText[], string hotelName[], int numberOfReviews){
    int code=0;
    file.clear();
    file.seekg(0, ios::beg);
                while(getline(file, reviewID[code],'\t')){
                  string tempRate;
                    getline(file, tempRate,'\t');
                    getline(file, reviewText[code],'\t');
                    getline(file, hotelName[code]);        // etc.
                    rating[code] = stoi(tempRate);
                    code++;
                    if (code>=numberOfReviews){
                      break;
                    }
                }
}
void saveUserdata(fstream &file, string userID[], string userName[], string country[],
                  string stateName[], string email[], string membership[],
                  int points[],int totalUsers){
    file.clear();
    file.seekp(0, ios::beg);
    for (int i=0;i<totalUsers;i++){
        file << userID[i] << '\t'
             << userName[i] << '\t'
             << country[i] << '\t'
             << stateName[i] << '\t'
             << email[i] << '\t'
             << membership[i] << '\t'
             << points[i] << '\n';
    }
}

void saveReviewdata(fstream &file, string reviewID[], int rating[],
                    string reviewText[], string hotelName[], int totalReviews){
    file.clear();
    file.seekp(0, ios::beg);
    for (int i=0;i<totalReviews;i++){
        file << reviewID[i] << '\t'
             << rating[i] << '\t'
             << reviewText[i] << '\t'
             << hotelName[i] << '\n';
    }
}
//prototype for main table
void displayUserReviews(string[], string[], int, string[], int[], string[],string[],int);
void displayHotelReviews(string[], string[], int, string[], string[], int[],int,string[]);
void displayCompleteUserInfo(string[] , string[] , string [],string [], string [], string [],int[], int );
void displayPositiveHotelReviews(int[],string[],string[],int,string[],string[], int, string[]);
void displayActivitySummary(int ,int ,int []);
void displayUsersByMembership(string [], string [], string [],int [], int );
void displayTopReviewers(string [], string [], int ,string [], int );
void displayTop3(string [], string [], int ,string [], int );
void displayHotelRatingSummary(string [], int [], int ,int ,string []);
void addNewReview(string[], string [], int ,int [], string [], string [],int &, int [],string[],int &,string[]);
void sortUsersByPoints(string [],string [],string [],string [],string [],string [], int [],int );
void printUserwithPoints(string [],int [],int );
void sortHotelsByReviewCount(string [], int [], int ,int ,string []);
void printHotelswithReviewCount(string [], int [], int [], int );
string tolower(string);
bool searchText(string, string);
void keywordSearch(string[],string[],int[],int);



int main(){
fstream userfile("user.txt", ios::in | ios::out);
fstream reviewfile("review.txt", ios::in | ios::out);

if (!userfile || !reviewfile){
    cout << "Error opening files." << endl;
    return 1;
}

    int totalUsers = readline(userfile);
    int totalReviews = readline(reviewfile);
    
    //arrays for user.txt
    string userID[totalUsers];
    string username[totalUsers];
    string country[totalUsers];
    string state[totalUsers];
    string emel[totalUsers];
    string membership[totalUsers];
    int points[totalUsers];   
    loaduserdata(userfile, userID, username, country, state, emel, membership, points, totalUsers);

    //arrays for review.txt
    string reviewID[MAX_REVIEWS];
    int rating[MAX_REVIEWS];
    string reviewText[MAX_REVIEWS];
    string hotelName[MAX_REVIEWS];
    loadreviewdata(reviewfile, reviewID, rating, reviewText, hotelName, totalReviews);

    string uniqueHotels[MAX_REVIEWS];
    int uniqueHotelCount = 0;
    for (int i = 0; i < totalReviews; i++) {
        bool isUnique = true;
        for (int j =0;j<uniqueHotelCount;j++){
            if (hotelName[i]==uniqueHotels[j]){
                isUnique = false;
                break;
            }
        }
        if (isUnique){
            uniqueHotels[uniqueHotelCount] = hotelName[i];
            uniqueHotelCount++;
        }
    }

    // Menu-driven interface (commented out for now)
    int choice;

    do{
        cout<<"Welcome to the hotel review management system!"<<endl;
        cout<<"Menu Options:\n"<<endl;
        cout<<"1. Display all reviews by user"<<endl;
        cout<<"2. Display all reviews for hotel"<<endl;
        cout<<"3. Display complete user information"<<endl;
        cout<<"4. Display positive reviews (4 - 5) for 1 hotel"<<endl;
        cout<<"5. Display activity summary"<<endl;
        cout<<"6. Display users by membership"<<endl;
        cout<<"7. Top reviewer leaderboard"<<endl;
        cout<<"8. Top 3 reviewers"<<endl;
        cout<<"9. Hotel rating summary"<<endl;
        cout<<"10. Add new review"<<endl;
        cout<<"11. Sort users by points (highest -> lowest)"<<endl;
        cout<<"12. Sort hotels by number of reviews"<<endl;
        cout<<"13. Keyword search in review text"<<endl;
        cout<<"0. Exit"<<endl;

        cout<<"Enter your choice: ";
        cin >> choice;
        switch (choice){
            case 1:
                // Functionality for displaying all reviews by user
                displayUserReviews(userID, username, totalUsers, reviewID, rating, 
                    reviewText, hotelName, totalReviews);
                break;
            case 2:
                // Functionality for displaying all reviews for hotel
                displayHotelReviews(reviewID, username, totalReviews, reviewText, hotelName, rating,totalUsers,userID);
                break;
            case 3:
                // Functionality for displaying complete user information
                displayCompleteUserInfo(userID, username, country,state, emel, membership,points, totalUsers);
                break;
            case 4:
                // Functionality for displaying positive reviews for 1 hotel
                displayPositiveHotelReviews(rating,reviewText,hotelName,totalReviews,userID,username,totalUsers,reviewID);
                break;
            case 5:
                // Functionality for displaying activity summary(totaluser& total reviews,total points in system-wide)
                displayActivitySummary(totalUsers,totalReviews,points);
                break;
            case 6:
                // Functionality for displaying users by membership
                 displayUsersByMembership( userID,  username, membership, points, totalUsers);
                break;
            case 7:
                // Functionality for top reviewer leaderboard
                displayTopReviewers(userID, username, totalUsers, reviewID, totalReviews);
                break;
            case 8:
                // Functionality for top 3 reviewers
                displayTop3(userID, username, totalUsers, reviewID, totalReviews);
                break;
            case 9:
                // Functionality for hotel rating summary(average rating & total reviews per hotel)
                displayHotelRatingSummary( hotelName, rating, totalReviews, uniqueHotelCount, uniqueHotels);
                break;
            case 10:
                // Functionality for adding new review
                addNewReview( reviewID, userID, totalUsers, rating, reviewText, hotelName,
                totalReviews, points,uniqueHotels,uniqueHotelCount,membership);                  
                break;
            case 11:
                // Functionality for sorting users by points
                sortUsersByPoints( userID, username, country, state, emel, membership, points, totalUsers);
                printUserwithPoints( userID, points, totalUsers);
                break;
            case 12:
                // Functionality for sorting hotels by number of reviews
                sortHotelsByReviewCount(hotelName, rating, totalReviews, uniqueHotelCount, uniqueHotels);
                break;
            case 13:
                // Functionality for keyword search in review text
                keywordSearch(reviewText, hotelName, rating, totalReviews);
                break;
            case 0:
                break;
            case 14:
                // Functionality for testing   
                cout<<"newest user input is "<<reviewID[totalReviews-1]<<endl;
                cout<<"newest rating is "<<rating[totalReviews-1]<<endl;
                cout<<"newest review text is "<<reviewText[totalReviews-1]<<endl;
                cout<<"newest hotel name is "<<hotelName[totalReviews-1]<<endl;
                
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    cout<<"\nDo you want to return to main menu or quit this program? (Y for quit or press any other key to continue): ";
    char ans;
    cin>>ans;
    if (ans=='Y' || ans=='y'){
        break;
    }
    }while (true);

//start load file write back
saveUserdata(userfile, userID, username, country, state, emel, membership, points, totalUsers);
saveReviewdata(reviewfile, reviewID, rating, reviewText, hotelName, totalReviews);
userfile.close();
reviewfile.close();
cout<<"end of program"<<endl;
return 0;


}
//1
void displayUserReviews(string userID[], string username[], int totalUsers,
                        string reviewID[], int rating[],
                        string reviewText[], string hotelName[], int totalReviews){
    while (true){
        string searchUserID;
        cout<<"Enter user ID for total review check (e.g., U1001): ";
        cin>>searchUserID;
        bool userFound = false;
        string tempUserName;
        for (int i = 0; i < totalUsers; i++){
            if (userID[i] == searchUserID){
                userFound = true;
                tempUserName = username[i];
                break;
            }
        }
        if (!userFound){
            cout << "User ID not found. Please try again or check your ID is valid or not." << endl;
            return;
        }

        cout << "\n\tReviews by " << tempUserName << " (User ID: " << searchUserID << "):\n" << endl;

        //search and display reviews
        int count = 0;
        for (int j=0;j<totalReviews;j++){
            if (reviewID[j]==searchUserID){
                count ++;
                cout <<"Review #"<<count<<" :"<<endl;
                cout<<"Hotel Name: "<<hotelName[j]<<endl;
                cout<<"Rating: "<<rating[j]<<"/5"<<endl;
                cout<<"Review Text: "<<reviewText[j]<<endl;
                cout<<"-------------------------------------"<<endl;
            }
        }
    cout<<"Total Reviews by "<<tempUserName<<": "<<count<<endl;
    cout<<"\nDo you want to check another user for total reviews? (Y for yes or any other key to exit): ";
    char ans;  
    cin>>ans;
    if (ans=='Y' || ans=='y'){
        continue;
    } else {
        return;
    }
    }
}
//2
void displayHotelReviews(string reviewID[],string username[],int totalReviews,string reviewText[],string hotelName[],int rating[],int totalUsers
                       ,string userID[]){
    while (true){
        string searchHotelName;
        cout<<"Enter hotel name for total review check (e.g., Grand Imperial Hotel): ";
        cin.ignore();
        getline(cin,searchHotelName);
        bool hotelFound = false;
        for (int i = 0; i < totalReviews; i++){
            if (hotelName[i] == searchHotelName){
                hotelFound = true;
                break;
            }
        }
        if (!hotelFound){
            cout << "Hotel name not found. Please try again or check your hotel name is valid or not.\n" << endl;
            continue;
        }

        cout << "\n\tReviews for " << searchHotelName << ":\n" << endl;

        //search and display reviews
        string SearchedUsername;

        int count = 0;
        for (int j=0;j<totalReviews;j++){
            if (hotelName[j]==searchHotelName){
                count ++;
                cout <<"Review #"<<count<<endl;
                cout<<"User ID: "<<reviewID[j]<<endl;
            for(int k=0;k<totalUsers;k++){
                if (userID[k]==reviewID[j]){
                SearchedUsername = username[k];
                break;
                }
            }
                cout<<"Username: "<<SearchedUsername<<endl;
                cout<<"Rating: "<<rating[j]<<"/5"<<endl;
                cout<<"Review Text: "<<reviewText[j]<<endl;
                cout<<"-------------------------------------"<<endl;
            }
        }
    cout<<"Total Reviews for "<<searchHotelName<<": "<<count<<endl;
    cout<<"\nDo you want to check another hotel for total reviews? (Y for yes or any other key to exit): ";
    char ans;
    cin>>ans;
    if (ans=='Y' || ans=='y'){
        continue;
    } else {
        return;
    }
    }
}
//3
void displayCompleteUserInfo(string userID[], string username[], string country[],
                             string stateName[], string email[], string membership[],
                             int points[], int totalUsers){
    while(true){
        string searchUserName;
        cout<<"Enter user name for complete information check (e.g., Ali bin abu): ";
        cin.ignore();
        getline(cin,searchUserName);
        bool userFound = false;
        int userIndex = 0;
        for (int i = 0; i < totalUsers; i++){
            if (username[i] == searchUserName){
                userFound = true;
                userIndex = i;
                break;
            }
        }
        if (!userFound){
            cout << "User name not found. Please try again or check your name is valid or not." << endl;
            continue;
        }

        cout << "\nComplete Information for User Name: " << searchUserName << ":\n" << endl;
        cout << "User ID: " << userID[userIndex] << endl;
        cout << "Country: " << country[userIndex] << endl;
        cout << "State: " << stateName[userIndex] << endl;
        cout << "Email: " << email[userIndex] << endl;
        cout << "Membership: " << membership[userIndex] << endl;
        cout << "Points: " << points[userIndex] << endl;
    
        cout<<"\nDo you want to check another user for complete information? (Y for yes or any other key to exit): ";
        char ans;  
        cin>>ans;
        if (ans=='Y' || ans=='y'){
            continue;
        } else {
            return;
        }
    }
}
//4
void displayPositiveHotelReviews(int rating[],string reviewText[],string hotelName[],int totalReviews,string userID[],string username[]
                                ,int totalUsers,string reviewID[]){
    while (true){
        string searchHotelName;
        cout<<"Enter hotel name for Positive review check (e.g., Grand Imperial Hotel): ";
        cin.ignore();
        getline(cin,searchHotelName);
        bool hotelFound = false;
        for (int i = 0; i < totalReviews; i++){
            if (hotelName[i] == searchHotelName){
                hotelFound = true;
                break;
            }
        }
        if (!hotelFound){
            cout << "Hotel name not found. Please try again or check your hotel name is valid or not." << endl;
            return;
        }

        cout << "\nReviews for " << searchHotelName << ":\n" << endl;

        string SearchedUsername;
        int count = 0;
        for (int j=0;j<totalReviews;j++){
            if (hotelName[j]==searchHotelName && (rating[j]==4 || rating[j]==5)){
                count ++;
                cout <<"Positive Review #"<<count<<endl;
                cout<<"User ID: "<<reviewID[j]<<endl;
            for(int k=0;k<totalUsers;k++){
                if (userID[k]==reviewID[j]){
                SearchedUsername = username[k];
                break;
            }
        }
                cout<<"Username: "<<SearchedUsername<<endl;
                cout<<"Review Text: "<<reviewText[j]<<endl;
                cout<<"-------------------------------------"<<endl;
            }
        }
        cout<<"Total Positive Reviews (4-5) for "<<searchHotelName<<": "<<count<<endl;
        cout<<"\nDo you want to check another hotel for positive reviews? (Y for yes or any other key to exit): ";
        char ans;
        cin>>ans;
        if (ans=='Y' || ans=='y'){
            continue;
        } else {
            break;
        }
    }
}
//5
void displayActivitySummary(int totalUsers,int totalReviews,int points[]){
    cout<<"\nActivity Summary\n"<<endl;
    cout<<"Total Users in the System: "<<totalUsers<<endl;
    cout<<"Total Reviews in the System: "<<totalReviews<<endl;
    int totalPoints = 0;
    for (int i=0;i<totalUsers;i++){
        totalPoints += points[i];
    }
    cout<<"Total Points in the System: "<<totalPoints<<endl;
}
//6
void displayUsersByMembership(string userID[], string username[], string membership[],int points[], int totalUsers){
    cout<<"\nUsers by Membership\n"<<endl;
        string memberships[] = {"Platinum", "Gold", "Silver", "Basic"};
        if (totalUsers==0){
            cout<<"No users available in the system."<<endl;
            return;
        }
        for(int i =0;i<4;i++){
            cout<<"\nMembership Level: "<<memberships[i]<<endl<<endl;
            bool found = false;
            for(int j=0;j<totalUsers;j++){
                if(membership[j]==memberships[i]){
                    found = true;
                    cout<<"User ID: "<<userID[j]<<endl;
                    cout<<"Username: "<<username[j]<<endl;
                    cout<<"Points: "<<points[j]<<endl;
                    cout<<"-------------------------------------"<<endl;
                }
            }
            if (!found){
                cout<<"No users with "<<memberships[i]<<" membership."<<endl;
                cout<<"-------------------------------------"<<endl;
            }
        }
}
//7
void displayTopReviewers(string userID[], string username[], int totalUsers,
                         string reviewID[], int totalReviews){
    int reviewcounts[totalUsers] = {0};
    // Count reviews per user
    for (int i=0;i<totalReviews;i++){
        for (int j=0;j<totalUsers;j++){
            if (reviewID[i]==userID[j]){
                reviewcounts[j]++;
            }
        }
    }
    //clone arrays for sorting
    string sortedUserID[totalUsers];
    string sortedUsername[totalUsers];
    int sortedReviewCounts[totalUsers];
    for (int i=0;i<totalUsers;i++){
        sortedUserID[i] = userID[i];
        sortedUsername[i] = username[i];
        sortedReviewCounts[i] = reviewcounts[i];
    }
    //bubble sort
    for (int i=0;i<totalUsers-1;i++){
        for (int j=0;j<totalUsers-i-1;j++){
            if (sortedReviewCounts[j]<sortedReviewCounts[j+1]){
                //swap userID
                string tempID = sortedUserID[j];
                sortedUserID[j] = sortedUserID[j+1];
                sortedUserID[j+1] = tempID;
                //swap username
                string tempName = sortedUsername[j];
                sortedUsername[j] = sortedUsername[j+1];
                sortedUsername[j+1] = tempName;
                //swap counts
                int tempCount = sortedReviewCounts[j];
                sortedReviewCounts[j] = sortedReviewCounts[j+1];
                sortedReviewCounts[j+1] = tempCount;
            }
        }
    }
    cout<<"\nTop Reviewers Leaderboard\n"<<endl;
    cout<<left<<setw(15)<<"User ID"<<setw(25)<<"Username"<<setw(15)<<"Review Count"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    for (int i=0;i<totalUsers;i++){
        cout<<left<<setw(15)<<sortedUserID[i]<<setw(25)<<sortedUsername[i]<<setw(15)<<sortedReviewCounts[i]<<endl;
    }
}
//8
void displayTop3(string userID[], string username[], int totalUsers,
                         string reviewID[], int totalReviews){ //just change the function 7
    int reviewcounts[totalUsers] = {0};
    // Count reviews per user
    for (int i=0;i<totalReviews;i++){
        for (int j=0;j<totalUsers;j++){
            if (reviewID[i]==userID[j]){
                reviewcounts[j]++;
            }
        }
    }
    //clone arrays for sorting
    string sortedUserID[totalUsers];
    string sortedUsername[totalUsers];
    int sortedReviewCounts[totalUsers];
    for (int i=0;i<totalUsers;i++){
        sortedUserID[i] = userID[i];
        sortedUsername[i] = username[i];
        sortedReviewCounts[i] = reviewcounts[i];
    }
    //bubble sort
    for (int i=0;i<totalUsers-1;i++){
        for (int j=0;j<totalUsers-i-1;j++){
            if (sortedReviewCounts[j]<sortedReviewCounts[j+1]){
                //swap userID
                string tempID = sortedUserID[j];
                sortedUserID[j] = sortedUserID[j+1];
                sortedUserID[j+1] = tempID;
                //swap username
                string tempName = sortedUsername[j];
                sortedUsername[j] = sortedUsername[j+1];
                sortedUsername[j+1] = tempName;
                //swap counts
                int tempCount = sortedReviewCounts[j];
                sortedReviewCounts[j] = sortedReviewCounts[j+1];
                sortedReviewCounts[j+1] = tempCount;
            }
        }
    }
    cout<<"\nTop 3 user that review\n"<<endl;
    for (int i=0;i<3;i++){
        cout<<"Rank #"<<i+1<<endl;
        cout<<"User ID: "<<sortedUserID[i]<<endl;
        cout<<"Username: "<<sortedUsername[i]<<endl;
        cout<<"Review Count: "<<sortedReviewCounts[i]<<endl;
        cout<<"-------------------------------------\n"<<endl;
    }
}
//9
void displayHotelRatingSummary(string hotelName[], int rating[], int totalReviews,int uniquehotelCount,string uniqueHotels[]){
    cout<<"\nHotel Rating Summary\n"<<endl;
    for (int i=0;i<uniquehotelCount;i++){
        int count=0;
        int sum=0;
        for(int j=0;j<totalReviews;j++){
            if (hotelName[j]==uniqueHotels[i]){
                count++;
                sum += rating[j];
            }
        }
        double average = (count==0)? 0.0 : static_cast<double>(sum)/count;
        cout<<"Hotel Name: "<<uniqueHotels[i]<<endl;
        cout<<"Total Reviews: "<<count<<endl;
        cout<<"Average Rating: "<<fixed<<setprecision(2)<<average<<"/5\n"<<endl;
    }
}
//10
void addNewReview(string reviewID[], string userID[], int totalUsers,int rating[], string reviewText[], string hotelName[],
    int &totalReviews, int points[],string uniqueHotels[], int &uniqueHotelCount,string membership[]){
        if (totalReviews >= MAX_REVIEWS){
            cout << "Cannot add more reviews. Maximum limit reached." << endl;
            return;
        }
    while (true){
        string newReviewUserID;
        cout << "Enter your User ID to add a new review: ";
        cin >> newReviewUserID;

        // if (totalUsers == 0){
        //     cout << "No users available in the system." << endl;
        //     return;
        // }

        int userIndex = -1;
        for (int i = 0; i < totalUsers; i++){
            if (userID[i] == newReviewUserID){
                userIndex = i;
                break;
            }
        }
        if (userIndex == -1){
            cout << "User ID not found. Please try again or check your ID is valid or not." << endl;
            continue;
        }

        reviewID[totalReviews] = newReviewUserID;

        int ratingIn;
        do {
            cout << "Enter rating (1-5): ";
            cin >> ratingIn;
            if (ratingIn < 1 || ratingIn > 5){
                cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
                continue;
            }
            break;
        } while (true);

        cin.ignore(); // consume '\n' before getline
        rating[totalReviews] = ratingIn;

        string reviewTextIn;
        do {
            cout << "Enter review text: ";
            getline(cin, reviewTextIn);
            if (reviewTextIn.empty()){
                cout << "Review text cannot be empty. Please enter valid review text." << endl;
                continue;
            }
            reviewText[totalReviews] = reviewTextIn;
            break;
        } while (true);

        string hotelNameIn;
        do {
            cout << "Enter hotel name: ";
            getline(cin, hotelNameIn);
            if (hotelNameIn.empty()){
                cout << "Hotel name cannot be empty. Please enter valid hotel name." << endl;
                continue;
            }
            hotelName[totalReviews] = hotelNameIn;
            break;
        } while (true);

        int basicpointearned = 100;
        int wordcount = 0;
        bool inWord = false;
        for (char c : reviewTextIn){
            if (isspace(static_cast<unsigned char>(c))){
                if (inWord){
                    ++wordcount;
                    inWord = false;
                }
            } else {
                inWord = true;
            }
        }
        if (inWord) ++wordcount;
        if (wordcount > 50) basicpointearned += 10;

        // update the correct user's points
        points[userIndex] += basicpointearned;
        cout << "You have earned " << basicpointearned << " points for this review!" << endl;
        cout << "Review added successfully!" << endl;

        string oldmembership=membership[userIndex];
        string newmembership=oldmembership;
        if(points[userIndex]>=10000) newmembership="Platinum";
        else if(points[userIndex]>=5000) newmembership="Gold";
        else if(points[userIndex]>=1000) newmembership="Silver";
        else newmembership="Basic";

        if (newmembership != oldmembership){
            membership[userIndex] = newmembership;
            cout << "Congratulations! Your membership has been upgraded to " << newmembership << "!" << endl;
            cout<<"Your current points: "<<points[userIndex]<<endl;
        }

        bool isUnique = true;
        for (int i =0;i<uniqueHotelCount;i++){
            if (hotelName[totalReviews]==uniqueHotels[i]){
                isUnique = false;
                break;
            }
        }
        if(isUnique){
            uniqueHotels[uniqueHotelCount] = hotelName[totalReviews];
            uniqueHotelCount++;
        }

        ++totalReviews;

        cout << "\nDo you want to add another review? (Y for yes or any other key to exit): ";
        char ans;
        cin >> ans;
        if (ans == 'Y' || ans == 'y'){
            cin.ignore(); // prepare for next getline
            continue;
        } else break;
    }
}
//11(a)
void sortUsersByPoints(string userID[],string userName[],string country[],string state[],string emel[],string membership[], int points[],int totalUsers){
    for(int i=0;i<totalUsers-1;i++){
        for(int j=0;j<totalUsers-i-1;j++){
            if(points[j]<points[j+1]){
                //swap points
                int tempPoints = points[j];
                points[j] = points[j+1];
                points[j+1] = tempPoints;
                //swap userID
                string tempID = userID[j];
                userID[j] = userID[j+1];
                userID[j+1] = tempID;
                //swap username
                string tempName = userName[j]; 
                userName[j] = userName[j+1];
                userName[j+1] = tempName;
                //swap country
                string tempCountry = country[j];
                country[j] = country[j+1];
                country[j+1] = tempCountry;
                //swap state
                string tempState = state[j];
                state[j] = state[j+1];
                state[j+1] = tempState;
                //swap email
                string tempEmail = emel[j];
                emel[j] = emel[j+1];
                emel[j+1] = tempEmail;
                //swap membership
                string tempMembership = membership[j];
                membership[j] = membership[j+1];
                membership[j+1] = tempMembership;
                
            }
        }
    }
    cout<<"\nUsers sorted by points (highest to lowest) in user file\n"<<endl;
}

//11(b)
void printUserwithPoints(string userID[],int points[],int totalUsers){
    for (int i=0;i<totalUsers;i++){
        cout<<"count "<<i+1<<". User ID: "<<userID[i]<<", Points: "<<points[i]<<endl;
    }
}
//12
void sortHotelsByReviewCount(string hotelName[], int rating[], int totalReviews,int uniquehotelCount,string uniqueHotels[]){
    int reviewcount[uniquehotelCount]={0};
    double averageReview[uniquehotelCount]={0};
    for (int i=0;i<uniquehotelCount;i++){
            int count=0;
            int sum=0;
            for(int j=0;j<totalReviews;j++){
                if (hotelName[j]==uniqueHotels[i]){
                    count++;
                    sum += rating[j];
                }
            }
            double average = (count==0)? 0.0 : static_cast<double>(sum)/count;
            reviewcount[i] = count;
            averageReview[i] = average;
    }
    for (int i=0;i<uniquehotelCount-1;i++){
        for (int j=0;j<uniquehotelCount-i-1;j++){
            if (reviewcount[j]<reviewcount[j+1]){
                //swap review count
                int tempCount = reviewcount[j];
                reviewcount[j] = reviewcount[j+1];
                reviewcount[j+1] = tempCount;
                //swap average review
                double tempAvg = averageReview[j];
                averageReview[j] = averageReview[j+1];
                averageReview[j+1] = tempAvg;
                //swap hotel name
                string tempHotel = uniqueHotels[j];
                uniqueHotels[j] = uniqueHotels[j+1];
                uniqueHotels[j+1] = tempHotel;
            }
        }
    }

        for (int i=0;i<uniquehotelCount;i++){
            cout<<"count "<<i+1<<". Hotel Name: "<<uniqueHotels[i]<<", Total Reviews: "<<reviewcount[i]
            <<", Average Rating: "<<fixed<<setprecision(2)<<averageReview[i]<<"/5"<<endl;
    }
}
//13(tolower)
string tolower_case(string str){
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');  
        }
    }
    return str;
}
//13(search)
bool searchText(string reviewSentence,string keyword){
    string lowerReview = tolower_case(reviewSentence);
    string lowerKeyword = tolower_case(keyword);
    string word="";
    for (int i=0;i<lowerReview.length();i++){
        if (isspace(static_cast<unsigned char>(lowerReview[i]))){
            if (word == lowerKeyword){
                return true;
            }
            word = "";
        } else {
            word += lowerReview[i];
        }
    }
    if (word == lowerKeyword){
        return true;
    }
    return false;
}
//13(main)
void keywordSearch(string reviewText[],string hotelName[],int rating[],int totalReviews){
    while (true){
        string keyword;
        cout<<"Enter keyword to search in review text (more than 3 characters): ";
        cin.ignore();
        getline(cin,keyword);
        if (keyword.length() < 3){
            cout << "Keyword must be more than 3 characters. Please try again." << endl;
            continue;
        }

        bool found = false;
        cout<<"\nSearch Results \""<<keyword<<"\":\n"<<endl;
        for (int i=0;i<totalReviews;i++){
            if (searchText(reviewText[i], keyword)){
                found = true;
                cout<<"Hotel Name: "<<hotelName[i]<<endl;
                cout<<"Rating: "<<rating[i]<<"/5"<<endl;
                cout<<"Review Text: "<<reviewText[i]<<endl;
                cout<<"-------------------------------------"<<endl;
            }
        }
        if (!found){
            cout<<"No reviews found containing the keyword \""<<keyword<<"\"."<<endl;
        }
        cout<<"\nDo you want to search another keyword? (Y for yes or any other key to exit): ";
        char ans;
        cin>>ans;
        if (ans=='Y' || ans=='y'){
            continue;
        } else {
            break;
        }
    }
}


//temp
