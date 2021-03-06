//DESCRIPTION: Project 4 asks us to create a reverse polish notation calculator using stacks. There are a variety of ways to do this but the main point of
//this project is to get used to the stack and the operations that come along with it. 
//Since we weren't allowed to use the built in functions for stack, I decided to use a singly linked list to recreate it.
//CONTACT INFO: Teng Lin tml5566@psu.edu 610-554-6369
//FUNCTIONS: caseinsensitive, validinput, peek, push, pop
// *** I will explain below what each function does.
//REVISION HISTORY: Edit 3/20/18 by Teng Lin
//LIMITATIONS: There is a defined format for user input that should be entered. It should be comma separated and placed properly without any spaces. However, if the 
//user does not follow the format, it will be handled by outputting an error and reprompting the user for another input that is in the proper format.

//Standard include files that we need to use basic functions and keywords in c++.
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>

//Needed to use standard library keywords and functions.
using namespace std;

class RPN {
public:
	//We aren't really allowed to use the built in stack functions like top, pop, and push so I made a stack using a singly linked list and
	//implemented the functions that basically does the same thing.

	//Constructor sets top to NULL so that we have a starting point.
	RPN() {
		top = NULL;
	}

	//Effectively the same as the built in method of top which returns an integer of the top value on the stack.
	//No parameter. Returns an integer (top value).
	int peek() {
		return top->data;
	}

	//push function does the same as the built in stack function. I created a new node and set the data equal to the parameter number.
	//In the case where there are no other elements in the linked list, the new node is set to top. This would only realistically happen in 
	//this program for the first number. Otherwise the next pointer for n points to the old top and top is redefined as n.
	//push parameter is an integer. No return value.
	void push(int number) {
		//Creating the node and assigning data and next pointer.
		node *n = new node;
		n->data = number;
		n->next = NULL;
		//In the case where top is already NULL, top will be redefined as n. Only really happens for first number.
		if (top == NULL) {
			top = n;
			n = NULL;
		}
		//Most pushes will just create a new node that is redefined as the top and next pointer adjusted accordingly.
		else {
			n->next = top;
			top = n;
			n = NULL;
		}
	}

	//pop function that basically deletes the top value from the linked list. I created a new node called n and set it equal to top to avoid
	//deletion conflict with top term. Top is redefined as top->next before n (which was the top) is deleted.
	//No parameter. No return value.
	void pop() {
		node* n = new node;
		n = top;
		top = top->next;
		//To ensure there is no memory leakage.
		delete(n);
	}

	
	//This function is used mainly to make user input case insensitive. This is really only applicable when the user enters exit. If they
	//enter 'EXIT' or 'ExIt' it will still process effectively and exit the program.
	string caseinsensitive(string command) {
		for (int i = 0; i < command.size(); i++) {
			command[i] = tolower(command[i]);
		}
		return command;
	}

