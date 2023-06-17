/***********************************************************************
 * File: main.cpp
 * Author: Tone (B11132013), Raymin (B11132009)
 * Create date: 2023/05/08
 * Editor: Raymin (B11132009)
 * Update Date: 2023/05/17
 * Description: Chess main for window call
 * ***********************************************************************/

#include <windows.h>
#include "Variables.h"
#include "SoundPlay.h"
#include "menu.h"
#include "BoardWindow.h"
using namespace std;

const int BOARDSIZE = 9;
int whoFirst = 0;

// Initialize the board
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

int main(int argc, char* argv[]) {
	// Sound
	playSound();

	// Window
	QApplication chess(argc, argv);
	Menu window;
	window.setWindowTitle("Chess Game");
	window.show();
	return chess.exec();
}