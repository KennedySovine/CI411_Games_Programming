// CI411_Week7.cpp
// Kennedy Sovine UoB
//

#include <iostream>
using namespace std;

//Functions

//WorkShop Tasks
void displayDaysOfWeek();
void displayPlayArea();

//Further Work
void createBoard();
void displayBoard();
void randomObjectsOnBoard();

//Global
bool gameOver = false;

const int boardHeight = 10;
const int boardWidth = 10;
char gameBoard[boardHeight][boardWidth];

int main() {

	cout << "====Days of the Week====" << endl;
	displayDaysOfWeek();
	cout << "\n";

	cout << "====Play Area====" << endl;
	displayPlayArea();
	cout << "\n";

	cout << "====Game Board====" << endl;
	createBoard();
	randomObjectsOnBoard();
	displayBoard();

	//Start Screen
	//Set Up
	//Main Loop
	//End Screen

	return 0;
}


//Functions
void displayDaysOfWeek() {
	string days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	for (int i = 1; i <= 7; i++) {
		cout << "Day " << i << " : " << days[i - 1] << endl;
	}
}

void displayPlayArea() {

	//Make play area
	char playArea[8][8] = { {'=','=','=','=','=','=','=', '='},
						{'|','-','-','-','-','-','-','|'},
						{'|','-','-','-','-','-','-','|'},
						{'|','-','-','-','-','-','-','|'},
						{'|','-','-','-','-','-','-','|'},
						{'|','-','-','-','-','-','-','|'},
						{'|','-','-','-','-','-','-','|'},
						{'=','=','=','=','=','=','=','='}};

	//Random Populace
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {

		int row = (rand() % (6) + 1);
		int col = (rand() % (6)) + 1;

		playArea[row][col] = '*';
	}


	//Display play area

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			cout << playArea[row][col];
			cout << " ";
		}
		cout << "\n";
	}
}

void createBoard() {
	for (int row = 0; row < boardHeight; row++) {
		for (int col = 0; col < boardWidth; col++) {

			if (row == 0 || row == boardHeight - 1) {
				gameBoard[row][col] = '=';
			}
			else {
				if (col == 0 || col == boardWidth - 1) {
					gameBoard[row][col] = '|';
				}
				else {
					gameBoard[row][col] = '-';
				}
			}
		}
	}
}

void displayBoard() {

	for (int row = 0; row < boardHeight; row++) {
		for (int col = 0; col < boardWidth; col++) {
			cout << gameBoard[row][col];
			cout << " ";
		}
		cout << "\n";
	}

}

void randomObjectsOnBoard() {

	char randObjects[5] = { 'A', 'M', 'G', 'E', 'L' };
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {

		int row = (rand() % (boardHeight - 2) + 1);
		int col = (rand() % (boardWidth - 2)) + 1;

		if (gameBoard[row][col] != '-') {
			i--;
		}
		else {
			gameBoard[row][col] = randObjects[i];
		}
	}
}