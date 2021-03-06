/*
	Created by
	Ethan Roberts
	on 09/21/2019

	This program is a custom interpreter meant to read commands from a command line and then
	execute the commands.

	This program implements a tree along with a vector.  When values are being "pulled" from tree, they are inserted
	into the command vector.


*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

class interp {

public:
	string commandAry;
	string readCommand();
	void build(interp*, string, int);
	interp *rootSave;
	~interp();
	interp();

private:
	interp * newNode();
	void evaluate();
	interp * down;
	interp* right;
	char token;
	char value;
};

interp *root = nullptr;
vector<char>vect;
vector<char>::iterator it;
bool FOUNDCONS = false;


interp::interp() {

}

interp::~interp() {
	root = nullptr;
	rootSave = nullptr;
	this->down = nullptr;
	this->right = nullptr;
}




interp* interp::newNode() {
	interp *ptr = new interp;
	ptr->down = nullptr;
	ptr->right = nullptr;
	ptr->value = NULL;
	return ptr;
}




string interp::readCommand() {
	string command;
	cout << "> ";
	getline(cin, this->commandAry);  //read-in command
	command = this->commandAry;
	return command;
}



void interp::build(interp *ptr, string command, int index) {

	if (command[index] == '@' || command[index] == '!' || command[index] == '$') { 
		ptr = newNode();
		if (command[index] == '@') {
			ptr->token = '@';
		}
		else if (command[index] == '!') {
			ptr->token = '!';
		}
		else if (command[index] == '$') {
			ptr->token = '$';
			FOUNDCONS = true;
		}
		++index;
		build(ptr->down, command, index);
		ptr->evaluate();
		return;
	}
	if (root == NULL) {     //base case
		ptr = this->newNode();
		root = ptr;
		build(root, command, ++index);
		return;
	}
	if (index == command.length() - 1) {  // all data as been processed into tree
		return;
	}
	if (command[index] == '(') {
		ptr = newNode();
		ptr->value = '(';
		++index;
		build(ptr->down, command, index);
	 	if (FOUNDCONS == true && vect.size() > 0 && vect.front() == '(') {   
			it = vect.begin() + 1;
			vect.insert(it, ptr->value);
		} 
		if (vect.back() != ')' && ptr->token != '@' ) { vect.push_back(')'); }
		it = vect.begin();
		if (*it != '('  && ptr->token != '@') { vect.insert(it, ptr->value);; }
	}
	else if (command[index] >= 97 && command[index] <= 122 || (command[index] >= 48 && command[index] <= 57)) {  //it's a value
		ptr = newNode();
		ptr->value = command[index];
		++index;
		build(ptr->right, command, index);
		if (FOUNDCONS == true && vect.size() > 0 && vect.front() == '(') {
			it = vect.begin() + 1;
			vect.insert(it, ptr->value);
		}
		else{
		it = vect.begin();
		vect.insert(it, ptr->value);
		}
	}
	else if (command[index] == ')') {  
		ptr = newNode();
		ptr->value = command[index];
		++index;
		build(ptr->down, command, index);
	 	if (FOUNDCONS == true && vect.size() > 0 && vect.front() == '(') {
			it = vect.begin() + 1;
			vect.insert(it, ptr->value);
		} 
		if (ptr->value != ')') {    //actual data is incoming
			it = vect.begin();
			vect.insert(it, ptr->value);
		}
		else { ++index; }
	}
	else if (command[index] == ' ') {   //handles cases for if there are blanks in the command entered 
		++index;  
		build(ptr, command, index); 
	}
}


void interp::evaluate() {

	char element = '\0';
	if (this->token == '@') {     // if "car" command (get first element from list)
		it = vect.begin() + 1;
		element = *it;
		vect.clear();
		vect.push_back(element);
	}
	else if (this->token == '!') {        // if "cdr" command (delete first element and return list)
		vect.erase(vect.begin() + 1);
		it = vect.begin();
	}
	return;
}






int main()
{
	interp interp;
	vector<char>::iterator it;
	string command = "";

	while (command != "exit") {
		vect.clear();
		root = nullptr;
		FOUNDCONS = false;
		command = interp.readCommand();
		interp.build(root, command, 0);
		it = vect.begin();   // returning pointer from tree
		cout << "   ";
		for (auto x : vect) {
			cout << x;
		}
		cout << endl << endl;
	}
	return 0;
}