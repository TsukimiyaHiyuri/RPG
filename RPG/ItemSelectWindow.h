#pragma once
#ifndef _ITEMSELECTWINDOW_
#define _ITEMSELECTWINDOW_

#include "Player.h"
#include <string>
#include <vector>
#define ITEMCOMANDNUM 2
#define ITEMSELECTWINDOWX1 400
#define ITEMSELECTWINDOWY1 300
#define ITEMSELECTWINDOWX2 480
#define ITEMSELECTWINDOWY2 400
#define ITEMSELECTWINDOWINTERBAL 20

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

public:
	ItemSelectWindow() { this->isHide = true; }
	ItemSelectWindow(Player *player, int itemNum);
	void drawItemSelectWindow();
	void setList();
	void moveSelector();
	bool select();
	bool drawAll();

	bool getIsHide() { return isHide; }
	void init();
};

#endif