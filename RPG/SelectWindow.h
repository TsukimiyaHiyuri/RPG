#pragma once
#include "Player.h"
#include "Sound.h"
#include <string>
#include <vector>
#define SELECTNUM 3
#define DRAWSELECTX1 30
#define DRAWSELECTY1 80
#define DRAWSELECTX2 100
#define DRAWSELECTY2 200
#define INTERBALSELECT 30

class Player;
class SelectWhoWindow;
class Sound;

enum Select {
	Use = 0,
	Equip = 1,
	Throw = 2,
	Defalt = 3,
};

class SelectWindow {
	int selectNum;
	int itemNum;
	bool isHide;
	Select selection;
	Player *player;
	Player *to;
	std::vector<std::string> list;	// メニューウィンドウの項目の文字列
	Sound *sound;

public:
	SelectWindow() {}
	SelectWindow(Player *p, Sound *sound);
	void setList();
	void drawSelectWindow();
	bool drawAll();
	void changeIsHide();
	void moveSelector();
	bool select();
	void init();
	bool getIsHide() { return isHide; }
	void setItemNum(int n) { this->itemNum = n; }
};

