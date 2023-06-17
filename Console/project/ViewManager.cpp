#include "ViewManager.h"

// Intent: print the board on the console
// Pre: none
// Post: the board is shown on the console
void ViewManager::printBoard() const {
	// console adjust
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// select color
			if (i == 0 && j == 0) {
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (i == 0 || j == 0) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			else if ((i + j) % 2 == 0) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN);
			}
			else {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			}

			// print
			char out = gBoard[i][j];
			if (isupper(out)) {
				out = tolower(out);
			}
			else {
				out = toupper(out);
			}
			cout << " " << out << " ";
		}
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
	}
}
