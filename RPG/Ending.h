#pragma once
#ifndef _Ending_
#define _Ending_

#include "Sound.h"
#include "BackGround.h"
#include <vector>
#include <string>
#define ENDINGLISTNUM 2
#define ENDINGDRAWY 520
#define ENDINGINTERBAL 100

class Sound;
class BackGround;

class Ending {
	long cnt;
	std::vector<std::string> list;
	Sound *sound;
	BackGround *backGround;

public:
	Ending(Sound *sound, BackGround *backGround);
	void setList();
	void drawEndind();
	void playEndingBGM();
	void drawAll();
	void drawBackGround();
	bool canDraw(int i, float y);
};

#endif