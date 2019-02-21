#pragma once
#ifndef _MAGICWINDOW_
#define _MAGICWINDOW_

#include "Enemy.h"
#include "Player.h"
#include "EnemyListWindow.h"
#define MAGICWINDOWX1 210
#define MAGICWINDOWY1 300
#define MAGICWINDOWX2 350
#define MAGICWINDOWY2 400
#define MAGICWINDOWINTERBAL 20

class Enemy;
class Player;
class EnemyListWindow;

class MagicWindow {
	bool isHide;
	int selectNum;
	int enemyNum;
	Player *player;
	EnemyListWindow *enemyListWindow;
	Enemy *enemy[MAXENEMYNUM];

public:
	MagicWindow();
	MagicWindow(Player *p, Enemy *e[], int enemyNum);
	void drawMagicWindow();
	void moveSelector();
	bool selsect();
	bool drawAll();

	bool getIsHide() { return isHide; }
	void init();
};

#endif