/***********************************************************************
 * File: Player.h
 * Author: Tone
 * Create date: 2023/05/17
 * Editor: Tone
 * Update Date: 2023/05/17
 * Description: declaration of Player class
 * ***********************************************************************/
#pragma once
#include "Position.h"
#include "Chess.h"
#include "Type.h"
#include "Variables.h"
#include <iostream>

class Chess;

class Player {
private:
	bool isSurrender = false;
	bool check = false;
	Chess chess[16];

public:
	//for surrender
	bool getSurrender();
	void setSurrender();

	//for check
	bool getCheck() { return check; };
	void setCheck(bool tof) { check = tof; };

	//for initial
	void WinitialChess();
	void BinitialChess();

	//for update
	void updateBoard();
	void updateChess();
	void moveChess(const Position&, const Position&);
	void ChessDie(const Position&);
	bool canMove();

	//for get
	Chess& findChess(const Position&);
	Chess& findByIcon(char c);
	Chess* getChess() { return chess; };
	Chess& setChessGroup(int i) { return chess[i]; }

	//operator overloading for assignment
	void operator= (Player p)
	{
		isSurrender = p.isSurrender;
		check = p.check;
		for (int i = 0; i < 16; i++)
		{
			chess[i] = p.chess[i];
		}
	}
};