	//This is probably the meat of program because it deals with the validation of the user input. It would be pointless to try and process the input if it isn't even valid, 
	//so it is especially important to validate the input before continuing forward.
	//Parameter is the user input string called command. Returns true or false whether or the command is within the defined constraints.
	bool validinput(string command) {
		//array that contains the operators that are valid. Will be used to check if a specific character in the input is an operator symbol.
		char validChars[5] = { '+', '-', '/', '*', '^' };

		//Below are checks for whether or not the input is valid. There are a plethora of constraints that will be explained below.

		//String command cannot contain any invalid characters. This will loop through every character of the loop and check what type it is.
		//If it is not a number, math operator, comma, or space, then it will return false.
		for (int i = 0; i < command.size(); i++) {
			//Checks if character is a math operator.
			bool isSymbol = false;
			for (int j = 0; j < sizeof(validChars) / sizeof(validChars[0]); j++) {
				if (command[i] == validChars[j]) {
					isSymbol = true;
				}
			}
			//Checks if digit, symbol, space, or comma. If not, return false.
			if (!(isdigit(command[i])) && isSymbol == false && command[i] != ' ' && command[i] != ',') {
				return false;
			}
		}

		//In RPN calculations there is a pattern where the amount of digits is always 1 greater than the amount of math operators.
		//So, I found the count for both the symbols and digits and compared them to see if the condition holds. If not return false.
		int digitcount = 0;
		int symbolcount = 0;
		for (int i = 0; i < command.size(); i++) {
			//Counts number of symbols(math operators).
			for (int j = 0; j < sizeof(validChars) / sizeof(validChars[0]); j++) {
				if (command[i] == validChars[j]) {
					symbolcount++;
				}
			}

			//The reason why we have to include a while loop is because of number with more than one digit. To make sure that it only counts a double digit number once, we need to
			//use a while loop until the character is not a number.
			if (isdigit(command[i])) {
				int j = i;
				while (isdigit(command[j])) {
					j++;
				}
				i = j;
				digitcount++;
			}
		}
		//This condition is always true for RPN calculations.
		if (digitcount != symbolcount + 1) {
			return false;
		}


		//Another condition for RPN calculations where the last character cannot be a number and must be an operator, so we check for that.
		if (isdigit(command[command.size() - 1])) {
			return false;
		}

		//RPN Calculations always have an even number of commas because there are always an odd number of elements (numbers + math operators).
		//We loop through the command and check the number of commas and if it is not even, return false.
		int commacount = 0;
		for (int i = 0; i < command.size(); i++) {
			if (command[i] == ',') {
				commacount++;
			}
		}
		//Condition is always true for in reverse polish notation.
		if (commacount % 2 != 0) {
			return false;
		}

		//The size of the command must be at least 5. Any smaller would be impossible for a valid RPN calculation. Return false if command size is less than 5.
		if (command.size() < 5) {
			return false;
		}

		//If the user input command fulfills all the constraints then we can safely say that the input is valid and in reverse polish notation.
		return true;
	}
	
private:
	struct node {
		int data;
		node *next;
	};
	node *top;
};

