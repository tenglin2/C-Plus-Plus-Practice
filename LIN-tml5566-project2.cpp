//DESCRIPTION: Project 2 is a project that asks us to create a dynamic array that can be manipulated by the user through various commands.
//This program is strictly defensive programming so any invalid input will be handled. In most cases we are verifying that the input is a valid integer and not a string.
//The main point of this programming to exercise the basic functions and skills involved with arrays and pointers as well as manipulating the heap for memory storage.
//CONTACT INFO: Teng Lin tml5566@psu.edu 610-554-6369
//FUNCTIONS: commandlist, caseinsensitive, create, addElement, deleteElement, insertElement, size, count, util,
//shrink, print.          *** I will explain below what each function does.
//REVISION HISTORY: Edit 2/27/18 by Teng Lin
//LIMITATIONS: Most of the user input is for integers, so the user should enter a valid integer. However, if they don't enter an integer and enter a string, it will
//be handled by printing an error and prompting again.

//Standard include files that we need to use basic functions and keywords in c++.
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>

//Needed to use standard library keywords and functions.
using namespace std;


class DynamicArray {
public:
	//Below are the methods that I used for the majority of the processing in main. Most of them take the array and size of the array as a parameter. 
	//I have specified and detailed what each method does and how it is called in the main class.

	//Method used for a list of commands that the user can input. No parameter. Print out the commandlist.
	void commandlist() {
		cout << "Create     Add     Insert     Delete     Size     Count     Util     Shrink     Print     Exit     Help" << endl;
	}
	//Input needs to be case insensitive so this method takes all the character of the the string command and turns it to lower case.
	string caseinsensitive(string command) {
		for (int i = 0; i < command.size(); i++) {
			command[i] = tolower(command[i]);
		}
		return command;
	}

