#pragma once
#ifndef _ENEMYLISTWINDOW_
#define _ENEMYLISTWINDOW_

#include "Player.h"
#include "Enemy.h"
#include "ComandType.h"
#include "ComandWindow.h"
#define ENEMYLISTWINDOWX1 210 
#define ENEMYLISTWINDOWY1 300
#define ENEMYLISTWINDOWX2 350
#define ENEMYLISTWINDOWY2 400
#define ENEMYLISTWINDOWINTERBAL 20

class Player;
class Enemy;

class EnemyListWindow {
	bool isHide;
	int selectNum;
	Enemy *enemy[MAXENEMYNUM];
	Player *player;
	int liveNum;
	int enemyNum;
	ComandType comandType;
	int magicNum;

public:
	EnemyListWindow() { this->isHide = true; }
	EnemyListWindow(Player *p, Enemy *e[], int eneNum, int magicNum, ComandType comandType);
	int setEnemy();
	void drawEnemyListWindow();
	void moveSelector();
	bool select();
	bool drawAll();
	bool getIsHide() { return isHide; }
	void init();
};

#endif