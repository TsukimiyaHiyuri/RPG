#pragma once

#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "ComandWindow.h"
#include "BattleWindow.h"
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

class Battle {
	int gold;	// �퓬�Ŋl�����邨��
	int exp;	// �퓬�Ŋl������o���l
	int enemyNum;	// �����Ă���G�̐�
	int lookEnemyNum;	// ���ݎQ�Ƃ��Ă���G�̓Y����
	bool isMyTurn;	// ���ݎ����̃^�[�����H
	bool isFinish;	// �퓬�͏I���������H
	bool isBoss;	// �G���J�E���g���Ă���̂̓{�X���H
	bool finishWindowFlag;	// �퓬�I���̃E�B���h�E�̃t���O
	Enemy *enemy[MAXENEMYNUM];	// �G�̔z��
	ComandWindow *comandWindow;
	BattleWindow *battleWindow;
	BattleWindow *finishWindow;

public:
	Battle();
	int encount(Player *player, Map *nowMap);
	int bossEncount(Player *player);
	void battle(Player *p, bool *clearFlag, Map *nowMap);
	void init();
	void sortEnemy();
	int countLiveEnemy();
	bool getIsFinish() { return isFinish; }
	void battleFinish();
	void drawStatus(Player *player);
};

