#pragma once
#ifndef _COMANDWINDOW_
#define _COMANDWINDOW_

#include "Player.h"
#include "Enemy.h"
#include "ItemWindow.h"
#include "EnemyListWindow.h"
#include "MagicWindow.h"
#include "ComandType.h"
#include "Sound.h"
#include <vector>
#include <string>
#define COMANDTYPENUM 4
#define COMANDWINDOWX1 100
#define COMANDWINDOWY1 300
#define COMANDWINDOWX2 200
#define COMANDWINDOWY2 400
#define COMANDWINDOWINTERBAL 20

class Player;
class Enemy;
class ItemWindow;
class EnemyListWindow;
class MagicWindow;
class Sound;

class ComandWindow {
	std::vector<std::string> list;	// コマンドの項目
	int selectNum;
	Player *player;
	Enemy *enemy[MAXENEMYNUM];
	bool isFinish;	// 自分のターンが終わったか？
	bool isHide;
	int enemyNum;
	ItemWindow *itemWindow;
	MagicWindow *magicWindow;
	EnemyListWindow *enemyListWindow;
	Sound *sound;

	std::string battleWindowStr;

public:
	ComandWindow(Player *player, Enemy *enemy[], int enemyNum, Sound *sound);
	void setList();
	void drawComandWindow();
	void moveSelector();
	bool select();
	bool drawAll();
	void init();
	std::string getBattleWindowStr() { return this->battleWindowStr; }

	bool getIsHide() { return this->isHide; }
};

#endif