	//Parameters of array and size. Function manipulates the array by creating new space at end.
	//Used when the user wants to create extra space in the array. They will appear as null values at the end of the array.
	//This utilizes positive integer validation to prevent invalid entry like strings and prints and error.
	//Similar to the add function, it we create a temporary array, resize the original array and copy the contents of temparray into the original.
	//Since we are creating null spaces, the values that were not set in original array are set to -1. Finally delete temparray to prevent memory leakage.
	void create(int *array, int size) {
		//Validation for create input.
		int number = -1;
		while (number < 0) {
			cout << "How many spaces do you want to create? " << endl;
			cin >> number;
			if (cin.fail()) {
				cout << "You did not enter an integer. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			//We do not accept 0 as valid because it would pointless to create 0 new spaces.
			if (number < 1) {
				cout << "Your input is not valid" << endl;
			}
		}

		//Copying content of array into temparray. Resizing array with new size. Copying contents back and setting new spaces to null.
		int *temparray = array;
		int originalsize = size;
		size = size + number;
		array = new int[size];
		for (int i = 0; i < originalsize; i++) {
			array[i] = temparray[i];
		}
		for (int i = originalsize; i < size; i++) {
			array[i] = -1;
		}

		//Important to prevent memory leakage!!
		delete(temparray);
	}
	//Parameter of array and size. Function manipulates the dynamic array by adding a specified number to first null number, or creates new element if no null numbers.
	//Method addElement takes the array pointer and size of the array as parameters. Prompted number will replace the first occurance of a null number.
	//In the instance of no null values in the array, the array will increase by 1 size and add the number as the last element.
	void addElement(int *array, int size) {
		//Validation process to ensure that the input is a valid number > -1 and will not accept a string. Will loop again if error detected.
		int number = -1;
		while (number < 0) {
			cout << "What number do you want to add? " << endl;
			cin >> number;
			if (cin.fail()) {
				cout << "You did not enter an integer. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (number < 0) {
				cout << "Your input is not valid" << endl;
			}
		}

		//In the case where there is a sentinel/null value inside the array, the input number will replace the first instance of null.
		bool done = false;
		for (int i = 0; i < size; i++) {
			//We need the addition condition of done == false so that it doesn't loop over after it has already found the first instance of null.
			//It will only replace the first null value it encounters.
			if (*(array + i) == -1 && done == false) {
				*(array + i) = number;
				done = true;
			}
		}

		//In the scenario where there are no null values inside the array, we will need to create a new element to the array to add the number.
		//To do this we need to first create a int pointer temparray that equals array. This basically copies everything that is in array and puts
		//it into temparray. Now we redefine array with a new size to account for the additional number. We copy everything from temparray back into
		//the old array and set the last value equal to the input number. Finally we delete the temparray.
		if (done == false) {
			int *temparray = array;
			array = new int[++size];
			for (int i = 0; i < size - 1; i++) {
				array[i] = temparray[i];
			}
			array[size - 1] = number;
			//Important to prevent memory leakage!!
			delete(temparray);
		}
	}
	//Parameters are the array and size. Function manipulates dynamic array so that a specified index will be replaced with a specified number.
	//Takes the array and size of the array as parameters. Includes validation to ensure proper input and will loop again if an error occurs.
	//This method changes the number value for the index that is specified by the user, no matter if it is a valid element or null value.
	void insertElement(int *array, int size) {
		//Keep in mind that we need two validations since we are checking both the number and the index. The number must be 0 or greater.
		int number = -1;
		while (number < 0) {
			cout << "What number do you want to insert? " << endl;
			cin >> number;
			if (cin.fail()) {
				cout << "You did not enter an integer. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (number < 0) {
				cout << "Your input is not valid." << endl;
			}
		}

		//For index validation, it must be from 0 to the size of the array -1.
		int index = -1;
		while (index < 0 || index > size - 1) {
			cout << "What index do you want to the number to be inserted into? " << endl;
			cin >> index;
			if (cin.fail()) {
				cout << "You did not enter an integer. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (index < 0) {
				cout << "Your input is not valid." << endl;
			}
			if (index > size - 1) {
				cout << "This index does not exist." << endl;
			}
		}

		//The main purpose here is to reassign the value for array index with the given number. Here we used pointers to change value.
		*(array + index) = number;
	}

	//Parameters are the array and size. Function will manipulate array by replacing the specified index with the null value of -1.
	//Takes the array and the size of the array as parameters. Includes validation to make sure it is a valid number that already exists in the array.
	void deleteElement(int *array, int size) {
		//Validation to prevent strings from being passed.
		int number = -1;
		while (number < 0) {
			cout << "What number do you want to delete? " << endl;
			cin >> number;
			if (cin.fail()) {
				cout << "You did not enter an integer. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			//In the instance where the input cannot happen where the number is less than 0, since the array cannot have negative numbers.
			if (number < 0) {
				cout << "Your input is not valid" << endl;
			}
		}
		//Checking if this number exists in the array. If it does, boolean value done turns to true and replaces the value at the specific index to null -1.
		bool done = false;
		for (int i = 0; i < size; i++) {
			if (*(array + i) == number && done == false) {
				*(array + i) = -1;
				done = true;
			}
		}
		//In the instance where the input is not in the array, an error message is printed and the user must delete again with the correct number.
		if (done == false) {
			cout << "Your input does not exist in the array." << endl;
		}
	}

	//Parameter is size of the array.
	//Print out the size of the array including the null values.
	void size(int size) {
		cout << "The current size of the array is " << size << endl;
	}
	//Parameter is array and size.
	//Prints out the valid elements of the array that are not null values.
	void count(int *array, int size) {
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (*(array + i) != -1) {
				count++;
			}
		}
		cout << "The current count of the array is " << count << endl;
	}
	//Parameter is the dynamic array and size.
	//Prints out the utility of the array which is count of valid elements / total size of the array including null.
	void util(int *array, int size) {
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (*(array + i) != -1) {
				count++;
			}
		}
		double util = static_cast<double>(count) / static_cast<double>(size);
		cout << "The current util  of the array is " << util << endl;
	}
	//Parameter is array and size. Function manipulates the array by removing the occurances of null (-1) in the array.
	//Shrink method deletes all the null values in the current array. This is done by creating a temporary array that copies that non null numbers. The original array is set
	//as a new integer array of a size # of elements. The array copies everything back from the temp array.
	//We delete the arrays that we stored in the heap for nonnull index and the temp array. This is to make sure there is no memory leakage.
	void shrink(int *array, int size) {
		//It's necesssary to first find the number of elements in the array that are not null, because we will be defining an array with a specific size
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (*(array + i) != -1) {
				count++;
			}
		}
		int *nonnull = new int[count];

		//This nested loop is used to find the index of the nonnull numbers which will be used to reference the actual values in the array.
		for (int i = 0; i < count; i++) {
			for (int j = i; j < size; j++) {
				if (*(array + j) != -1) {
					*(nonnull + i) = j;
					goto flag;
				}
			}
		flag:
			cout << "";
		}

		//Creating a temporary array that copies all the values of array.
		int *temparray = array;
		//Changing the values in temparray to only those that are real elements and not null numbers. 
		for (int i = 0; i < count; i++) {
			temparray[i] = array[nonnull[i]];
		}

