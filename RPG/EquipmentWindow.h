#pragma once
#ifndef _EQUIPMENTWINDOW_
#define _EQUIPMENTWINDOW_

#include "Item.h"
#include "Player.h"
#include "SelectWindow.h"
#include "Sound.h"
#include <string>
#include <vector>
#define DRAWDESCRIPTIONX1 420
#define DRAWDESCRIPTIONY1 100
#define DRAWDESCRIPTIONX2 560
#define DRAWDESCRIPTIONY2 250

class Item;
class SelectWindow;
class Player;
class Sound;

class EquipmentWindow {
	int selectNum;
	bool isHide;
	Player *player;
	SelectWindow *selectWindow;
	Sound *sound;

public:
	EquipmentWindow() {}
	EquipmentWindow(Player *who, Sound *sound);
	void drawEquipmentWindow();
	void drawAll();
	void changeIsHide();
	void moveSelector();
	void select();
	void init();
	bool canSelect();
	bool getIsHide() { return isHide; }
};

#endif