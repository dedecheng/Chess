/***********************************************************************
 * File: Player.cpp
 * Author: Tone
 * Create date: 2023/05/17
 * Editor: Tone
 * Update Date: 2023/05/17
 * Description: code of Player class
 * ***********************************************************************/
#include "Player.h"

 // Return to Game class
bool Player::getSurrender() {
	return isSurrender;
}

// Set Player surrrender
void Player::setSurrender() {
	isSurrender = true;
}

// Intent: intialized white chess
// Pre: none
// Post: chess are initialized
void Player::WinitialChess() {
	for (int i = 0; i < 16; i++) {
		chess[i].setIsWhite(true);
		chess[i].setIsAlive(true);
	}

	// for pawns
	Position temp(1, 7);
	for (int i = 0; i < 8; i++) {
		chess[i].setType(Type::pawn);
		chess[i].setIcon('p');
		chess[i].setPos(temp);
		chess[i].setOriginPos(temp);
		temp.x++;
	}

	// for rooks
	chess[8].setPos(Position(1, 8));
	chess[9].setPos(Position(8, 8));
	chess[8].setOriginPos(Position(1, 8));
	chess[9].setOriginPos(Position(8, 8));
	for (int i = 8; i < 10; i++) {
		chess[i].setType(Type::rook);
		chess[i].setIcon('r');
	}

	// for knight
	chess[10].setPos(Position(2, 8));
	chess[11].setPos(Position(7, 8));
	chess[10].setOriginPos(Position(2, 8));
	chess[11].setOriginPos(Position(7, 8));
	for (int i = 10; i < 12; i++) {
		chess[i].setType(Type::knight);
		chess[i].setIcon('n');
	}

	// for bishop
	chess[12].setPos(Position(3, 8));
	chess[13].setPos(Position(6, 8));
	chess[12].setOriginPos(Position(3, 8));
	chess[13].setOriginPos(Position(6, 8));
	for (int i = 12; i < 14; i++) {
		chess[i].setType(Type::bishop);
		chess[i].setIcon('b');
	}
	 
	// for queen
	chess[14].setPos(Position(4, 8));
	chess[14].setOriginPos(Position(4, 8));
	chess[14].setType(Type::queen);
	chess[14].setIcon('q');

	// for king
	chess[15].setPos(Position(5, 8));
	chess[15].setOriginPos(Position(5, 8));
	chess[15].setType(Type::king);
	chess[15].setIcon('k');
}

// Intent: intialized black chess
// Pre: none
// Post: chess are initialized
void Player::BinitialChess() {
	for (int i = 0; i < 16; i++) {
		chess[i].setIsWhite(false);
		chess[i].setIsAlive(true);
	}

	// for pawns
	Position temp(1, 2);
	for (int i = 0; i < 8; i++) {
		chess[i].setType(Type::pawn);
		chess[i].setIcon('P');
		chess[i].setPos(temp);
		chess[i].setOriginPos(temp);
		temp.x++;
	}

	// for rooks
	chess[8].setPos(Position(1, 1));
	chess[9].setPos(Position(8, 1));
	chess[8].setOriginPos(Position(1, 1));
	chess[9].setOriginPos(Position(8, 1));
	for (int i = 8; i < 10; i++) {
		chess[i].setType(Type::rook);
		chess[i].setIcon('R');
	}

	// for knights
	chess[10].setPos(Position(2, 1));
	chess[11].setPos(Position(7, 1));
	chess[10].setOriginPos(Position(2, 1));
	chess[11].setOriginPos(Position(7, 1));
	for (int i = 10; i < 12; i++) {
		chess[i].setType(Type::knight);
		chess[i].setIcon('N');
	}

	// for bishops
	chess[12].setPos(Position(3, 1));
	chess[13].setPos(Position(6, 1));
	chess[12].setOriginPos(Position(3, 1));
	chess[13].setOriginPos(Position(6, 1));
	for (int i = 12; i < 14; i++) {
		chess[i].setType(Type::bishop);
		chess[i].setIcon('B');
	}

	// for queen
	chess[14].setPos(Position(4, 1));
	chess[14].setOriginPos(Position(4, 1));
	chess[14].setType(Type::queen);
	chess[14].setIcon('Q');

	// for king
	chess[15].setPos(Position(5, 1));
	chess[15].setOriginPos(Position(5, 1));
	chess[15].setType(Type::king);
	chess[15].setIcon('K');
}

// Intent: get the reference of the given chess
// Pre: there should be a chess on the pos
// Post: the chess can be modified if find
Chess& Player::findChess(const Position& pos) {
	for (int i = 0; i < 16; i++) {
		if (chess[i].getPos() == pos && chess[i].getIsAlive()) {
			return chess[i];
		}
	}

	return chess[0];
}

// For FEN
Chess& Player::findByIcon(char c)
{
	for (int i = 0; i < 16; i++) {
		if (chess[i].getIcon() == c) {
			return chess[i];
		}
	}

	return chess[0];
}

/**
  * Intent : move chess's Position
  * Pre : start and end Position
  * Post : none
 */
void Player::moveChess(const Position& start, const Position& end) {
	int startIndex, endIndex = -1;

	//find chess
	for (int i = 0; i < 16; i++) {
		if (chess[i].getPos() == start && chess[i].getIsAlive())
		{
			startIndex = i;
		}
		if (chess[i].getPos() == end && chess[i].getIsAlive())
		{
			endIndex = i;
		}
	}

	//castling (change their posotion)
	if (chess[startIndex].getType() == Type::king && endIndex != -1 && chess[endIndex].getType() == Type::rook)
	{
		Position kingPos, rookPos;
		if (end.x - start.x > 0)
		{
			kingPos = { start.x + 2,start.y };
			rookPos = { start.x + 1,start.y };
		}
		else
		{
			kingPos = { start.x - 2,start.y };
			rookPos = { start.x - 1,start.y };
		}

		//do castling and make sure that they cant do this angain
		chess[startIndex].setPosition(kingPos);
		chess[endIndex].setPosition(rookPos);
		chess[startIndex].setNeverMove(0);
		chess[endIndex].setNeverMove(0);
	}
	else //normal move
	{
		//set position
		chess[startIndex].setPos(end);
		chess[startIndex].setNeverMove(0);
	}
}

// Intent: let chess did
// Pre: there should be a chess on the position end
// Post: the chess is set dead
void Player::ChessDie(const Position& end) {
	for (int i = 0; i < 16; i++) {
		if (chess[i].getPos() == end) {
			chess[i].setIsAlive(false);
		}
	}
}

// Intent: check if the player has valid move
// Pre: none
// Post: if player has valid move return true, other wise return false
bool Player::canMove()
{
	for (int i = 0; i < 16; i++)
	{
		if (!chess[i].getValidMove().empty() && chess[i].getIsAlive())return true;
	}
	return false;
}

// Intent: update the gBoard
// Pre: the board should be empty before update
// Post: the chess is shown on the board
void Player::updateBoard() {
	for (int i = 0; i < 16; i++) {
		if (chess[i].getIsAlive()) gBoard[chess[i].getY()][chess[i].getX()] = chess[i].getIcon();
	}
}

// Intent: update all chess
// Pre: none
// Post: the chess is updated
void Player::updateChess() {
	for (int i = 0; i < 16; i++) {
		if (chess[i].getIsAlive()) {
			chess[i].update();
			chess[i].updateValidMove();
		}
	}
}
