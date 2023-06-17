/***********************************************************************
 * File: Game.cpp
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--05-17
 * Editor: KUAN-TE CHENG (B11132007), Tone, Raymin
 * Update Date: 2023--05-17
 * Description: code of Game class
***********************************************************************/
#pragma once
#include "Game.h"

/**
  * Intent : copy board
  * Pre : two board
  * Post : none
 */
void copyGameBoard(char a[9][9], char b[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}

// Intent: initialize the game
// Pre: none
// Post: the board and the chess are set to the original version
void Game::initialGame() {
	gBoard[0][0] = ' ';

	// show x coordinates
	for (int i = 1; i < BOARDSIZE; i++) {
		gBoard[0][i] = char(i + '0');
	}

	// show y coordinates
	for (int i = 1; i < BOARDSIZE; i++) {
		gBoard[i][0] = char(i + '0');
	}

	// set black pawns
	for (int i = 1; i < BOARDSIZE; i++) {
		gBoard[2][i] = 'P';
	}

	// set white pawns
	for (int i = 1; i < BOARDSIZE; i++) {
		gBoard[7][i] = 'p';
	}

	// set left black chess
	gBoard[1][1] = 'R'; gBoard[1][8] = 'R';
	gBoard[1][2] = 'N'; gBoard[1][7] = 'N';
	gBoard[1][3] = 'B'; gBoard[1][6] = 'B';
	gBoard[1][4] = 'Q'; gBoard[1][5] = 'K';

	// set left white chess
	gBoard[8][1] = 'r'; gBoard[8][8] = 'r';
	gBoard[8][2] = 'n'; gBoard[8][7] = 'n';
	gBoard[8][3] = 'b'; gBoard[8][6] = 'b';
	gBoard[8][4] = 'q'; gBoard[8][5] = 'k';

	// initialize varialbes about chess of two players
	playerWhite.WinitialChess();
	playerBlack.BinitialChess();
	update();
	newRecord();
}

// Intent: check the start position is valid
// Pre: pos.x and pos.y should be between 1 to 8
// Post: return if start position is valid
bool Game::isStartValid(const Position& pos) {
	if (pos.x < 0 || pos.x > 8 || pos.y < 0 || pos.y > 8) return false;

	if (gBoard[pos.y][pos.x] == ' ') return false;

	// find the chess we choose
	Chess chess;
	if (turns % 2 == 1) { // white turn
		if (!(gBoard[pos.y][pos.x] < 'z' && gBoard[pos.y][pos.x] > 'a')) {
			return false;
		}
		chess = playerWhite.findChess(pos);
	}
	else { // black turn
		if (!(gBoard[pos.y][pos.x] < 'Z' && gBoard[pos.y][pos.x] > 'A')) return false;
		chess = playerBlack.findChess(pos);
	}

	if (chess.getIsAlive() == false) {
		return false;
	}
	if (chess.getValidMove().empty()) {
		return false;
	}
	return true;
}

// Intent: check the end position is valid
// Pre: pos.x and pos.y should be between 1 to 8
// Post: return if end position is valid
bool Game::isEndValid(const Position& start, const Position& end) {
	if (end.x < 0 || end.x > 8 || end.y < 0 || end.y > 8) return false;
	// find the chess we choose first
	Chess chess;
	if (turns % 2 == 1) {
		chess = playerWhite.findChess(start);
	}
	else {
		chess = playerBlack.findChess(start);
	}

	// check valid move
	std::vector<Position> path;
	path = chess.getValidMove();
	for (int i = 0; i < path.size(); i++) {
		if (path[i] == end) {
			return true;
		}
	}

	return false;
}

// Intent: move the chess
// Pre: the start and end position must be verified
// Post: the chosen chess was moved to the end position
void Game::move(const Position& start, const Position& end) {
	if (turns % 2 == 1) { // white

		playerWhite.moveChess(start, end);
		if (gBoard[end.y][end.x] != ' ') { // check if chess kill the enemy
			lastChangeTurn = turns;
			playerBlack.ChessDie(end);
		}

		//check if can do passant
		resetAllMoveTwoW();
		if (gBoard[start.y][start.x] == 'p')
		{
			whiteDoPassant(start, end);
			whiteMoveTwo(start, end);
		}
	}
	else { // black
		playerBlack.moveChess(start, end);
		if (gBoard[end.y][end.x] != ' ') {  // check if chess kill the enemy
			lastChangeTurn = turns;
			playerWhite.ChessDie(end);
		}

		//check if can do passant
		resetAllMoveTwoB();
		if (gBoard[start.y][start.x] == 'P')
		{
			blackDoPassant(start, end);
			blackMoveTwo(start, end);
		}
	}
}

// Intent: update the game information about board and chess
// Pre: none
// Post: board and chess are updated
void Game::update() {
	// reset the board
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			gBoard[i][j] = ' ';
		}
	}
	// update board first time
	playerBlack.updateBoard();
	playerWhite.updateBoard();

	// update chess and check if there are some exception problem
	playerBlack.updateChess();
	playerWhite.updateChess();
	whiteUpdatePassant();
	blackUpdatePassant();
	whiteUpdateCastling();
	blackUpdateCastling();

	// final update board
	playerBlack.updateBoard();
	playerWhite.updateBoard();
}

