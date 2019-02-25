#pragma once

#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "ComandWindow.h"
#include "BattleWindow.h"
#define BATTLEINTEBAL 30
#define WIDTH 640

class Player;
class Map;
class Enemy;
class ComandWindow;
class BattleWindow;

class Battle {
	int gold;	// 戦闘で獲得するお金
	int exp;	// 戦闘で獲得する経験値
	int enemyNum;	// 生きている敵の数
	int lookEnemyNum;	// 現在参照している敵の添え字
	bool isMyTurn;	// 現在自分のターンか？
	bool isFinish;	// 戦闘は終了したか？
	bool finishWindowFlag;	// 戦闘終了のウィンドウのフラグ
	Enemy *enemy[MAXENEMYNUM];	// 敵の配列
	ComandWindow *comandWindow;
	BattleWindow *battleWindow;
	BattleWindow *finishWindow;

public:
	Battle();
	int encount(Player *player, Map *nowMap);
	void battle(Player *p);
	void init();
	void sortEnemy();
	int countLiveEnemy();
	bool getIsFinish() { return isFinish; }
	void battleFinish();
};

