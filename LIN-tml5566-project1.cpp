//DESCRIPTION: Project 1 is a project that asks us to create a program that validates an email. 
//That means we are given an email address and we need to use certain guidelines to check if it is valid.
//CONTACT INFO: Teng Lin tml5566@psu.edu 610-554-6369
//FUNCTIONS: findUsername, findDomain, atValid, usernameValid, domainValid, emailValid 
//setEmail, setUsername, setDomain, getEmail, getUsername, getDomain *** I will explain below what each function does.
//REVISION HISTORY: Edit 1/20/18 by Teng Lin
//LIMITATIONS: Prompt accepts a string, so if you press enter it will keep going until you type something. 

//Standard include files that we need to use basic functions and keywords in c++.
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>

//These are the constant that are defined, specifically about the length requirements of username and domain of emails found online.
#define MINUSERNAMESIZE 1	//Minimum length of username in an email
#define MAXUSERNAMESIZE 64	//Maximum length of username in an email
#define MINDOMAINSIZE 1		//Minimum length of username in an email
#define MAXDOMAINSIZE 255	//Maximum length of username in an email

//Needed to use standard library keywords and functions.
using namespace std;

//This is the class constructor that sets up the framework of the program. 
//It establishes the main variables that I will be using and creates the setter and getter functions for these variables.
//Also contains the main functions I will be using.
class Constructor {
//public is open and changable which is appropriate for the setters and getters
public:
	//Accepts a string which is prompted in main and sets the string equal to the variable email. Does not return anything because void.
	void setEmail(string a) {
		email = a;
	}
	//Accepts a string which is found(by splitting email) in main and sets the string equal to the variable username.
	void setUsername(string a) {
		username = a;
	}
	//Accepts a string which is found(by splitting email) in main and sets the string equal to the variable domain.
	void setDomain(string a) {
		domain = a;
	}
	//Below are the getter functions that allow me to access the private variables email, username, and domain by
	//creating an object of this class and using these functions. They return the strings.
	string getEmail() {
		return email;
	}
	string getUsername() {
		return username;
	}
	string getDomain() {
		return domain;
	}

	//This function takes in the parameter of the email string and converts it into a new string called username.
	//This is done by setting username equal to the substring with bounds defined as 0 and the index of the '@' symbol.
	string findUsername(string email) {
		string username = email.substr(0, email.find('@')); //left bound is inclusive while rightbound is exclusive
		return username;
	}

	//This function takes in the parameters of the email string and the size of the username string as an integer.
	//It uses these two parameters to return a string called domain. Like the findUsername function, it uses
	//substrings and the find method to get the correct string. The only difference is the bounds.
	string findDomain(string email, int usernameSize) {
		//Left bound has a +1 because we don't want to include '@'. Right bound is basically domain.size().
		string domain = email.substr(email.find('@') + 1, email.size() - (usernameSize + 1));
		return domain;
	}

	//This is a boolean function used to check if there is the correct amount of @ symbols since an email must have only 1 @ symbol.
	//It accepts the email string and loops through it to check the # of occurances in the string.
	//If it is not 1, it will return false, otherwise return true. The results will be used to determine if email is valid.
	bool atValid(string email) {
		int atCount = 0;		//setting count to 0
		char atSymbol = '@';	//since the result of checking the index of a string is of type char, I had to make atSymbol into a character rather than a string.

								//loops through email string and checks if each char in string is the '@' symbol. Increase the count if it is.
		for (int i = 0; i < email.size(); i++) {
			if (email[i] == atSymbol) {
				atCount++;
			}
		}

		//if/else condition used for actual validation. Check if the number of '@' is allowed and outputs the appropriate message.
		if (atCount != 1) {
			cout << "This email has " << atCount << " \'@\' symbols. Invalid!" << endl;
			return false;
		}
		else {
			cout << email << " has a valid amount of \'@\' symbols." << endl;
			return true;
		}
	}

	//Boolean function that accepts the username string(which is found in main) and checks whether if falls under the correct requirements of a username.
	//Requirements that I used included the correct length and proper syntax. The username is limited to alphanumerical and some special characters.
	//Basically I check each of these conditions and if they fail anyone of them, I return false.
	bool usernameValid(string username) {
		string usernameSpecialChars = "!#$%&'*+-/=?^_`{|}~."; //These are the special characters along with alphanumerical allowed in username.
															  //I compare the size of the username string to the constant I established in the preprocessor define .. MINUSERNAMESIZE = 1
		if (username.size() < MINUSERNAMESIZE) {
			cout << "Username has no length!" << endl;
			return false;
		}
		//Same as above except as an upperbound for username size .. MAXUSERNAMESIZE = 64
		if (username.size() > MAXUSERNAMESIZE) {
			cout << "The username of the email is too long!" << endl;
			return false;
		}

		//This loop checks if the syntax of the string is correct. So it loops through the string and checks if each character falls under the guidelines of 
		//what is allowed (alphanumerical and special characters). This is done by doing an if/else for each character.
		//isalnum(username[i]) check if the character is alphanumerical .. returns true or false
		//usernameSpecialChars.find(username[i]) != string::npos checks if the character is inside the usernameSpecialChars string that I already defined above.
		//It returns true if there is a position in the string that contains that character. Basically if it exists in the string return true.
		for (int i = 0; i < username.size(); i++) {
			if ((isalnum(username[i])) || (usernameSpecialChars.find(username[i]) != string::npos)) {
				;
			}
			else {
				cout << "\'" << username[i] << "\'" << " is not a valid character you can use in the username. Invalid!" << endl;
				return false;
			}
		}

		cout << username << " is a valid username." << endl;
		return true;
	}