// Intent: check if game is over 
// Pre: none
// Post: if game is over return true, other wise return false
bool Game::gameover() {
	if (turns - lastChangeTurn > 100) { // check draw
		std::cout << "Draw!" << endl;
		return true;
	}

	// check someone surrender
	if (playerWhite.getSurrender()) {
		std::cout << "White Lose!" << endl;
		return true;
	}
	if (playerBlack.getSurrender()) {
		std::cout << "Black Lose!" << endl;
		return true;
	}

	// check if checkmate or draw happened
	bool whiteLose = false, blackLose = false;
	bool whiteCantGo = true, blackCantGo = true;
	if (playerWhite.canMove())whiteCantGo = false;
	if (playerBlack.canMove())blackCantGo = false;
	if (whiteCantGo)
	{
		if (playerWhite.getCheck())
		{
			whiteLose = true;
		}
		else
		{
			std::cout << "Draw!" << endl;
			return true;
		}
	}
	if (blackCantGo)
	{
		if (playerBlack.getCheck())
		{
			blackLose = true;
		}
		else
		{
			std::cout << "Draw!" << endl;
			return true;
		}
	}

	// print who lose
	if (whiteLose) {
		std::cout << "White Lose!" << endl;
		return true;
	}
	if (blackLose) {
		std::cout << "Black Lose!" << endl;
		return true;
	}

	return false;
}

// Intent: print the board and show the path
void Game::printPathBoard(const Position& pos) {

	// Fetch: getValidMove()
	vector<Position> location;

	// Turn check
	if (getTurns() % 2 == 0) {
		location = this->playerBlack.findChess(pos).getValidMove();
	}
	else {
		location = this->playerWhite.findChess(pos).getValidMove();
	}

	// console adjust
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// path adjust
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			// Default color Selection
			if (this->search(location, Position(j, i))) {
				if (i == 0 && j == 0) {
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (i == 0 || j == 0) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else if ((i + j) % 2 == 0) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);
				}
				else {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				}
			}
			else {
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
			}

			if (this->search(location, Position(j, i)) && gBoard[i][j] == ' ') { cout << " " << 'X' << " "; }
			else {
				char out = gBoard[i][j];
				if (isupper(out)) {
					out = tolower(out);
				}
				else {
					out = toupper(out);
				}
				cout << " " << out << " ";
			}

			// Get back to default color(non-color)
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl;
	}
}

// Intent: search the path position and pair with the board
// Pre: none
// Post: if pair return true
bool Game::search(const vector<Position>& location, const Position& pos) {
	for (int i = 0; i < location.size(); i++) {
		if (location[i].x == pos.x && location[i].y == pos.y) { return true; }
	}
	return false;
}

/**
  * Intent : undo
  * Pre : none
  * Post : none
 */
void Game::undo()
{
	if (turns - 2 >= 0)
	{
		turns -= 2;
		setData(turns);
	}
}

