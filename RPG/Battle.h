#pragma once

#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "ComandWindow.h"
#include "BattleWindow.h"
#include "Sound.h"
#define BATTLEINTEBAL 30
#define WIDTH 640
#define STATUSX1 5
#define STATUSY1 300
#define STATUSX2 95
#define STATUSY2 400
#define STATUSINTERBAL 20

class Player;
class Map;
class Enemy;
class ComandWindow;
class BattleWindow;
class Sound;

class Battle {
	int gold;	// 戦闘で獲得するお金
	int exp;	// 戦闘で獲得する経験値
	int enemyNum;	// 生きている敵の数
	int lookEnemyNum;	// 現在参照している敵の添え字
	bool isMyTurn;	// 現在自分のターンか？
	bool isFinish;	// 戦闘は終了したか？
	bool isEscape;
	bool isBoss;	// エンカウントしているのはボスか？
	bool finishWindowFlag;	// 戦闘終了のウィンドウのフラグ
	Enemy *enemy[MAXENEMYNUM];	// 敵の配列
	ComandWindow *comandWindow;
	BattleWindow *battleWindow;
	BattleWindow *finishWindow;
	Sound *sound;

public:
	Battle(Sound *sound);
	int encount(Player *player, Map *nowMap);
	int bossEncount(Player *player);
	void battle(Player *p, bool *clearFlag, Map *nowMap);
	void init();
	void sortEnemy();
	int countLiveEnemy();
	bool getIsFinish() { return isFinish; }
	void escape(Player *player);
	void drawStatus(Player *player);
	bool getIsBoss() { return this->isBoss; }
	void gameOver(Player *player);
	void finishAction(Player *player);
};

