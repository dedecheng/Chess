/***********************************************************************
 * File: main.cpp
 * Author: Tone, Raymin, dede, yao
 * Create date: 2023/05/08
 * Editor: Tone, Raymin, dede, yao
 * Update Date: 2023/05/08
 * Description: main function in chess
 * ***********************************************************************/
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Game.h"
#include "Variables.h"
#include "SoundPlay.h"
using namespace std;

const double ROUNDTIME = 60; // a round should be 60 seconds
const int BOARDSIZE = 9;

char gBoard[BOARDSIZE][BOARDSIZE] = {
		{' ','1','2','3','4','5','6','7','8'},
		{'1','R','N','B','Q','K','B','N','R'},
		{'2','P','P','P','P','P','P','P','P'},
		{'3',' ',' ',' ',' ',' ',' ',' ',' '},
		{'4',' ',' ',' ',' ',' ',' ',' ',' '},
		{'5',' ',' ',' ',' ',' ',' ',' ',' '},
		{'6',' ',' ',' ',' ',' ',' ',' ',' '},
		{'7','p','p','p','p','p','p','p','p'},
		{'8','r','n','b','q','k','b','n','r'}
};

int main(int argc, char argv[]) {
	bool gKeyState[ValidInput::INVALID]; // boolean array to store the state of each keys

	// initialize
	for (int i = 0; i < ValidInput::INVALID; i++) {
		gKeyState[i] = false;
	}

	system("CLS");
	cout << "Welcome to the Cheese! :)\n";

	while (!gKeyState[ValidInput::EESC]) { // while not enter esc
		cout << "press (1) create a new game, (ESC) Exit: \n";

		char input = _getch();

		// Press to ESC
		if (input == 27) break;

		// Press to play game
		else if (input == '1') {

			// Initialize the game
			Game game;
			game.initialGame();

			// Play the music
			playSound();

			// Select which side first
			while (1) {
				cout << "press (1) for white first, press (2) for black first" << endl;
				char select = _getch();
				if (select == '1') { break; }
				else if (select == '2') { game.setTurns(); break; }
			}

			// main game loop
			while (1) {
				system("CLS");
				game.setTurns();

				if (game.getTurns() % 2 == 1) { // white turn
					cout << "its white turn now.\n";
					if (game.getPlayerWhiteCheck()) {
						cout << "you are checked, try to save your king.\n";
					}
				}
				else { // black turn
					cout << "its black turn now.\n";
					if (game.getPlayerBlackCheck()) {
						cout << "you are checked, try to save your king.\n";
					}
				}

				game.printBoard();
				cout << endl;

				bool undo = false, redo = false, surrender = false;

				// Mode select
				while (1) {
					cout << "press (1) for keep playing, press (2) for surrender, press (3) for undo, press (4) for redo:\n" << endl;
					char select = _getch();
					if (select == '1') { break; } // for keep playing
					else if (select == '2') { // for surrender
						surrender = true;
						if (game.getTurns() % 2 == 1) { // white turn
							game.whiteSurrender();
						}
						else { // black turn
							game.blackSurrender();
						}
						break;
					}
					else if (select == '3') { // for undo
						if (game.getTurns() < 2) {
							cout << "cannot undo\n";
						}
						else {
							undo = true;
							game.undo();
							break;
						}
					}
					else if (select == '4') { // for redo
						if (game.getTurns() >= game.getRecordSize()) {
							cout << "cannot redo\n";
						}
						else {
							redo = true;
							game.redo();
							break;
						}
					}
				}

				if (surrender) {
					game.gameover();
					break;
				}
				else if (undo || redo) { // if undo or redo skip this turn
					game.update(); // update chess and board
					game.refreshCheck();
					game.updateForCheck();// update for check
					continue;
				}

				bool runTime = false;
				bool posInvalid = false;
				clock_t startT = clock(), endT;

				Position start;
				// loop for choose chess to move
				while (1) {
					endT = clock();
					if (double(endT - startT) / CLOCKS_PER_SEC > ROUNDTIME) { // count time
						runTime = true;
						break;
					}

					system("CLS");
					if (game.getTurns() % 2 == 1) { // white turn and check if checked
						cout << "its white turn now.\n";
						if (game.getPlayerWhiteCheck()) {
							cout << "you are checked, try to save your king.\n";
						}
					}
					else { // black turn
						cout << "its black turn now.\n";
						if (game.getPlayerBlackCheck()) {
							cout << "you are checked, try to save your king.\n";
						}
					}

					game.printBoard();
					cout << endl;

					if (posInvalid) cout << "the chess is invalid\n";
					cout << "now you have " << (ROUNDTIME - double(endT - startT) / CLOCKS_PER_SEC) << " seconds to think.\n"
						<< "choose a chess to move(x, y)\n"
						<< "(both x and y should between 1 to 8): ";

					// get the coordinate
					string x, y;
					cin >> x >> y;
					if (x.size() == 1 && y.size() == 1) {
						start.x = x[0] - '0';
						start.y = y[0] - '0';
					}

					posInvalid = false;
					if (game.isStartValid(start)) break;
					else posInvalid = true;
				}

				if (runTime) continue;

				runTime = false;
				posInvalid = false;
				startT = clock();
				Position end;

				// loop for move chess to a position
				while (1) {
					endT = clock();
					if (double(endT - startT) / CLOCKS_PER_SEC > ROUNDTIME) {
						runTime = true;
						break;
					}

					system("CLS");
					game.printPathBoard(start);
					cout << endl;

					if (posInvalid) cout << "the position is invalid"; // check if last move is invalid and hint the user
					cout << "\nnow you have " << (ROUNDTIME - double(endT - startT) / CLOCKS_PER_SEC) << " seconds to think.\n"
						<< "where to move(x, y)\n"
						<< "(both x and y should between 1 to 8): ";

					string x, y;
					cin >> x >> y;
					if (x.size() == 1 && y.size() == 1) {
						end.x = x[0] - '0';
						end.y = y[0] - '0';
					}

					if (game.isEndValid(start, end)) break;
					else posInvalid = true;
				}

				if (runTime) continue;

				game.move(start, end);// move chess
				game.update(); // update chess and board
				game.refreshCheck();
				game.updateForCheck();// update for check

				//this need to be called after move
				game.newRecord();

				if (game.gameover()) break;
			}
		}
	}

	return 0;
}