/**
  * Intent : redo
  * Pre : none
  * Post : none
 */
void Game::redo()
{
	if (turns <= record.size())
	{
		setData(turns);
	}
}

/**
  * Intent : set data to Tth turns
  * Pre : int T
  * Post : none
 */
void Game::setData(int T)
{
	playerWhite = record[T].playerWhite_;
	playerBlack = record[T].playerBlack_;
	copyGameBoard(gBoard, record[T].gboard_);
	lastChangeTurn = record[T].lastChangeTurn_;
}

/**
  * Intent : push new record
  * Pre : none
  * Post : none
 */
void Game::newRecord()
{
	//copy
	gameData newData;
	newData.playerWhite_ = playerWhite;
	newData.playerBlack_ = playerBlack;
	copyGameBoard(newData.gboard_, gBoard);
	newData.lastChangeTurn_ = lastChangeTurn;

	//inspect size and delete extra data
	if (record.size() > turns)
	{
		for (int i = turns; i <= record.size(); i++)
		{
			record.pop_back();
		}
	}

	//push
	record.push_back(newData);
}

/**
  * Intent : when white pawn is doing passant, we make that black pawn dead
  * Pre : start and end Position
  * Post : none
 */
void Game::whiteDoPassant(const Position& start, const Position& end)
{
	if (gBoard[end.y][end.x] == ' ') {
		if (start.x != end.x)
		{
			Position p = { end.x,end.y + 1 };
			playerBlack.ChessDie(p);
		}
	}
}
/**
  * Intent : when black pawn is doing passant, we make that white pawn dead
  * Pre : start and end Position
  * Post : none
 */
void Game::blackDoPassant(const Position& start, const Position& end)
{
	if (gBoard[end.y][end.x] == ' ') {
		if (start.x != end.x)
		{
			Position p = { end.x,end.y - 1 };
			playerWhite.ChessDie(p);
		}
	}
}

/**
  * Intent : if white pawn move two, we set its moveTwo as true
  * Pre : start and end Position
  * Post : none
 */
void Game::whiteMoveTwo(const Position& start, const Position& end)
{
	if (start.y - end.y == 2)
	{
		playerWhite.findChess(end).setMoveTwo(1);
	}
}
/**
  * Intent : if black pawn move two, we set its moveTwo as true
  * Pre : start and end Position
  * Post : none
 */
void Game::blackMoveTwo(const Position& start, const Position& end)
{
	if (end.y - start.y == 2)
	{
		playerBlack.findChess(end).setMoveTwo(1);
	}
}

/**
  * Intent : reset moveTwo with all white chess
  * Pre : none
  * Post : none
 */
void Game::resetAllMoveTwoW()
{
	for (int i = 0; i < 16; i++) {
		Chess* chess = playerWhite.getChess();
		chess[i].setMoveTwo(0);
	}
}

/**
  * Intent : reset moveTwo with all black chess
  * Pre : none
  * Post : none
 */
void Game::resetAllMoveTwoB()
{
	for (int i = 0; i < 16; i++) {
		Chess* chess = playerBlack.getChess();
		chess[i].setMoveTwo(0);
	}
}

/**
  * Intent : update validMove for check
  * Pre : none
  * Post : none
 */
