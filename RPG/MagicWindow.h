#pragma once
#ifndef _MAGICWINDOW_
#define _MAGICWINDOW_

#include "Enemy.h"
#include "Player.h"
#include "EnemyListWindow.h"
#include "Sound.h"
#include <string>
#define MAGICWINDOWX1 210
#define MAGICWINDOWY1 300
#define MAGICWINDOWX2 350
#define MAGICWINDOWY2 400
#define MAGICWINDOWINTERBAL 20

class Enemy;
class Player;
class EnemyListWindow;
class Sound;

class MagicWindow {
	bool isHide;
	int selectNum;
	int enemyNum;
	Player *player;
	EnemyListWindow *enemyListWindow;
	Enemy *enemy[MAXENEMYNUM];
	Sound *sound;

	std::string battleWindowStr;

public:
	MagicWindow();
	MagicWindow(Player *p, Enemy *e[], int enemyNum, Sound *sound);
	void drawMagicWindow();
	void moveSelector();
	bool selsect();
	bool drawAll();

	bool getIsHide() { return isHide; }
	std::string getBattleWindowStr() { return this->battleWindowStr; }
	void init();
};

#endif