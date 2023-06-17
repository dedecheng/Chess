/***********************************************************************
 * File: ViewManager.h
 * Author: Raymin
 * Create date: 2023/05/08
 * Editor: Raymin
 * Update Date: 2023/05/22
 * Description: header file to view board
 * ***********************************************************************/

#pragma once

#include "Variables.h"

#include <iostream>
#include <windows.h>
#include <cctype>

using namespace std;

class ViewManager {
public:
	// Intent: print the board on console
	// Pre: game must be playing
	// Post: print the board on the console
	void printBoard() const;
};
