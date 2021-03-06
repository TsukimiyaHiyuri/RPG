#pragma once
#ifndef _StatusWindow_
#define _StatusWindow_

#include "Player.h"
#include "Sound.h"
#include <vector>
#include <string>
#define DRAWXSTATUS1 230
#define DRAWYSTATUS1 30
#define DRAWXSTATUS2 400
#define DRAWYSTATUS2 250
#define STATUSMENUNUM 10
#define STATUSINTERBAL 20

class Player;
class Sound;

enum StatusMenu {
	lv = 0,
	maxHp = 1,
	hp = 2,
	maxMp = 3,
	mp = 4,
	str = 5,
	def = 6,
	experience = 7,
	gold = 8,
	nextLv = 9
};

class StatusWindow {
	int selectNum;
	bool isHide;
	Player *player;
	std::vector<std::string> list;	// メニューウィンドウの項目の文字列
	Sound *sound;

public:
	StatusWindow() {}
	StatusWindow(Player *p, Sound *sound);
	void setList();
	void drawStatusWindow();
	void drawAll();
	void changeIsHide();
	void select();
	bool getIsHide() { return isHide; }
};

#endif