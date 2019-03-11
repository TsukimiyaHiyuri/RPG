#pragma once
#ifndef _ENEMYLISTWINDOW_
#define _ENEMYLISTWINDOW_

#include "Player.h"
#include "Enemy.h"
#include "ComandType.h"
#include "ComandWindow.h"
#include "Sound.h"
#include <string>
#define ENEMYLISTWINDOWX1 360
#define ENEMYLISTWINDOWY1 300
#define ENEMYLISTWINDOWX2 500
#define ENEMYLISTWINDOWY2 400
#define ENEMYLISTWINDOWINTERBAL 20

class Player;
class Enemy;
class Sound;

class EnemyListWindow {
	bool isHide;
	int selectNum;
	Enemy *enemy[MAXENEMYNUM];
	Player *player;
	int liveNum;
	int enemyNum;
	ComandType comandType;
	int magicNum;
	Sound *sound;

	std::string battleWindowStr;

public:
	EnemyListWindow() { this->isHide = true; }
	EnemyListWindow(Player *p, Enemy *e[], int eneNum, int magicNum, ComandType comandType, Sound *sound);
	int setEnemy();
	void drawEnemyListWindow();
	void moveSelector();
	bool select();
	bool drawAll();
	bool getIsHide() { return isHide; }
	std::string getBattleWindowStr() { return this->battleWindowStr; }
	void init();
};

#endif