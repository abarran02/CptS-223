#include <map>
#include <iostream>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = {{"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}};
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }

    // map scenario 1
    // new map with string keys and TwitterData values
    map<string, TwitterData> twitterUsers;
    // iterate over twitter_data list and map each username to corresponding data
    for (int i = 0; i < 5; i++) {
        twitterUsers[ twitter_data[i].getUserName() ] = twitter_data[i];
    }

    // iterate over map and print key-value pairs
    // with help from https://stackoverflow.com/a/21436440
    cout << "Print search by name map: " << endl;
    for (const auto &pair : twitterUsers) {
        cout << pair.first << " : " << pair.second.print() << endl;
    }

    // find user by username and print record
    // https://en.cppreference.com/w/cpp/container/map/find
    string userQuery = "savage1";
    auto userSearch = twitterUsers.find(userQuery);
    if (userSearch != twitterUsers.end()) {
        cout << "Found user record for " << userSearch->first << ":" << endl;
        cout << userSearch->second.print() << endl;

        // remove found record from map
        twitterUsers.erase(userQuery);
        cout << "Removed user record for " << userSearch->first << endl;
    } else {
        cout << "User record not found for username " << userSearch->first << endl;
    }

    // map scenario 2
    // new map with string keys and TwitterData values
    map<string, TwitterData> twitterEmails;
    // iterate over twitter_data list and map each email to corresponding data
    for (int i = 0; i < 5; i++) {
        twitterEmails[ twitter_data[i].getEmail() ] = twitter_data[i];
    }

    // iterate over map and print key-value pairs
    // with help from https://stackoverflow.com/a/21436440
    cout << "Print search by email map: " << endl;
    for (const auto &pair : twitterEmails) {
        cout << pair.first << " : " << pair.second.print() << endl;
    }

    // find user by email and print record
    // https://en.cppreference.com/w/cpp/container/map/find
    string emailQuery = "kat@gmail.com";
    auto emailSearch = twitterEmails.find(emailQuery);
    if (emailSearch != twitterEmails.end()) {
        cout << "Found user record for " << emailSearch->first << ":" << endl;
        cout << emailSearch->second.print() << endl;;

        // remove found record from map
        twitterEmails.erase(emailQuery);
        cout << "Removed user record for " << emailSearch->first << endl;
    } else {
        cout << "User record not found for email " << emailSearch->first << endl;
    }

    return 0;
}