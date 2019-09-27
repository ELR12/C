

/*
Created by
Ethan Roberts
on 8/02/2016

This is a game of TIC-TAC-TOE

*/



#include "stdafx.h"  // mandatory for Visual Studio
#include <iostream>
#include <string>
using namespace std;

const int ROWSIZE = 3;
const int COLSIZE = 3;

void showBeginningBoard(char[][COLSIZE]);
void displayBoard(char[][COLSIZE]);
void getMoveX(int, int, char[][COLSIZE]);
void getMoveO(int, int, char[][COLSIZE]);
bool checkGameOverX(char[][COLSIZE]);
bool checkGameOverO(char[][COLSIZE]);

int main()
{
	int getRow = 0;
	int getCol = 0;
	char player1;
	char gameAry[3][3];
	bool keepPlayingX = true;
	bool keepPlayingO = true;
	bool OneisX = false;


	cout << "Player 1, do you want to be X's or O's?\n";
	cin >> player1;
	player1 = tolower(player1);
	while (player1 != 'o' && player1 != 'x') {
		cout << "Invalid symbol choice, you must choose an X or an O.\n";
		cin >> player1;
	}

	if (player1 == 'x') {
		OneisX = true;
	}

	cout << "\n";
	showBeginningBoard(gameAry);

	while (keepPlayingX && keepPlayingO) {
		if (OneisX)  // if player is x, iterate while loop in the following order
		{
			if (keepPlayingO)
			{
				getMoveX(getRow, getCol, gameAry);
				keepPlayingX = checkGameOverX(gameAry);
				cout << "\n";
				displayBoard(gameAry);
			}

			if (keepPlayingX)
			{
				getMoveO(getRow, getCol, gameAry);
				keepPlayingO = checkGameOverO(gameAry);
				cout << "\n";
				displayBoard(gameAry);
			}

		}
		else  // if player chose o, iterate while loop in this order
		{
			if (keepPlayingX)
			{
				getMoveO(getRow, getCol, gameAry);
				keepPlayingO = checkGameOverO(gameAry);
				cout << "\n";
				displayBoard(gameAry);
			}

			if (keepPlayingO)
			{
				getMoveX(getRow, getCol, gameAry);
				keepPlayingX = checkGameOverX(gameAry);
				cout << "\n";
				displayBoard(gameAry);
			}
		}

	}


	if (!keepPlayingX) {
		cout << "\nPlayer X WINS -- ";
	}
	else {
		cout << "\nPlayer O WINS -- ";
	}

	cout << "Flawless Victory!\n\n";


	return 0;
}




void showBeginningBoard(char ary[][COLSIZE])
{
	int r = 0;
	int c = 0;

	for (r = 0; r < ROWSIZE; r++)
	{
		for (c = 0; c < COLSIZE; c++)
		{
			ary[r][c] = '*';
			cout << "   " << ary[r][c];
		}

		cout << "\n\n";
	}
}



void displayBoard(char ary[][COLSIZE])
{
	int r = 0;
	int c = 0;

	for (r = 0; r < ROWSIZE; r++)
	{
		for (c = 0; c < COLSIZE; c++)
		{
			cout << "   " << ary[r][c];
		}

		cout << "\n\n";
	}
}




void getMoveX(int row, int col, char ary[][COLSIZE])
{
	cout << "\n";
	cout << "Player X, your turn. Enter the row you want: ";
	cin >> row;
	while (row > 3 || row < 1)
	{
		cout << "Invalid entry, re-enter the row. (1 - 3) \n";
		cin >> row;
	}
	cout << "Now enter the column: ";
	cin >> col;

	while (col > 3 || col < 1)
	{
		cout << "Invalid entry, re-enter the column. (1 - 3) \n";
		cin >> col;
	}

	ary[row - 1][col - 1] = 'x';
}




void getMoveO(int row, int col, char ary[][COLSIZE])
{
	cout << "\n";
	cout << "Player O, your turn. Enter the row you want: ";
	cin >> row;

	while (row > 3 || row < 1)
	{
		cout << "Invalid entry, re-enter the row. (1 - 3) \n";
		cin >> row;
	}
	cout << "Now enter the column: ";
	cin >> col;

	while (col > 3 || col < 1)
	{
		cout << "Invalid entry, re-enter the column. (1 - 3) \n";
		cin >> col;
	}

	ary[row - 1][col - 1] = 'o';
}




bool checkGameOverX(char ary[ROWSIZE][COLSIZE])
{
	int r = 0;
	int c = 0;
	int counter = 0;

	if (ary[0][0] == 'x' && ary[1][0] == 'x' && ary[2][0] == 'x') {
		return false;
	}
	else if (ary[0][0] == 'x' && ary[0][1] == 'x' && ary[0][2] == 'x') {
		return false;
	}
	else if (ary[2][0] == 'x' && ary[2][1] == 'x' && ary[2][2] == 'x') {
		return false;
	}
	else if (ary[0][2] == 'x' && ary[1][2] == 'x' && ary[2][2] == 'x') {
		return false;
	}
	else if (ary[0][0] == 'x' && ary[1][1] == 'x' && ary[2][2] == 'x') {
		return false;
	}
	else if (ary[0][2] == 'x' && ary[1][1] == 'x' && ary[2][0] == 'x') {
		return false;
	}
	else if (ary[0][1] == 'x' && ary[1][1] == 'x' && ary[2][1] == 'x') {
		return false;
	}
	else {
		return true;  // keep playing
	}

}




bool checkGameOverO(char ary[ROWSIZE][COLSIZE])
{
	int r = 0;
	int c = 0;
	int counter = 0;

	if (ary[0][0] == 'o' && ary[1][0] == 'o' && ary[2][0] == 'o') {
		return false;
	}
	else if (ary[0][0] == 'o' && ary[0][1] == 'o' && ary[0][2] == 'o') {
		return false;
	}
	else if (ary[2][0] == 'o' && ary[2][1] == 'o' && ary[2][2] == 'o') {
		return false;
	}
	else if (ary[0][2] == 'o' && ary[1][2] == 'o' && ary[2][2] == 'o') {
		return false;
	}
	else if (ary[0][0] == 'o' && ary[1][1] == 'o' && ary[2][2] == 'o') {
		return false;
	}
	else if (ary[0][2] == 'o' && ary[1][1] == 'o' && ary[2][0] == 'o') {
		return false;
	}
	else if (ary[0][1] == 'o' && ary[1][1] == 'o' && ary[2][1] == 'o') {
		return false;
	}
	else {
		return true;  // keep playing
	}

}

