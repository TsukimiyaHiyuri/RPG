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
	int gold;	// �퓬�Ŋl�����邨��
	int exp;	// �퓬�Ŋl������o���l
	int enemyNum;	// �����Ă���G�̐�
	int lookEnemyNum;	// ���ݎQ�Ƃ��Ă���G�̓Y����
	bool isMyTurn;	// ���ݎ����̃^�[�����H
	bool isFinish;	// �퓬�͏I���������H
	bool finishWindowFlag;	// �퓬�I���̃E�B���h�E�̃t���O
	Enemy *enemy[MAXENEMYNUM];	// �G�̔z��
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

