#ifndef TWITTER_DATA_H
#define TWITTER_DATA_H

#include <iostream>
#include <string>

class TwitterData
{
public:
	std::string getUserName() const;   // we do want to return a copy of the string, not the pointer
	std::string getActualName() const; // we do want to return a copy of the string, not the pointer
	std::string getEmail() const;	   // we do want to return a copy of the string, not the pointer
	std::string getCategory() const;   // we do want to return a copy of the string, not the pointer
	int getNumTweets() const;		   // we do want to return a copy of the integer, not the pointer

	void setUserName(const std::string &newUserName);
	void setActualName(const std::string &newActualName);
	void setEmail(const std::string &newEmail);
	void setCategory(const std::string &newCategory);
	void setNumTweets(const int &newNumTweets);

	std::string print() const;

private:
	std::string mpUserName, mpActualName,
		mpEmail, mpCategory;
	int mpNumTweets;
};

#endif
