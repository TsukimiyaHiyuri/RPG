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
	int gold;	// �퓬�Ŋl�����邨��
	int exp;	// �퓬�Ŋl������o���l
	int enemyNum;	// �G�̐�
	bool isMyTurn;	// ���ݎ����̃^�[�����H
	bool isFinish;	// �퓬�͏I���������H
	Enemy *enemy[MAXENEMYNUM];	// �G�̔z��
	ComandWindow *comandWindow;
public:
	Battle();
	int encount(Player *player, Map *nowMap);
	void battle(Player *p);
	void init();
	bool getIsFinish() { return isFinish; }
};

