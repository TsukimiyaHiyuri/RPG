#pragma once
#ifndef _ITEMSELECTWINDOW_
#define _ITEMSELECTWINDOW_

#include "Player.h"
#include "Sound.h"
#include <string>
#include <vector>
#define ITEMCOMANDNUM 2
#define ITEMSELECTWINDOWX1 400
#define ITEMSELECTWINDOWY1 300
#define ITEMSELECTWINDOWX2 480
#define ITEMSELECTWINDOWY2 400
#define ITEMSELECTWINDOWINTERBAL 20

class Sound;

enum ItemComand {
	ComandUse = 0,
	ComandEquip = 1,
};

class ItemSelectWindow {
	bool isHide;
	int selectNum;
	int itemNum;	//　選択されたアイテムの番号
	Player *player;
	std::vector<std::string> list;
	std::string battleWindowStr;
	Sound *sound;

public:
	ItemSelectWindow() { this->isHide = true; }
	ItemSelectWindow(Player *player, int itemNum, Sound *sound);
	void drawItemSelectWindow();
	void setList();
	void moveSelector();
	bool select();
	bool drawAll();
	std::string getBattleWindowStr() { return this->battleWindowStr; }

	bool getIsHide() { return isHide; }
	void init();
};

#endif