void Game::updateForCheck()
{
	//reduce validMove's member which would let player checked

	if (turns % 2 == 0) // next turn is white
	{
		Player copyPlayerWhite = playerWhite, copyPlayerBlack = playerBlack;
		char copyBoard[9][9];
		copyGameBoard(copyBoard, gBoard);
		Chess* chess = playerWhite.getChess();

		//run all chess
		for (int i = 0; i < 16; i++)
		{
			if (!chess[i].getIsAlive())continue;
			vector<Position> pre = chess[i].getValidMove();
			vector<Position> v;

			//simulating the move
			//if it would make player himself check,
			//we delete this move from valid move
			for (auto u : pre)
			{
				Position start = chess[i].getPos(), end = u;
				turns++;
				move(start, end);
				update();
				refreshCheck();
				if (!playerWhite.getCheck())v.push_back(end);
				playerWhite = copyPlayerWhite;
				playerBlack = copyPlayerBlack;
				copyGameBoard(gBoard, copyBoard);
				turns--;
			}
			copyPlayerWhite.getChess()[i].setValidMove(v);
		}
		playerWhite = copyPlayerWhite;
	}
	else //next turn is black
	{
		Player copyPlayerWhite = playerWhite, copyPlayerBlack = playerBlack;
		char copyBoard[9][9];
		copyGameBoard(copyBoard, gBoard);
		Chess* chess = playerBlack.getChess();

		//run all chess
		for (int i = 0; i < 16; i++)
		{
			if (!chess[i].getIsAlive())continue;
			vector<Position> pre = chess[i].getValidMove();
			vector<Position> v;

			//simulating the move
			//if it would make player himself check,
			//we delete this move from valid move
			for (auto u : pre)
			{
				Position start = chess[i].getPos(), end = u;
				turns++;
				move(start, end);
				update();
				refreshCheck();
				if (!playerBlack.getCheck())v.push_back(end);
				playerBlack = copyPlayerBlack;
				playerWhite = copyPlayerWhite;
				copyGameBoard(gBoard, copyBoard);
				turns--;
			}
			copyPlayerBlack.getChess()[i].setValidMove(v);
		}
		playerBlack = copyPlayerBlack;
	}
}

/**
  * Intent : refresh player's check value
  * Pre : none
  * Post : none
 */
void Game::refreshCheck()
{
	//white
	Chess* chess;
	chess = playerBlack.getChess();
	playerWhite.setCheck(false);
	//when enemy can attack king
	//check is true
	for (int i = 0; i < 16; i++)
	{
		if (!chess[i].getIsAlive())continue;
		vector<Position> v = chess[i].getValidMove();
		for (auto u : v)
		{
			if (gBoard[u.y][u.x] == 'k') playerWhite.setCheck(true);
		}
	}

	//black
	chess = playerWhite.getChess();
	playerBlack.setCheck(false);
	//when enemy can attack king
	//check is true
	for (int i = 0; i < 16; i++)
	{
		if (!chess[i].getIsAlive())continue;
		vector<Position> v = chess[i].getValidMove();
		for (auto u : v)
		{
			if (gBoard[u.y][u.x] == 'K') playerBlack.setCheck(true);
		}
	}
}

/**
  * Intent : update validMove for white passant
  * Pre : none
  * Post : none
 */
void Game::whiteUpdatePassant()
{
	Chess* chess = playerWhite.getChess();
	for (int i = 0; i < 16; i++)
	{

		if (chess[i].getType() == Type::pawn)
		{
			Position p = chess[i].getPos();
			Position left = { p.x - 1,p.y }, right = { p.x + 1,p.y };
			if (gBoard[left.y][left.x] == 'P')
			{
				Chess temp = playerBlack.findChess(left);

				if (temp.getMoveTwo())
				{
					Position upleft = { p.x - 1,p.y - 1 };
					chess[i].getValidMove().push_back(upleft);
				}
			}
			if (gBoard[right.y][right.x] == 'P')
			{
				Chess temp = playerBlack.findChess(right);
				if (temp.getMoveTwo())
				{
					Position upright = { p.x + 1,p.y - 1 };
					chess[i].getValidMove().push_back(upright);
				}
			}
		}
	}
}
/**
  * Intent : update validMove for black passant
  * Pre : none
  * Post : none
 */
void Game::blackUpdatePassant()
{
	Chess* chess = playerBlack.getChess();
	for (int i = 0; i < 16; i++)
	{

		if (chess[i].getType() == Type::pawn)
		{
			Position p = chess[i].getPos();
			Position left = { p.x - 1,p.y }, right = { p.x + 1,p.y };
			if (gBoard[left.y][left.x] == 'p')
			{
				Chess temp = playerWhite.findChess(left);

				if (temp.getMoveTwo())
				{
					Position upleft = { p.x - 1,p.y + 1 };
					chess[i].getValidMove().push_back(upleft);
				}
			}
			if (gBoard[right.y][right.x] == 'p')
			{
				Chess temp = playerWhite.findChess(right);

				if (temp.getMoveTwo())
				{
					Position upright = { p.x + 1,p.y + 1 };
					chess[i].getValidMove().push_back(upright);
				}
			}
		}
	}
}

