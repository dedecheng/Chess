/***********************************************************************
 * File: Chess.cpp
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--05-17
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--05-17
 * Description: code of Chess class
***********************************************************************/
#pragma once 
#include "Chess.h"

using namespace std;

/**
  * Intent : constructor
  * Pre : none
  * Post : none
 */
Chess::Chess()
{
	bool isAlive = true;
	bool isDangerous = false;
	bool isWhite = true;
	bool justMoveTwo = false;
	char icon = ' ';
	Type type = Type::pawn;
	Position pos(0, 0), originPos(0, 0);
	vector<Position> validMove;
}

/**
  * Intent : update chess type and icon
  * Pre : none
  * Post : none
 */
void Chess::update()
{
	if (type == Type::pawn)
	{
		if (isWhite)
		{
			if (pos.y == 1)
			{
				int tp;
				/*while (type == Type::pawn) {
					cout << "Choose new type (2:Q 3:R 4:B 5:N):";
					cin >> tp;
					switch (tp) {
					case 2:
						type = Type::queen;
						icon = 'q';
						break;
					case 3:
						type = Type::rook;
						icon = 'r';
						break;
					case 4:
						type = Type::bishop;
						icon = 'b';
						break;
					case 5:
						type = Type::knight;
						icon = 'n';
						break;
					default:
						type = type;
						break;
					}
				}*/
				type = Type::queen;
				icon = 'q';
			}
		}
		else
		{
			if (pos.y == 8)
			{
				int tp;
				/*while (type == Type::pawn) {
					cout << "Choose new type (2:Q 3:R 4:B 5:N):";
					cin >> tp;
					switch (tp) {
					case 2:
						type = Type::queen;
						icon = 'Q';
						break;
					case 3:
						type = Type::rook;
						icon = 'R';
						break;
					case 4:
						type = Type::bishop;
						icon = 'B';
						break;
					case 5:
						type = Type::knight;
						icon = 'N';
						break;
					default:
						type = type;
						break;
					}
				}*/
				type = Type::queen;
				icon = 'Q';
			}
		}
	}
}

/**
  * Intent : update validMove vector
  * Pre : none
  * Post : none
 */
void Chess::updateValidMove()
{
	validMove.clear();

	if (!isAlive) return;

	//update according to type of chess
	switch (type)
	{
	case Type::king:
		moveKing(validMove, pos);
		break;
	case Type::queen:
		moveQueen(validMove, pos);
		break;
	case Type::rook:
		moveRook(validMove, pos);
		break;
	case Type::bishop:
		moveBishop(validMove, pos);
		break;
	case Type::knight:
		moveKinght(validMove, pos);
		break;
	case Type::pawn:
		movePawn(validMove, pos);
		break;
	default:
		break;
	}
}


/**
  * Intent : Check if input start or end is valid
  * Pre : position
  * Post : bool
 */
bool isPositionValid(const Position& p)
{
	//if in board
	if (p.x > 8 || p.x < 1 || p.y>8 || p.y < 1) return false;
	else return true;
}

/**
  * Intent : test if can go
  * Pre : pos, isWhite, meetEnemy
  * Post : bool
 */
