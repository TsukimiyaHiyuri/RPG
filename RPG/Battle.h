#pragma once

#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "ComandWindow.h"
#define BATTLEINTEBAL 15
#define WIDTH 640

class Player;
class Map;
class Enemy;
class ComandWindow;

class Battle {
	int gold;	// 戦闘で獲得するお金
	int exp;	// 戦闘で獲得する経験値
	int enemyNum;	// 敵の数
	bool isMyTurn;	// 現在自分のターンか？
	bool isFinish;	// 戦闘は終了したか？
	Enemy *enemy[MAXENEMYNUM];	// 敵の配列
	ComandWindow *comandWindow;
public:
	Battle();
	int encount(Player *player, Map *nowMap);
	void battle(Player *p);
	void init();
	bool getIsFinish() { return isFinish; }
};

