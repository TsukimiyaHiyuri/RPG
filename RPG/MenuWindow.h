#pragma once

#include "StatusWindow.h"
#include "EquipmentWindow.h"
#include "Player.h"
#include "Sound.h"
#include <string>
#include <vector>
#define MENUNUM 3
#define DRAWX1 30
#define DRAWY1 30
#define DRAWX2 120
#define DRAWY2 200
#define INTERBAL 30

class StatusWindow;
class EquipmentWindow;
class Sound;

enum Menu {
	Equipment = 0,
	Paramater = 1,
	Save = 2,
};

class MenuWindow {
	int selectNum;
	bool isHide;
	std::vector<std::string> list;	// メニューウィンドウの項目の文字列
	Player *player;
	StatusWindow *statusWindow;
	EquipmentWindow *equipmentWindow;
	Sound *sound;

public:
	MenuWindow(Player *p, Sound *sound);
	void setList();
	void drawMenuWindow();
	void changeIsHide();
	void moveSelector();
	void select();
	void drawAll();
	void init();
	bool canSelect();
	bool getIsHide() { return isHide; }
};