int main() {
	//Introduction to what the program does and some precautionary words to avoid headache.
	cout << "Hello, this is a Reverse Polish Notation Calculator." << endl;
	cout << "The proper format for the input is comma separated values. Ex. 3,4,+,10,- You do not need an equal sign." << endl;
	
	//Creating an object so that we can use the functions that we defined in the RPN class.
	RPN object;
	//Instantiating a string vector and calling it myVector.
	vector<string> myVector;
	//character array that contains the valid math operators that can be used in the program.
	char isSymbol[5] = { '+', '-', '*', '/', '^' };
	
	//The loop below will loop forever until the user inputs 'exit'. This is good so that the user doesn't have to start the program everytime to make a calculation.
	string command = "";
	while (command != "exit") {
		//Part of the validation and defensive programming to ensure the input is valid.
		bool valid = false;
		while (valid == false) {
			//Taking in an input using the getline function and calling it command.
			cout << "Please enter an input in the proper format or enter 'exit'." << endl;
			getline(cin, command);
			//Turn the command string to lowercase, only really used in the case where the user enters 'exit' with capital letters.
			command = object.caseinsensitive(command);
			//To prevent the vector from saving the results of the last calculations, we must clear the values inside.
			myVector.clear();
			
			//Prelimary check to ensure that the input does not contain any unwanted spaces.
			bool nospaces = true;
			for (int i = 0; i < command.size(); i++) {
				if (command[i] == ' ' && nospaces == true) {
					nospaces == false;
				}
			}
			//If the user command is 'exit' valid is set to true and will disregard the conditions for the later else statements.
			if (command == "exit" && nospaces == true) {
				valid = true;
			}
			//If the user input is not 'exit' it will call the function validinput in RPN class to check if the input is valid.
			else if (object.validinput(command) && nospaces == true) {
				//If the condition is evaluated to true then we know the input is valid. So we can immediately set valid to true.
				valid = true;

				//Below is the part that parse the input string and puts all the numbers and math operators into a vector that I can use later to evaluate.
				string input = "";
				for (int i = 0; i < command.size(); i++) {
					//When we encounter a digit as a character, we must check if the number is more than one digit.
					//So we use a while loop and add to empty input string until we encounter a character that is not a digit.
					if (isdigit(command[i])) {
						int j = i;
						while (isdigit(command[j])) {
							input += command[j];
							j++;
						}
						i = j;
						myVector.push_back(input);
						input = "";
					}
					//Checking if the character is a valid symbol. 
					bool symbol = false;
					for (int k = 0; k < sizeof(isSymbol) / sizeof(isSymbol[0]); k++) {
						if (command[i] == isSymbol[k]) {
							symbol = true;
						}
					}
					//In the case where it is a valid math operator, we add the character to an empty string called take.
					//take is then added to the vector so we can use it later.
					if (symbol == true) {
						string take = "";
						take += command[i];
						myVector.push_back(take);
					}
				}

			}
			//If the user input is not 'exit' and not a valid input as defined by the validinput function, then we print out a error statement.
			//Valid is still false so the loop will continue and prompt the user again.
			else {
				cout << "No this is not a valid input. Try again." << endl;
			}
		}

		//Since we have a vector that contains all the important operations, we can finally use it to calculate the actual answer.
		//We loop through the vector and if the element is a number then we push it onto the stack. If the element is a math symbol then we have to perform and operation
		//which effectively pops off the top two values and computes them according to which math operator is given.
		for (int i = 0; i < myVector.size(); i++) {
			//The reason why we have a try catch is because we are attempting to convert the vector element to a integer using stoi.
			//If it is a number no problem, however, if it is an operator we catch the error and perform a calculation for operators.
			try {
				stoi(myVector[i]);
				object.push(stoi(myVector[i]));
			}
			//If the try statement doesn't work and there is an error, we know for a fact that myVector[i] element must be an operator.
			//That is a queue to perform the operation.
			//The operation with call the peek, push, and pop functions that I created using a singling linked list in the above RPN class.
			catch (exception e) {
				//Important to create integer variables to properly evaluate.
				int left, right, result;
				if (myVector[i] == "+") {
					//right is set to top value and then top value is popped off the stack.
					right = object.peek();
					object.pop();
					//left is same process. New top is set to left and popped off stack.
					left = object.peek();
					object.pop();
					//result is always equal to left (operator) right. 
					result = left + right;
					//The end result after calculation should be pushed back into the stack.
					object.push(result);
				}
				//Look at + operation for details.
				else if (myVector[i] == "-") {
					right = object.peek();
					object.pop();
					left = object.peek();
					object.pop();
					result = left - right;
					object.push(result);
				}
				//Look at + operation for details.
				else if (myVector[i] == "*") {
					right = object.peek();
					object.pop();
					left = object.peek();
					object.pop();
					result = left * right;
					object.push(result);
				}
				//Look at + operation for details.
				else if (myVector[i] == "/") {
					
					right = object.peek();
					object.pop();
					left = object.peek();
					object.pop();
					result = left / right;
					object.push(result);
				}
				//Look at + operation for details.
				else if (myVector[i] == "^") {
					
					right = object.peek();
					object.pop();
					left = object.peek();
					object.pop();
					//Using math function pow from math.h library.
					result = pow(left, right);
					object.push(result);
				}
				//Just in case, but really should never happen.
				else {
					cout << "Error" << endl;
				}

			}

		}
		//Will print out the evaluated answer.
		if (command != "exit") {
			cout << ">> " << object.peek() << endl;
		}

		//Keep in mind that the stack should have only one value (result) after the end of this.
	}

	//Graceful Termination.
	cout << "You have exited... Goodbye." << endl;
	system("pause");
	return 0;
}