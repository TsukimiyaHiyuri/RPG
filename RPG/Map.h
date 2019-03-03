#pragma once
#ifndef _MAP_
#define _MAP_

#include "Player.h"
#include "NonPlayerCharacter.h"
#include "Enemy.h"
#include "Sound.h"
#include <vector>
#define MAP_SIZE 32          // マップチップ一つのドットサイズ
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
	int width;		// マップの幅
	int height;		// マップの高さ
	bool isEncount;	// エンカウントするか？
	std::vector<std::vector<int>> mapGround;		// マップビットの二次元配列
	std::vector<std::vector<int>> mapBridge;		// マップビットの二次元配列
	std::vector<std::vector<int>> mapSea;			// マップビットの二次元配列
	int ground[TIPSIZE];				// マップビットのグラフィックハンドル
	int bridge[TIPSIZE];
	int sea[TIPSIZE];
	NonPlayerCharacter *npc[MAXNPCNUM];
	NonPlayerCharacter *nowNPC;
	int npcNum;
	Sound *sound;

	Enemy *enemy[MAXENEMYNUM];
	int enemyNum;	// このマップで出現する敵の種類数

public:
	Map() {}
	Map(int wid, int hei);
	virtual void setMap();
	virtual void setMapGround() {}
	virtual void setMapBridge() {}
	virtual void setMapSea() {}
	virtual void loadMapTip() {}
	virtual bool judgeWall(int x, int y);
	virtual void changeMap(Player *p) {}
	virtual void setNPC() {};
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy) {}
	virtual void setEnemy() {}
	virtual bool bossIsEncount(int x, int y) { return false; }

	void setWidth() {}
	void setHeight() {}
	void drawMap(int ScrollX, int ScrollY, Player *p);
	void npcAction(Player *player);
	bool getIsEncount() { return isEncount; }
	bool judgeWallNPC(int x, int y);
	Enemy *getEnemy(int n, int x) { return this->enemy[n]->getEnemy(x); }
	int getEnemyNum() { return this->enemyNum; }
};

extern Map *nowMap;

#endif