/*
   Created by
   Ethan Roberts
   on 08/23/2019

   This program is an interpreter.  This program will read from a text file, interpret each line,
   and then execute according to the interpretation.

   example of file-format that will be read-in:  +0001000002
                                                 +0000000003
                                                 +0256000004
                                                 +0250000005
                                                 -7123451234
                                                 -7111111111
                                                 +9999999999
                                                 +8000000777
                                                 +8000000778
                                                 -8777000000
                                                 -8003000000
                                                 +9999999999
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void looper();

struct interpreter {
	string programAry[999];
	long long int dataAry[999];
	bool endOfInitialData = false;
	string *IP = nullptr;
	string *restore;
	string instruction;
	int firstOct = 0;
	int secOct = 0;
	int thirdOct = 0;
	int foundNine = 0;
	bool looperRunning = false;
	int sevenCounter = 0;

};

interpreter interp;


// This function converts ascii to int
int convertToInt(string myString, int startSub, int endSub) {
	int size = 0;
	int temp = 0;
	int number = 0;
	temp = myString[startSub] - '0';  //convert to int
	number = temp;

	for (int i = startSub + 1; i <= endSub; ++i) {
		number = number * 10;
		temp = myString[i] - '0';
		number = number + temp;
	}
	return number;
}





void checkOpcode(string myString) {
	char opCode = NULL;
	opCode = myString[1];  //get opcode
	int arraySize = 0;
	int data = 0;
	int index = 0;
	string *restore;

	if (myString[0] == '+') {
		switch (opCode) {
		case '0':  interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			data = interp.firstOct; // value that will be initialized to element
			interp.dataAry[interp.thirdOct] = data;
			break;
		case '1':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.firstOct] + interp.dataAry[interp.secOct];
			break;
		case '2':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.firstOct] * interp.dataAry[interp.secOct];
			break;
		case '3':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.firstOct] * interp.dataAry[interp.firstOct];
			break;
		case '4':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			if (interp.dataAry[interp.firstOct] == interp.dataAry[interp.secOct]) {
				interp.IP = &interp.programAry[interp.thirdOct];       // loop back to location
			}
			break;
		case '5':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			if (interp.dataAry[interp.firstOct] >= interp.dataAry[interp.secOct]) {
				interp.IP = &interp.programAry[interp.thirdOct];       // loop back to location
			}
			break;
		case '6':  interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);     // array index
			interp.thirdOct = convertToInt(myString, 8, 10);
			index = interp.dataAry[interp.secOct];
			interp.dataAry[interp.thirdOct] = interp.dataAry[index];
			break;
		case '7':  interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			++interp.sevenCounter;
			if (interp.dataAry[interp.firstOct] < interp.dataAry[4]) {  //element 4 is array size
				++interp.dataAry[interp.firstOct];                      //increment i
				interp.IP = &interp.programAry[interp.thirdOct];       // loop back to location
				if (interp.looperRunning == false) {
					interp.looperRunning = true;
					looper();
				}
			}
			break;
		case '8':  	interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);     // array index
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.thirdOct];  // move data into temp location
			break;
		default:   interp.endOfInitialData = true;  // +9 was encountered
			break;
		}
	}
	else if (myString[0] == '-') {
		switch (opCode) {
			break;
		case '1':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.firstOct] - interp.dataAry[interp.secOct];
			break;
		case '2':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.firstOct] / interp.dataAry[interp.secOct];
			break;
		case '3':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = sqrt(interp.dataAry[interp.firstOct]);
			break;
		case '4':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			if (interp.dataAry[interp.firstOct] != interp.dataAry[interp.secOct]) {
				interp.IP = &interp.programAry[interp.thirdOct];       // loop back to location
			}
			break;
		case '5':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);
			interp.thirdOct = convertToInt(myString, 8, 10);
			if (interp.dataAry[interp.firstOct] < interp.dataAry[interp.secOct]) {
				interp.IP = &interp.programAry[interp.thirdOct];       // loop back to location
			}
			break;
		case '6':   interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);     // array index
			interp.thirdOct = convertToInt(myString, 8, 10);
			index = interp.dataAry[interp.thirdOct];         //getting next available array element
			interp.dataAry[index] = interp.dataAry[interp.firstOct]; // moving temp into array
			break;
		case '7':  interp.firstOct = convertToInt(myString, 2, 10);  // special case for converting a 9-digit number
			if (interp.dataAry[777] == 0) {
				interp.dataAry[777] = interp.firstOct;
			}
			else{
				interp.dataAry[778] = interp.firstOct;
			}
			break;
		case '8':  	interp.firstOct = convertToInt(myString, 2, 4);
			interp.secOct = convertToInt(myString, 5, 7);     // array index
			interp.thirdOct = convertToInt(myString, 8, 10);
			interp.dataAry[interp.thirdOct] = interp.dataAry[interp.thirdOct];  // move data into temp location
			cout << interp.dataAry[interp.firstOct] << endl;
			break;
		default:    interp.endOfInitialData = true;  // +9 was encountered
			break;
		}
	}
}





void clearArrays() {
	for (int i = 0; i < 999; ++i) {
		interp.dataAry[i] = 0;
		interp.programAry[i] = "";
	}
}




void looper() {
	int start = interp.dataAry[interp.firstOct];
	int end = interp.dataAry[4];

	for (int i = start; i <= end; ++i) {
		while (interp.sevenCounter == 0) {
			interp.instruction = *interp.IP;         // read instruction
			++interp.IP;
			checkOpcode(interp.instruction);         // select which opcode instruction to use
		}
		interp.sevenCounter = 0;
	}
	interp.IP = interp.restore; // leaving +7 loop, restore to location where we left off
	interp.looperRunning = false;
	interp.sevenCounter = 0;
}



int main()
{
	ifstream myFile;
	string line = "";
	int executeLines = 0;
	int initCounter = 0;  //counts how many initialization variables there are
	int lineCounter = 0;

	clearArrays(); //initializing data array before interpreter starts
	myFile.open("data.txt");
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			if (line[1] == '9') {  // Flag that marks the end of a section of code
				interp.endOfInitialData = true;
				++interp.foundNine;
			}
			if (interp.endOfInitialData == true && interp.foundNine == 1 && line[1] != '9') {  // begin counting actual execution code
				interp.programAry[executeLines] = line;
				++executeLines;
			}
			if (interp.endOfInitialData == true && interp.foundNine == 2) {  // checking for flag marking beginning of Input Data
				if (line[1] != '9') {
					checkOpcode(line);
				}
			}
			if (interp.endOfInitialData == false && interp.foundNine == 0) {  // counts number of initial variables
				++initCounter;
				checkOpcode(line);
			}
			line = "";       // reset
			++lineCounter;
		}
	}

	// The machine instructions have been read-in.  Now start interpreting

	interp.IP = interp.programAry;
	for (int i = 0; i < executeLines; ++i) {
		interp.instruction = *interp.IP;         // read instruction
		if (interp.instruction == "") {         // end of program has been reached
			break;
		}
		if (interp.instruction.find('+7') != std::string::npos) {   // loop is about to start, save location to come back to after looping
			interp.restore = interp.IP + 1;                        // cite for 'find': http://www.cplusplus.com/reference/string/string/find/  
		}
		++interp.IP;
		checkOpcode(interp.instruction);         // select which opcode instruction to use
	}

	myFile.close();
	return 0;
}