// Intent: white surrender
// Pre: none
// Post: white is surrendered
void Game::whiteSurrender() {
	playerWhite.setSurrender();
}

// Intent: black surrender
// Pre: none
// Post: black is surrendered
void Game::blackSurrender() {
	playerBlack.setSurrender();
}

/**
  * Intent : update validMove for white castling
  * Pre : none
  * Post : none
 */
void Game::whiteUpdateCastling()
{
	Chess* chess = playerWhite.getChess();
	for (int i = 0; i < 16; i++)
	{
		//if satisty castling's condition
		if (chess[i].getType() == Type::king && chess[i].getNeverMove())
		{
			Position p = chess[i].getPos();
			bool noBarrierLeft = 1, noBarrierRight = 1;

			//test left side
			for (int j = 1; j < 5; j++)
			{
				if (noBarrierLeft)
				{
					if (gBoard[p.y][p.x - j] == ' ')
					{
						continue;
					}
					else if (gBoard[p.y][p.x - j] == 'r')
					{
						if (playerWhite.findChess({ p.x - j,p.y }).getNeverMove())
						{
							chess[i].getValidMove().push_back({ p.x - j,p.y });
						}
						break;
					}
					else
					{
						noBarrierLeft = 0;
					}
				}
				else
				{
					break;
				}
			}

			//test right side
			for (int j = 1; j < 5; j++)
			{
				if (noBarrierRight)
				{
					if (gBoard[p.y][p.x + j] == ' ')
					{
						continue;
					}
					else if (gBoard[p.y][p.x + j] == 'r')
					{
						if (playerWhite.findChess({ p.x + j,p.y }).getNeverMove())
						{
							chess[i].getValidMove().push_back({ p.x + j,p.y });
						}
						break;
					}
					else
					{
						noBarrierRight = 0;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
}
/**
  * Intent : update validMove for black castling
  * Pre : none
  * Post : none
 */
void Game::blackUpdateCastling()
{
	Chess* chess = playerBlack.getChess();
	for (int i = 0; i < 16; i++)
	{
		//if satisty castling's condition
		if (chess[i].getType() == Type::king && chess[i].getNeverMove())
		{
			Position p = chess[i].getPos();
			bool noBarrierLeft = 1, noBarrierRight = 1;

			//test left side
			for (int j = 1; j < 5; j++)
			{
				if (noBarrierLeft)
				{
					if (gBoard[p.y][p.x - j] == ' ')
					{
						continue;
					}
					else if (gBoard[p.y][p.x - j] == 'R')
					{
						if (playerBlack.findChess({ p.x - j,p.y }).getNeverMove())
						{
							chess[i].getValidMove().push_back({ p.x - j,p.y });
						}
						break;
					}
					else
					{
						noBarrierLeft = 0;
					}
				}
				else
				{
					break;
				}
			}

			//test right side
			for (int j = 1; j < 5; j++)
			{
				if (noBarrierRight)
				{
					if (gBoard[p.y][p.x + j] == ' ')
					{
						continue;
					}
					else if (gBoard[p.y][p.x + j] == 'R')
					{
						if (playerBlack.findChess({ p.x + j,p.y }).getNeverMove())
						{
							chess[i].getValidMove().push_back({ p.x + j,p.y });
						}
						break;
					}
					else
					{
						noBarrierRight = 0;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
}

// For FEN (unfinished)
bool isWhiteIcon(char c) {
	if (c == 'p' || c == 'k' || c == 'q' || c == 'b' || c == 'n' || c == 'r') return true;
	else return false;

}

// For FEN (unfinished)
bool isBlackIcon(char c) {
	if (c == 'P' || c == 'K' || c == 'Q' || c == 'B' || c == 'N' || c == 'R') return true;
	else return false;

}

// For FEN (unfinished)
void Game::readFEN(ifstream& file) {
	std::string fen;
	Chess present;

	if (std::getline(file, fen))
	{
		std::stringstream ss(fen);
		std::string boardSub, activePlayer, castlingRights, enPassantSquare, halfMoveClock, fullMoveNumber;

		// Reset the board
		for (int i = 1; i < BOARDSIZE; i++) {
			for (int j = 1; j < BOARDSIZE; j++) {
				gBoard[i][j] = ' ';
			}
		}

		// Parse the FEN string
		if (getline(ss, boardSub, ' '))
		{
			int row = 1;
			int col = 0;
			int wCount = 0;
			int bCount = 0;
			for (char c : boardSub) {
				if (c == '/') {
					row++;
					col = 0;
				}
				else if (isdigit(c)) {
					int numEmptySquares = c - '0';
					for (int i = 0; i < numEmptySquares; i++) {
						gBoard[row][col] = ' ';
						col++;
					}
				}
				else {
					gBoard[row][col] = c;

					if (isWhiteIcon(c)) {
						present = playerWhite.setChessGroup(wCount);
						present.setXY(row, col);
						present.setIsAlive(1);
						wCount++;
					}
					else if (isBlackIcon(c)) {
						present = playerBlack.setChessGroup(bCount);
						present.setXY(row, col);
						present.setIsAlive(1);
						bCount++;
					}

					col++;
				}

				if (col >= BOARDSIZE) {
					break;
				}
			}
		}

		// Parse the remaining FEN components
		if (getline(ss, activePlayer, ' '))
		{
			if (activePlayer == "w") {
				turns = 0;
			}
			if (activePlayer == "b") {
				turns = 1;
			}
		}

		if (getline(ss, castlingRights, ' '))
		{
			// Process castlingRights (castling availability)
			for (char c : castlingRights) {
				if (c == 'K') {
					present = playerBlack.findByIcon(c);
					present.setNeverMove(1);
				}
				else if (c == 'k') {
					present = playerWhite.findByIcon(c);
					present.setNeverMove(1);
				}
				else if (c == 'Q') {
					present = playerBlack.findByIcon(c);
					present.setNeverMove(1);
				}
				else if (c == 'q') {
					present = playerWhite.findByIcon(c);
					present.setNeverMove(1);
				}
				else {
					continue;
				}
			}
		}

		if (getline(ss, enPassantSquare, ' '))
		{
			// Process enPassantSquare (en passant target square)
			// ...
		}

		if (getline(ss, halfMoveClock, ' '))
		{
			// Process halfMoveClock (half move clock)
			// ...
		}

		if (getline(ss, fullMoveNumber, ' '))
		{
			if (turns == 1 && stoi(fullMoveNumber) % 2 == 1) {
				turns = stoi(fullMoveNumber);
			}
			else if (turns == 0 && stoi(fullMoveNumber) % 2 == 0) {
				turns = stoi(fullMoveNumber);
			}
		}
	}
}

// Unfinished
void Game::boardFEN() {
	std::string outputFile = "board.txt";
	std::ofstream file;
	file.open(outputFile); // 指定輸出的檔案名稱

	if (!file.is_open()) { cout << "無法開啟輸出檔案。" << std::endl; return; }
	std::cout << "盤面已成功輸出到 chess_board.txt 檔案中。" << std::endl;

	for (int row = 8; row >= 1; row--) {
		string result = "";
		int blank = 0;
		for (int col = 1; col <= 8; col++) {
			char piece = gBoard[row][col];

			if (piece == ' ') {
				blank++;
				if (col == 8) { result += to_string(blank); }
			}
			else if (piece != ' ' && blank != 0) {
				result = result + to_string(blank) + piece;
				blank = 0;
			}
			else {
				result += piece;
			}
		}

		if (row != 1) { file << result << "/"; }
		else { file << result; }
	}

	file.close();
}

/**
  * Intent : get record size
  * Pre : none
  * Post : int
 */
int Game::getRecordSize() {
	return record.size();
}
