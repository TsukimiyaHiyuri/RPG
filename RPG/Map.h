#pragma once
#ifndef _MAP_
#define _MAP_

#include "Player.h"
#include "NonPlayerCharacter.h"
#include "Enemy.h"
#include "Sound.h"
#include <vector>
#define MAP_SIZE 32          // �}�b�v�`�b�v��̃h�b�g�T�C�Y
#define TIPSIZE 256
#define MAXNPCNUM 8

class Player;
class NonPlayerCharacter;
class Sound;

enum MapName {
	World = 0,
	Town = 1,
};

class Map {
protected:
	int width;		// �}�b�v�̕�
	int height;		// �}�b�v�̍���
	bool isEncount;	// �G���J�E���g���邩�H
	std::vector<std::vector<int>> map;		// �}�b�v�r�b�g�̓񎟌��z��
	int mapTip[TIPSIZE];				// �}�b�v�r�b�g�̃O���t�B�b�N�n���h��
	NonPlayerCharacter *npc[MAXNPCNUM];
	NonPlayerCharacter *nowNPC;
	int npcNum;
	Sound *sound;

	Enemy *enemy[MAXENEMYNUM];
	int enemyNum;	// ���̃}�b�v�ŏo������G�̎�ސ�

public:
	Map() {}
	Map(int wid, int hei);
	virtual void setMap() {};
	virtual void loadMapTip() {};
	virtual bool judgeWall(int x, int y);
	virtual void changeMap(Player *p) {};
	virtual void setNPC() {};
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy) {}
	void drawMap(int ScrollX, int ScrollY, Player *p);
	void npcAction(Player *player);
	bool getIsEncount() { return isEncount; }
	bool judgeWallNPC(int x, int y);
	virtual void setEnemy() {}
	Enemy *getEnemy(int n, int x) { return this->enemy[n]->getEnemy(x); }
	int getEnemyNum() { return this->enemyNum; }
	virtual bool bossIsEncount(int x, int y) { return false; }
};

extern Map *nowMap;

#endif