//DESCRIPTION: Project 5 is a short and simple program that accepts a character string and outputs the string in reverse order. The catch is that
//this must be done using a recursive algorithm.
//CONTACT INFO: Teng Lin tml5566@psu.edu 610-554-6369
//FUNCTIONS: reverse
// *** I will explain below what each function does.
//REVISION HISTORY: Edit 3/31/18 by Teng Lin
//LIMITATIONS: The project did not specify any constraints for the input string. So whatever is entered by the user will be reversed. There are no limitations for input.

//Standard include files that we need to use basic functions and keywords in c++.
#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <iomanip>

//Needed to use standard library keywords and functions.
using namespace std;

//The class called Flip contains the reverse function. We call this class using an object in main.
class Flip {
public:
	//The function reverse has a parameter of string input and returns the input after it has been reverse.
	string reverse(string input) {
		//Base case for recursion happens when the length of the input equals 0. This is because for every recursive loop, input is shortened by 1 on the front.
		//When there is nothing left to take from input, we can return.
		if (input.length() == 0) {
			return input;
		}
		//Recursive step returns reverse(input.substr(1)) + input[0] which basically takes the front character in the input and adds it to the back.
		//The recursive step takes the new input without the front character using substr method.
		else {
			return reverse(input.substr(1)) + input[0];
		}
	}
};

int main() {
	//Creating an object so that we can call the functions in Flip.
	Flip object;
	//Instantiating strings called input and output.
	string input;
	string output;
	//Prompting user for character string.
	cout << "Input: ";
	//Setting input variable to whatever the user input.
	getline(cin, input);
	//Calling the reverse function in Flip and putting the user input as the parameter. 
	//After it finishes, it should return the reverse of the string. We assign output string to equal the returned string.
	output = object.reverse(input);
	//Outputs the reverse of the original input.
	cout << "Output: " << output << endl;
	system("pause");
	return 0;
}