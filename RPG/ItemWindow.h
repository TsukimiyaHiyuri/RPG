#pragma once
#ifndef _ITEMWINDOW_
#define _ITEMWINDOW_

#include "Player.h"
#include "Item.h"
#include "ItemSelectWindow.h"
#include "Sound.h"
#define ITEMWINDOWX1 210
#define ITEMWINDOWY1 300
#define ITEMWINDOWX2 350
#define ITEMWINDOWY2 470
#define ITEMWINDOWDISCRIPTIONX1 450
#define ITEMWINDOWDISCRIPTIONY1 300
#define ITEMWINDOWDISCRIPTIONX2 590
#define ITEMWINDOWDISCRIPTIONY2 470
#define ITEMWINDOWINTERBAL 20

class Player;
class Item;
class ItemSelectWindow;
class Sound;

class ItemWindow {
	bool isHide;
	ItemSelectWindow *itemSelectWindow;
	Player *player;
	int selectNum;
	std::string battleWindowStr;
	Sound *sound;

public:
	ItemWindow();
	ItemWindow(Player *player, Sound *sound);
	void drawItemWindow();
	void moveSelector();
	void select();
	bool drawAll();
	std::string getBattleWindowStr() { return this->battleWindowStr; }

	bool getIsHide() { return isHide; }
	void init();
};

#endif