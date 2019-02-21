#pragma once

#include "Player.h"
#include <vector>
#include <string>
#define DRAWXSTATUS1 230
#define DRAWYSTATUS1 30
#define DRAWXSTATUS2 400
#define DRAWYSTATUS2 250
#define MENUNUM 9
#define INTERBAL 20

class Player;

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
};

class StatusWindow {
	int selectNum;
	bool isHide;
	Player * who;
	std::vector<std::string> list;	// メニューウィンドウの項目の文字列

public:
	StatusWindow();
	StatusWindow(Player *p);
	void setList();
	void drawStatusWindow();
	void changeIsHide();
	void moveSelector();
	bool getIsHide() { return isHide; }
	int getselectNum() { return selectNum; }
};