bool canGo(Position p, bool isWhite, bool& meetEnemy)
{
	if (isPositionValid(p) && !meetEnemy)
	{
		if (isWhite)
		{
			if (islower(gBoard[p.y][p.x])) return 0;
			if (isupper(gBoard[p.y][p.x])) meetEnemy = true;
		}
		else
		{
			if (isupper(gBoard[p.y][p.x])) return 0;
			if (islower(gBoard[p.y][p.x])) meetEnemy = true;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * Intent : test if can go
  * Pre :  pos, isWhite
  * Post : bool
 */
bool canGo(Position p, bool isWhite)
{
	if (isPositionValid(p))
	{
		if (gBoard[p.y][p.x] != ' ') return 0;
		else return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * Intent : move King
  * Pre : validMove, position
  * Post : none
 */
void Chess::moveKing(vector<Position>& v, const Position& p)
{
	//move vector
	int move[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
	bool meetEnemy = false;

	for (int i = 0; i < 8; i++)
	{
		meetEnemy = false;
		Position t = p;
		t.x += move[i][0];
		t.y += move[i][1];

		//pushing if canGo
		if (canGo(t, isWhite, meetEnemy))
		{
			v.push_back(t);
		}
	}
}

/**
  * Intent : move Queen
  * Pre : validMove, position
  * Post : none
 */
void Chess::moveQueen(vector<Position>& v, const Position& p)
{
	moveRook(v, p);
	moveBishop(v, p);
}

/**
  * Intent : move Rook
  * Pre : validMove, position
  * Post : none
 */
void Chess::moveRook(vector<Position>& v, const Position& p)
{
	//do four direction
	//if cant go we break loop
	bool meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position top(p.x, p.y - i);

		if (canGo(top, isWhite, meetEnemy)) v.push_back(top);
		else break;
	}

	meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position down(p.x, p.y + i);

		if (canGo(down, isWhite, meetEnemy)) v.push_back(down);
		else break;
	}

	meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position left(p.x - i, p.y);

		if (canGo(left, isWhite, meetEnemy)) v.push_back(left);
		else break;
	}

	meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position right(p.x + i, p.y);

		if (canGo(right, isWhite, meetEnemy)) v.push_back(right);
		else break;
	}

}

/**
  * Intent : move Bishop
  * Pre : validMove, position
  * Post : none
 */
void Chess::moveBishop(vector<Position>& v, const Position& p)
{
	//do four direction
	//if cant go we break loop
	bool meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position topLeft(p.x - i, p.y - i);

		if (canGo(topLeft, isWhite, meetEnemy)) v.push_back(topLeft);
		else break;
	}

	meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position topRight(p.x + i, p.y - i);

		if (canGo(topRight, isWhite, meetEnemy)) v.push_back(topRight);
		else break;
	}

	meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position donwLeft(p.x - i, p.y + i);

		if (canGo(donwLeft, isWhite, meetEnemy)) v.push_back(donwLeft);
		else break;
	}

	meetEnemy = false;
	for (int i = 1; i < 8; i++) {
		Position donwRight(p.x + i, p.y + i);

		if (canGo(donwRight, isWhite, meetEnemy)) v.push_back(donwRight);
		else break;
	}
	/*
	Position t = p;
	for (int i = 1; i < 8; i++)
	{
		Position a = { t.x + i,t.y + i },
			b = { t.x + i,t.y - i },
			c = { t.x - i,t.y + i },
			d = { t.x - i,t.y - i };
		if (canGo(a, isWhite))
		{
			v.push_back(a);
		}
		if (canGo(b, isWhite))
		{
			v.push_back(b);
		}
		if (canGo(c, isWhite))
		{
			v.push_back(c);
		}
		if (canGo(d, isWhite))
		{
			v.push_back(d);
		}
	}*/
}

/**
  * Intent : move Kinght
  * Pre : validMove, position
  * Post : none
 */
void Chess::moveKinght(vector<Position>& v, const Position& p)
{
	//move vector
	int move[8][2] = { {-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1} };
	bool meetEnemy = false;
	for (int i = 0; i < 8; i++)
	{
		meetEnemy = false;
		Position t = p;
		t.x += move[i][0];
		t.y += move[i][1];

		//pushing if canGo
		if (canGo(t, isWhite, meetEnemy))
		{
			v.push_back(t);
		}
	}
}

/**
  * Intent : move Pawn
  * Pre : validMove, position
  * Post : none
 */
void Chess::movePawn(vector<Position>& v, const Position& p)
{
	//moveTwo = 0;

	//white
	if (isWhite)
	{


		Position t = p;

		//move forward
		bool firstMove = false;
		Position forward = { t.x,t.y - 1 };
		if (canGo(forward, isWhite))
		{
			v.push_back(forward);
			firstMove = true;
		}

		//move two
		if (p.x == originPos.x && p.y == originPos.y && firstMove)
		{
			Position two = { t.x,t.y - 2 };
			if (canGo(two, isWhite))
			{
				v.push_back(two);
			}
		}

		//eat diagnolly
		bool meetEnemy = false;
		Position upLeft = { t.x - 1,t.y - 1 }, upRight = { t.x + 1,t.y - 1 };
		if (canGo(upLeft, isWhite, meetEnemy) && isupper(gBoard[upLeft.y][upLeft.x]))
		{
			v.push_back(upLeft);
		}
		meetEnemy = false;
		if (canGo(upRight, isWhite, meetEnemy) && isupper(gBoard[upRight.y][upRight.x]))
		{
			v.push_back(upRight);
		}

	}
	else//black
	{
		Position t = p;

		//move forward
		Position forward = { t.x,t.y + 1 };
		bool firstMove = false;
		if (canGo(forward, isWhite))
		{
			v.push_back(forward);
			firstMove = true;
		}

		//move two
		if (p.x == originPos.x && p.y == originPos.y && firstMove)
		{
			Position two = { t.x,t.y + 2 };
			if (canGo(two, isWhite))
			{
				v.push_back(two);
			}
		}

		//eat diagnolly
		bool meetEnemy = false;
		Position downLeft = { t.x - 1,t.y + 1 }, downRight = { t.x + 1,t.y + 1 };
		if (canGo(downLeft, isWhite, meetEnemy) && islower(gBoard[downLeft.y][downLeft.x]))
		{
			v.push_back(downLeft);
		}
		meetEnemy = false;
		if (canGo(downRight, isWhite, meetEnemy) && islower(gBoard[downRight.y][downRight.x]))
		{
			v.push_back(downRight);
		}

	}

}
