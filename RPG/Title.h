#pragma once
#ifndef _Title_
#define _Title_

#include "BackGround.h"
#include "Sound.h"
#include <string>
#include <vector>
#define TITLEMENUNUM 3
#define TITLENAMEX 140
#define TITLENAMEY 100
#define TITLEMENUX 270
#define TITLEMENUY 270
#define TITLEMENUINTERBAL 45

class BackGround;
class Sound;

enum TitleMenu {
	Start = 0,
	Load = 1,
	Exit = 2
};

class Title {
	bool isHide;
	int titleFont;
	int menuFont;
	int selectNum;
	std::vector<std::string> list;
	std::string titleName;
	BackGround *backGround;
	Sound *sound;

public:
	Title(BackGround *bg, Sound *sound);
	void setList();
	void setTitleName(std::string titleName);
	void setFont();
	void changeIsHide();
	void drawTitleName();
	void drawTitleMenu();
	void drawTitleGraph();
	void playTitleBGM();
	bool select(bool *isFinish);
	void moveSelector();
	bool drawAll(bool *isFinish);
	void init();
};

#endif