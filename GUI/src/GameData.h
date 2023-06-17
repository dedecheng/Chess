#pragma once
#include "Player.h"
#include "Position.h"
#include "Chess.h"
#include "Variables.h"

typedef struct gameData {
	char gboard_[9][9];
	Player playerWhite_, playerBlack_;
	int lastChangeTurn_;
} gameData;
