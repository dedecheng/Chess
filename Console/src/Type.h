/***********************************************************************
 * File: Type.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--05-17
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--05-17
 * Description: declaration of enum Type and ValidInput
***********************************************************************/
#pragma once

enum Type
{
	none = 0,
	king = 1,
	queen = 2,
	rook,
	bishop,
	knight,
	pawn
};

enum ValidInput
{
	EESC = 0,
	E1 = 1,
	INVALID = 2
};
