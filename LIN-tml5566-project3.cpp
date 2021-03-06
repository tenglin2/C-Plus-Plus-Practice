//DESCRIPTION: Project 3 is a project that asks us to create a dynamic array using linked lists that can be manipulated by the user through various commands.
//This program is strictly defensive programming so any invalid input will be handled. In most cases we are verifying that the input is a valid integer and not a string.
//The main point of this program is to learn an alternative method of creating a dynamic array using a doubly linked list. 
//This is done by creating node structures and connecting them together using pointers called next and prev.
//CONTACT INFO: Teng Lin tml5566@psu.edu 610-554-6369
//FUNCTIONS: commandlist, caseinsensitive, create, addElementFront, insertElement, addElementBack, deleteElement, removeFront, removeBack, size, print
// *** I will explain below what each function does.
//REVISION HISTORY: Edit 3/10/18 by Teng Lin
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


class LinkedList {
public:
	//Used for help prompt to output a list of the valid commands that the user can enter. No parameter or return value.
	void commandlist() {
		cout << "Create     AddFront     AddBack     Insert     Del     DelFront     DelBack     Size     Print     Exit     Help" << endl;
	}
	//Used to make sure that user input is case insensitive. Parameter is a string taken from user. Returns the string in all lowercase.
	string caseinsensitive(string command) {
		for (int i = 0; i < command.size(); i++) {
			command[i] = tolower(command[i]);
		}
		return command;
	}
	//The program automatically begins with this. It creates a initial node that has next and prev pointers set to NULL since there are no other nodes. 
	//It is also the head and tail pointer for the same reason. The main point of this function is to start off with a node 
	//so that it can be built into a larger linked list with other functions.
	//Takes no parameters. Has no return value. 
	void create() {
		//Prompt user for a number to set the value for the first node. Defensive programming to prevent invalid input.
		int number = -1;
		while (number < 0) {
			cout << "To create a linked list, we must first start with a node. Please enter a value for the first node." << endl;
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
		//Creates a new initial node 
		n = new node;
		//next and prev are set to NULL because there are currently no other nodes to reference.
		n->next = NULL;
		n->prev = NULL;
		//Data value for node is set to user input number.
		n->data = number;
		//Head and tail pointers both set to node because no other nodes to reference.
		head = n;
		tail = n;
	}
	//Creates a new node and sets its data value equal to the user input number. Adds to the chain by orienting pointers.
	//Takes no parameters. No return value.
	void addElementFront() {
		//User input, defensive programming validation.
		int number = -1;
		while (number < 0) {
			cout << "What number do you want to add to the front?" << endl;
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

		//Creates a new node and updates pointers so that it is new head.
		n = new node;
		n->prev = NULL;
		n->next = head;
		head->prev = n;
		n->data = number;
		head = n;

	}

	//Creates a new node and sets its data value equal to the input number. Its next pointer is set to null and prev pointer set to tail. Tail pointer is then set to the node.
	//Takes no parameters. No return value.
	void addElementBack() {
		//Input Validation.
		int number = -1;
		while (number < 0) {
			cout << "What number do you want to add to the back?" << endl;
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

		//Creates new node and adjusts the pointers so that it is new tail.
		n = new node;
		n->next = NULL;
		n->prev = tail;
		tail->next = n;
		n->data = number;
		tail = n;
	}

	//Inserts a user input number into a specified index of the the linked list. You can input an index that would be effectively at the very end.
	//No parameters taken. No return value.
	void insertElement() {
		//User input number validation.
		int number = -1;
		while (number < 0) {
			cout << "What number do you want to insert?" << endl;
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
		
		//Doing this operation to count the number of nodes within the linked list. Useful for later operation.
		int size = 0;
		node *temp = head;
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}

		//User input index validation.
		int index = -1;
		while (index < 0 || index > size ) {
			cout << "What index position do you want to insert the number?" << endl;
			cin >> index;
			if (cin.fail()) {
				cout << "You did not enter an integer. Try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (index < 0 || index > size) {
				cout << "Your input is not valid" << endl;
			}
		}
		
		//If index is 0, effectively the same process as addfront. So we create a new node and adjust the pointers.
		if (index == 0) {
			n = new node;
			n->prev = NULL;
			n->next = head;
			head->prev = n;
			n->data = number;
			head = n;
		}
		//If index is equal to size, it is effectively the same process as addback. We create new node and adjust the pointers.
		if (index == size) {
			n = new node;
			n->next = NULL;
			n->prev = tail;
			tail->next = n;
			n->data = number;
			tail = n;
		}
		//This part is where we actually insert the number. We go through the linked list until the count is equal to the specified index. From there we know that the node should be inserted into
		//That particular position. We update the pointers for the created node and the nodes that are suppose to be before and after it. 
		if ((index > 0) && (index < size)) {
			int count = 0;
			n = new node;
			n->data = number;
			temp = head;
			while (temp != NULL) {
				if (count == index) {
					temp->prev->next = n;
					n->prev = temp->prev;

					temp->prev = n;
					n->next = temp;
				}
				count++;
				temp = temp->next;
			}

		}
		//Output Message.
		cout << "Inserted " << number << " into index position " << index << "." << endl;
	}

	//This function takes a user input number and seeks out the first occurance of that number in the linked list. If it is found, it is deleted.
	//No parameters, no return value.
	void deleteElement() {
		//Finding side of linked list used later in other functions.
		int size = 0;
		node* temp = head;
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}
		//To prevent a pointless operation.
		if (size == 1) {
			cout << "You cannot delete the only element in the linked list." << endl;
		}
		else {
			//Number validation.
			int number = -1;
			while (number < 0) {
				cout << "What number do you want to delete?" << endl;
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

			//It is necessary to have a position integer as a way to count for the special cases where the number is exactly the first or last element in list. This is important
			//because they will have different pointers to adjust.
			int position = 0;
			//boolean flag is used to that the loop will stop on the first occurance of the number and not continue afterwards.
			bool flag = false;
			temp = head;
			//Goes through the linked list and checks if the input number exists. IF it does exist, it will adjust the pointers and stop the loop.
			while (temp != NULL && flag == false) {
				if (temp->data == number) {
					if (position == 0) {
						temp->next->prev = NULL;
						head = temp->next;
					}
					if (position == size - 1) {
						temp->prev->next = NULL;
						tail = temp->prev;
					}
					if (position > 0 && position < size - 1) {
						temp->prev->next = temp->next;
						temp->next->prev = temp->prev;
					}
					flag = true;
				}
				//Update/increment to continue loop
				if (flag == false) {
					position++;
					temp = temp->next;
				}
			}
			//In the case where the user input number does not exist in the linked list. Output message.
			if (flag == false) {
				cout << "The number you entered does not exist in the linked list." << endl;
			}

			//To prevent any memory leakage, we stopped the while loop exactly when the node temp would have a data value equal to the specified user input.
			//So by deleting temp, we delete the node with the specified number.
			delete(temp);
		}
	}

	//Deletes the first element of the linked list. Takes no parameters and no return value.
	void removeFront() {
		int size = 0;
		node* temp = head;
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}
		//To prevent a pointless operation.
		if (size == 1) {
			cout << "You cannot delete the only element in the linked list." << endl;
		}
		//Since the delete part is the head, we simply adjust the pointers and reassign head to the next value.
		else {
			temp = head;
			temp->next->prev = NULL;
			head = temp->next;
			//To prevent memory leakage we delete node temp which was first element.
			delete(temp);
			cout << "Deleted the first number in the linked list." << endl;
		}
	}
	//Deletes the last element of the linked list. Takes no parameters and no return value.
	void removeBack() {
		int size = 0;
		node* temp = head;
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}
		//To prevent a pointless operation.
		if (size == 1) {
			cout << "You cannot delete the only element in the linked list." << endl;
		}
		//Since the delete part is the tail, we simply adjust the pointers and reassign tail to prev value.
		else {
			temp = tail;
			temp->prev->next = NULL;
			tail = temp->prev;
			//To prevent memory leakage we delete the node temp which was last element.
			delete(temp);
			cout << "Deleted the last number in the linked list." << endl;
		}
	}
	//Goes through linked list and counts the total number of elements.
	//No parameters. No return value.
	void size() {
		int size = 0;
		node* temp = head;
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}
		//Main point is for output message to tell the user the size of the linked list so far.
		cout << "The size of the linked list is " << size << endl;
	}
	//Simple print out of the data values in th linked list. We traverse it using a temp node pointer set to head.
	void print() {
		node* temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
private:
	struct node {
		int data;
		node* next;
		node* prev;
	};
	node* head;
	node* tail;
	node* n;

};


int main()
{
	//Part of the user input validation for commands.
	string validCommands[11] = { "create", "addfront", "addback", "insert", "del", "delfront", "delback", "size", "print", "exit", "help" };
	//Creates an object that will reference and call the methods I made above.
	LinkedList object;

	//Introduction on what the program does. 
	cout << "Welcome, this program allows you to create a linked list. There are a variety of commands you can implement including..." << endl;
	cout << "Create     AddFront     AddBack     Insert     Del     DelFront     DelBack     Size     Print     Exit     Help" << endl;
	cout << endl;
	cout << "First let's create a linked list." << endl;
	object.create();

	//String command will constantly be updating and will continue to loop until the user enters exit.
	string command = "";
	while (command != "exit") {
		//User input validation to make sure it is a valid command. Accounts for different cases, making it case insensitive.
		bool valid = false;
		while (valid == false) {
			cout << "Please enter a valid command, or enter 'help' for list of commands " << endl;
			cin >> command;
			command = object.caseinsensitive(command);
			for (int i = 0; i < sizeof(validCommands) / sizeof(validCommands[0]); i++) {
				if (command == validCommands[i]) {
					valid = true;
				}
			}
			if (valid == false) {
				cout << "Your input was not a valid command, try again." << endl;
			}
		}

		//Depending on exactly what command is entered, it will call the function that was created in the LinkedList class.
		//For more information on the functions check above for what each one does.
		if (command == "help") {
			object.commandlist();
		}
		if (command == "create") {
			object.create();
		}
		if (command == "addfront") {
			object.addElementFront();
		}
		if (command == "addback") {
			object.addElementBack();
		}
		if (command == "insert") {
			object.insertElement();
		}
		if (command == "del") {
			object.deleteElement();
		}
		if (command == "delfront") {
			object.removeFront();
		}
		if (command == "delback") {
			object.removeBack();
		}
		if (command == "size") {
			object.size();
		}
		if (command == "print") {
			object.print();
		}

	}

	//Graceful termination.
	cout << "You have exited... Goodbye." << endl;


	system("pause");
	return 0;
}