#pragma once
#ifndef _Ending_
#define _Ending_

#include "Sound.h"
#include "BackGround.h"
#include <vector>
#include <string>
#define ENDINGLISTNUM 2
#define ENDINGDRAWX 400.0
#define ENDINGSPEED 0.2
#define ENDINGDRAWY 495
#define ENDINGINTERBAL 170

class Sound;
class BackGround;

class Ending {
	long cnt;
	int endingFont;
	std::vector<std::string> list;
	Sound *sound;
	BackGround *backGround;

public:
	Ending(Sound *sound, BackGround *backGround);
	void setList();
	void setFont();
	void drawEndind();
	void playEndingBGM();
	void drawAll();
	void drawBackGround();
	bool canDraw(int i, float y);
};

#endif