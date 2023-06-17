/***********************************************************************
 * File: Game.h
 * Author: Tone
 * Create date: 2023/05/17
 * Editor: Tone
 * Update Date: 2023/05/17
 * Description: This header declare functions about game management
 * ***********************************************************************/
#pragma once
#include "Player.h"
#include "Position.h"
#include "Chess.h"
#include "Variables.h"
#include "ViewManager.h"
#include "GameData.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <cctype>
#include <vector>


class Game : public ViewManager { // inherent
private:
	Player playerBlack, playerWhite;
	int lastChangeTurn = 0, turns = 0;
	vector<gameData> record;

public:
	Player getplayerBlack() { return playerBlack; }
	Player getplayerWhite() { return playerWhite; }
	bool getPlayerWhiteCheck() { return playerWhite.getCheck(); }
	bool getPlayerBlackCheck() { return playerBlack.getCheck(); }
	void initialGame();
	void update();
	void setTurns() { turns++; };
	void printPathBoard(const Position&);
	void readFEN(ifstream& file);
	void boardFEN();
	void move(const Position& start, const Position& end);

	//for surrender
	void whiteSurrender();
	void blackSurrender();

	//for spaciel case
	//castle
	void whiteUpdateCastling();
	void blackUpdateCastling();
	//passant
	void whiteUpdatePassant();
	void blackUpdatePassant();
	void whiteDoPassant(const Position& start, const Position& end);
	void blackDoPassant(const Position& start, const Position& end);
	void whiteMoveTwo(const Position& start, const Position& end);
	void blackMoveTwo(const Position& start, const Position& end);
	void resetAllMoveTwoW();
	void resetAllMoveTwoB();

	//check
	void updateForCheck();
	void refreshCheck();

	bool isStartValid(const Position&);
	bool isEndValid(const Position&, const Position&);
	bool gameover();
	bool search(const vector<Position>& location, const Position& pos);
	int getTurns() { return turns; };

	//operator overloading for assignment
	void operator= (Game g)
	{
		playerBlack = g.playerBlack;
		playerWhite = g.playerWhite;
		lastChangeTurn = g.lastChangeTurn;
		turns = g.turns;
	}

	//for undo redo
	void undo();
	void redo();
	void setData(int);
	void newRecord();
	int getRecordSize();
};

