/***********************************************************************
 * File: Chess.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--05-17
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--05-17
 * Description: declaration of Chess class
***********************************************************************/
#pragma once 
#include "Position.h"
#include "Type.h"
#include "Variables.h"
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

bool isPositionValid(const Position& p);


class Chess {
private:
	//some variable
	bool isAlive = true;
	bool isDangerous = false;
	bool isWhite;
	bool moveTwo = false;
	bool neverMove = true;
	char icon;
	Type type;
	Position pos, originPos;
	vector<Position> validMove;

	//function for updating
	void moveKing(vector<Position>&, const Position&);
	void moveQueen(vector<Position>&, const Position&);
	void moveRook(vector<Position>&, const Position&);
	void moveBishop(vector<Position>&, const Position&);
	void moveKinght(vector<Position>&, const Position&);
	void movePawn(vector<Position>&, const Position&);

public:
	//constructor
	Chess(Type t, Position p, bool isW)
	{
		type = t;
		pos = p;
		originPos = p;
		if (isW)
		{
			switch (type)
			{
			case Type::king:
				icon = 'k';
				break;
			case Type::queen:
				icon = 'q';
				break;
			case Type::rook:
				icon = 'r';
				break;
			case Type::bishop:
				icon = 'b';
				break;
			case Type::knight:
				icon = 'n';
				break;
			case Type::pawn:
				icon = 'p';
				break;
			default:
				break;
			}
		}
		else
		{
			switch (type)
			{
			case Type::king:
				icon = 'K';
				break;
			case Type::queen:
				icon = 'Q';
				break;
			case Type::rook:
				icon = 'R';
				break;
			case Type::bishop:
				icon = 'B';
				break;
			case Type::knight:
				icon = 'N';
				break;
			case Type::pawn:
				icon = 'P';
				break;
			default:
				break;
			}
		}
	}
	Chess();

	//function for setting 
	void setPosition(const Position& p)
	{
		pos = p;
	}
	void setType(Type type) {
		this->type = type;
	}
	void setIcon(char icon) {
		this->icon = icon;
	}
	void setIsWhite(bool white)
	{
		this->isWhite = white;
	}
	void setIsAlive(bool isAlive) {
		this->isAlive = isAlive;
	}
	void setPos(Position pos) {
		this->pos = pos;
	}
	void setXY(int x, int y) { pos.x = x; pos.y = y; }
	void setOriginPos(Position pos) {
		this->originPos = pos;
	}
	void setMoveTwo(bool tof) { moveTwo = tof; }
	void setNeverMove(bool tof) { neverMove = tof; };
	void setValidMove(vector<Position> v) { validMove = v; }

	//function for getting 
	bool getIsAlive() { return isAlive; };
	bool getIsDangerous() { return isDangerous; };
	bool getIsWhite() { return isWhite; };
	bool getMoveTwo() { return moveTwo; };
	bool getNeverMove() { return neverMove; };
	char getIcon() { return icon; };
	Type getType() { return type; };
	Position getPos() { return pos; };
	int getX() { return pos.x; }
	int getY() { return pos.y; }
	vector<Position>& getValidMove() { return validMove; }

	//function for updating
	void updateValidMove();
	void update(); //pawn upgrade
};

