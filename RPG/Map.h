#pragma once
#ifndef _MAP_
#define _MAP_

#include "Player.h"
#include <vector>
#define MAP_SIZE 32          // マップチップ一つのドットサイズ
#define TIPSIZE 256

class Player;

enum MapName {
	World = 0,
	Town = 1,
};

class Map {
protected:
	int width;		// マップの幅
	int height;		// マップの高さ
	bool isEncount;	// エンカウントするか？
	std::vector<std::vector<int>> map;		// マップビットの二次元配列
	int mapTip[TIPSIZE];				// マップビットのグラフィックハンドル
public:
	Map() {}
	Map(int wid, int hei);
	virtual void setMap() {};
	virtual void loadMapTip() {};
	virtual bool judgeWall(int x, int y);
	virtual void changeMap(Player *p) {};
	void drawMap(int ScrollX, int ScrollY, Player *p);
	bool getIsEncount() { return isEncount; }
};

extern Map *nowMap;

#endif