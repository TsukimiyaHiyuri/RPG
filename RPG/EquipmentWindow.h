#pragma once
#ifndef _EQUIPMENTWINDOW_
#define _EQUIPMENTWINDOW_

#include "Item.h"
#include "Player.h"
#include "SelectWindow.h"
#include <string>
#include <vector>
#define DRAWDESCRIPTIONX1 420
#define DRAWDESCRIPTIONY1 100
#define DRAWDESCRIPTIONX2 560
#define DRAWDESCRIPTIONY2 250

class Item;
class SelectWindow;
class Player;

class EquipmentWindow {
	int selectNum;
	bool isHide;
	Item * list[MAXBELONGINGS];	// メニューウィンドウの項目の文字列
	Player * who;
	SelectWindow selectWindow;
public:
	EquipmentWindow();
	EquipmentWindow(Player *who);
	void setList();
	void drawEquipmentWindow();
	void changeIsHide();
	void moveSelector();
	void select();
	void changeList();
	void throwItem(int n);
	bool getIsHide() { return isHide; }
	int getselectNum() { return selectNum; }
};

#endif