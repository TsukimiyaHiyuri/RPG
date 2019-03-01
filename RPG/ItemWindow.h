#pragma once
#ifndef _ITEMWINDOW_
#define _ITEMWINDOW_

#include "Player.h"
#include "Item.h"
#include "ItemSelectWindow.h"
#define ITEMWINDOWX1 210
#define ITEMWINDOWY1 300
#define ITEMWINDOWX2 350
#define ITEMWINDOWY2 400
#define ITEMWINDOWINTERBAL 20

class Player;
class Item;
class ItemSelectWindow;

class ItemWindow {
	bool isHide;
	ItemSelectWindow *itemSelectWindow;
	Player *player;
	int selectNum;
	std::string battleWindowStr;

public:
	ItemWindow();
	ItemWindow(Player *player);
	void drawItemWindow();
	void moveSelector();
	void select();
	bool drawAll();
	std::string getBattleWindowStr() { return this->battleWindowStr; }

	bool getIsHide() { return isHide; }
	void init();
};

#endif