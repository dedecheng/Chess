/***********************************************************************
 * File: SoundPlay.h
 * Author: Raymin
 * Create Date: 2023/05/15
 * Editor: Raymin
 * Update Date: 2023/05/15
 * Description: when calling this, it would play music
***********************************************************************/

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

void playSound() {
	PlaySound(TEXT(".\\Sound\\Sound.wav"), NULL, SND_ASYNC);
}