	//Boolean function that takes in the domain string(found in main) and checks the domain requirements to see if it is valid.
	//It returns true or false depending on if it passes the requirements of size and syntax.
	bool domainValid(string domain) {
		//Domain does not allowed as many special characters as username, only hyphen and period.
		string domainSpecialChars = "-.";
		//Comparing domain size to lower bound requirement .. MINDOMAINSIZE = 1
		if (domain.size() < MINDOMAINSIZE) {
			cout << "Domain has no length!" << endl;
			return false;
		}
		//Comparing domain size to upper bound requirement .. MAXDOMAINSIZE = 255
		if (domain.size() > MAXDOMAINSIZE) {
			cout << "The domain of the email is too long!" << endl;
			return false;
		}

		//Same function used in usernameValid. Loops through and checks if each character in string follows the syntax requirement of alphanumerical, hyphen, or period.
		for (int i = 0; i < domain.size(); i++) {
			if (isalnum(domain[i]) || (domainSpecialChars.find(domain[i]) != string::npos)) {
				;
			}
			else {
				cout << "\'" << domain[i] << "\'" << " is not a valid character you can use in the domain. Invalid!" << endl;
				return false;
			}
		}
		cout << domain << " is a valid domain." << endl;
		return true;
	}

	//Boolean function that takes in the strings email, username, and domain. This function calls all three functions atValid, usernameValid, and domainValid
	//and puts the appropriate parameter in each. A username is only valid if it passes all three requirements established in the above Valid functions. 
	//So that means if any of them return false, the whole emailValid will return false. That is why the if condition has and(&&).
	//The results of emailValid will be used for the final part in main
	bool emailValid(string email, string username, string domain) {
		if (atValid(email) && usernameValid(username) && domainValid(domain)) {
			return true;
		}
		else {
			return false;
		}
	}

//These are the main variables that I used throughout the program. They are kept private.
private:
	string email;
	string username;
	string domain;
};


//main 
int main() {
	Constructor object; //creating an object so I can use it to reference the private variable and the functions that I already made in Constructor class
	string response = ""; //empty string called response which I will use in while loop below

	//These undeclared string variables are placeholders so that I can user them to establish and set the private variables equal to them.
	string tempEmail;
	string tempUsername;
	string tempDomain;

	//The program asks us to validate the email and prompt the user whether or not they want to validate another email or quit.
	//Thats why I felt a while loop would be appropriate. The condition to break out of the loop is to have response = "n" which can be 
	//done in the prompt at the very bottom. If the user wants to continue they can enter any other key.
	while (response != "n") {
		//Prompts the user for the email and sets the private variable email equal to the input by using the object referencing the Constructor class.
		cout << "What is the email you want validated? " << endl;
		cin >> tempEmail;
		object.setEmail(tempEmail);

		//This calls the findUsername function defined above. The function returns the username and sets it equal to the private variable using object.
		tempUsername = object.findUsername(object.getEmail());
		object.setUsername(tempUsername);

		//Calls the findDomain function defined above. It returns the domain string and sets it equal to the private variable using object.
		tempDomain = object.findDomain(object.getEmail(), object.getUsername().size());
		object.setDomain(tempDomain);

		//If/else that calls the function emailValid that either returns true or false. The parameters for emailValid are found using the object.
		//Depending on the result of emailValid, it will print an appropriate response and tell the user whether or not the email is valid.
		if (object.emailValid(object.getEmail(), object.getUsername(), object.getDomain())) {
			cout << "Yes, " << object.getEmail() << " is a valid email!" << endl;
		}
		else {
			cout << object.getEmail() << " is not a valid email!" << endl;
		}

		//Prompts user whether or not they want to validate another email. Any key for yes, "n" for no.
		//The input of the user then updates the string value of response which is used in the while condition again.
		cout << "Do you want to enter another email? (ANYKEY/n)" << endl;
		cin >> response;
	}

	//Message to show that the program ended.
	cout << "You have exited the program. Goodbye." << endl;
	system("pause"); //Instead of breakpoints
	return 0;
}