		//Changing the established size so that the array will fit and not have junk values.
		size = count;
		array = new int[size];

		//Copying the array with temparray values
		for (int i = 0; i < count; i++) {
			array[i] = temparray[i];
		}

		//Deleting nonnull and temparray arrays to prevent memory leakage
		delete(nonnull);
		delete(temparray);
	}

	//Parameter is array and size.
	//Simple printout of the array using a for loop and the given parameters of the array and size of the array.
	void print(int *array, int size) {
		for (int i = 0; i < size; i++) {
			cout << *(array + i) << " ";
		}
		cout << endl;
	}
	
private:
	int array[];
};

int main()
{
	//Below are the commands that are able to be process in this program. This array is used to validate if the user input can be processed.
	string validCommands[11] = {"create", "add", "insert", "delete", "size", "count", "util", "shrink", "print", "exit", "help"};
	//Creating an object that references the DynamicArray class so that I can use the methods I defined already.
	DynamicArray object;

	//Introduction on what the program does and how it works. Useful for users that don't have background in what the program is suppose to do.
	cout << "Hello, this program allows you to create a dynamic array. There are a variety of command you can implement including..." << endl;
	cout << "Create     Add     Insert     Delete     Size     Count     Util     Shrink     Print     Exit     Help" << endl;
	
	//Prompting the user for the size of the array that we start with.
	cout << "First let's create an array." << endl;
	
	//Whole part is used to validate the input of the user. This is defensive programming so we have to make sure the user does not enter a invalid number or a string.
	//Validation is built to loop again until they enter a valid size.
	int size = -1;
	while (size < 1) {
		cout << "What size do you want the array to start with?" << endl;
		cin >> size;
		//In the instance where the user enters a string, we clear and ignore entry and give an error message.
		if (cin.fail()) {
			cout << "You did not enter an integer. Try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		//In the instance where the user enters a number but it is 0, which would be pointless to create an array of 0 size, or if the user
		//enters a negative number, which is not possible for the size of an array.
		if (size < 1) {
			cout << "Your input is not valid" << endl;
		}
	}
	//Setting up the array that we will be using and setting the size from the user prompt
	int *array = new int[size];
	//Establishing Sentinel/Null values of -1 for all the elements in the array.
	for (int i = 0; i < size; i++) {
		*(array + i) = -1;
	}
	//Explanation to unaware user and basic print of the array that we have.
	cout << "Here is the array you start with. -1 means null value." << endl;
	for (int i = 0; i < size; i++) {
		cout << *(array + i) << " ";
	}
	cout << endl;

	//Here is the part where we continually prompt the user for a command. The whole part is checked for validation to make sure that any unacceptable input is handled and that
	//only the valid commands that were predefined above are allowed to process.
	//To start the loop, we must begin with an empty string called command, which is updated each loop by user input.
	string command = "";
	//Loop will continue until valid command exit is enter, whereby the loop and program will end.
	while (command != "exit") {
		//Validation for input to make sure it is acceptable.
		bool valid = false;
		while (valid == false) {
			cout << "Please enter a valid command, or enter 'help' for list of commands " << endl;
			cin >> command;
			//command is set to lowercase by the caseinsensitive method defined in DynamicArray. This is to make sure that any input that is uppercase
			//is immediately set to lower case before processing.
			command = object.caseinsensitive(command);
			//Looping through the validCommands array until we find a command that matches. If not, boolean value for valid is false.
			for (int i = 0; i < sizeof(validCommands) / sizeof(validCommands[0]); i++) {
				if (command == validCommands[i]) {
					valid = true;
				}
			}
			//When command is not in the list, valid stays false. We give an error message and loop through it again.
			if (valid == false) {
				cout << "Your input was not a valid command, try again." << endl;
			}
		}
		//This whole section is for processing the command that we have receive from the user. Most of these functions will be done by referencing the methods defined by
		//DynamicArray. So I use the object I created to access them.


		//Useful for users that forgot what the list of commands are
		if (command == "help") {
			object.commandlist();
		}

		//Used when the user wants to create extra space in the array. They will appear as null values at the end of the array.
		//This utilizes positive integer validation to prevent invalid entry like strings and prints and error.
		//Similar to the add function, it we create a temporary array, resize the original array and copy the contents of temparray into the original.
		//Since we are creating null spaces, the values that were not set in original array are set to -1. Finally delete temparray to prevent memory leakage.
		if (command == "create") {
			//Validation for create input.
			int number = -1;
			while (number < 0) {
				cout << "How many spaces do you want to create? " << endl;
				cin >> number;
				if (cin.fail()) {
					cout << "You did not enter an integer. Try again." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				//We do not accept 0 as valid because it would pointless to create 0 new spaces.
				if (number < 1) {
					cout << "Your input is not valid" << endl;
				}
			}

			//Copying content of array into temparray. Resizing array with new size. Copying contents back and setting new spaces to null.
			int *temparray = array;
			int originalsize = size;
			size = size + number;
			array = new int[size];
			for (int i = 0; i < originalsize; i++) {
				array[i] = temparray[i];
			}
			for (int i = originalsize; i < size; i++) {
				array[i] = -1;
			}
			
			//Important to prevent memory leakage!!
			delete(temparray);
			
		}

		//Involves adding a prompted positive integer to the array into a null value. If there is no null value, create another element/space for it.
		if (command == "add") {
			//Validation process to ensure that the input is a valid number > -1 and will not accept a string. Will loop again if error detected.
			int number = -1;
			while (number < 0) {
				cout << "What number do you want to add? " << endl;
				cin >> number;
				if (cin.fail()) {
					cout << "You did not enter an integer. Try again." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (number < 0) {
					cout << "Your input is not valid" << endl;
				}
			}

			//In the case where there is a sentinel/null value inside the array, the input number will replace the first instance of null.
			bool done = false;
			for (int i = 0; i < size; i++) {
				//We need the addition condition of done == false so that it doesn't loop over after it has already found the first instance of null.
				//It will only replace the first null value it encounters.
				if (*(array + i) == -1 && done == false ) {
					*(array + i) = number;
					done = true;
				}
			}

			//In the scenario where there are no null values inside the array, we will need to create a new element to the array to add the number.
			//To do this we need to first create a int pointer temparray that equals array. This basically copies everything that is in array and puts
			//it into temparray. Now we redefine array with a new size to account for the additional number. We copy everything from temparray back into
			//the old array and set the last value equal to the input number. Finally we delete the temparray.
			if (done == false) {
				int *temparray = array;
				array = new int[++size];
				for (int i = 0; i < size - 1; i++) {
					array[i] = temparray[i];
				}
				array[size - 1] = number;
				//Important to prevent memory leakage!!
				delete(temparray);
			}

		}

		//Prompts user for number and index and replaces the current number in the index with the input.
		if (command == "insert") {
			object.insertElement(array, size);
		}

		//Prompts user for a number. Will delete first instance of the number in the array. If no occurance, error message.
		if (command == "delete") {
			object.deleteElement(array, size);
		}

		//Tells the size, number of elements including null values of the array.
		if (command == "size") {
			object.size(size);
		}

		//Tells the number of elements excluding null values of the array.
		if (command == "count") {
			object.count(array, size);
		}

		//Tells the utilization, the count/size. What percent of the array are actual elements.
		if (command == "util") {
			object.util(array, size);
		}

		//Deletes all the null values inside the array.
		if (command == "shrink") {
			
			//It's necesssary to first find the number of elements in the array that are not null, because we will be defining an array with a specific size
			int count = 0;
			for (int i = 0; i < size; i++) {
				if (*(array + i) != -1) {
					count++;
				}
			}
			int *nonnull = new int[count];

			//This nested loop is used to find the index of the nonnull numbers which will be used to reference the actual values in the array.
			for (int i = 0; i < count; i++) {
				for (int j = i; j < size; j++) {
					if (*(array + j) != -1) {
						*(nonnull + i) = j;
						goto flag;
					}
				}
			flag:
				cout << "";
			}

			//Creating a temporary array that copies all the values of array.
			int *temparray = array;
			//Changing the values in temparray to only those that are real elements and not null numbers. 
			for (int i = 0; i < count; i++) {
				temparray[i] = array[nonnull[i]];
			}

			//Changing the established size so that the array will fit and not have junk values.
			size = count; 
			array = new int[size];

			//Copying the array with temparray values
			for (int i = 0; i < count; i++) {
				array[i] = temparray[i];
			}

			//Deleting nonnull and temparray arrays to prevent memory leakage
			delete(nonnull);
			delete(temparray);
		}

		//Used to print out the array into a readable format.
		if (command == "print") {
			object.print(array, size);
		}
		
	}

	//Graceful Termination.
	cout << "You have exited... Goodbye." << endl;

	system("pause");
    return 0;
	
}

