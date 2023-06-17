/***********************************************************************
 * File: Position.h
 * Author: Tone
 * Create date: 2023/05/17
 * Editor: Tone
 * Update Date: 2023/05/17
 * Description: declaration of Position class
 * ***********************************************************************/
#pragma once

typedef struct Position {
	int x, y;

	//consructor
	Position() {
		this->x = 0;
		this->y = 0;
	}
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	//operator overloading =
	Position& operator =(const Position& next)
	{
		x = next.x;
		y = next.y;
		return *this;
	}

	//operator overloading ==
	bool operator==(const Position& next)
	{
		if (this->x == next.x && this->y == next.y) {
			return true;
		}
		return false;
	}
} Position;
