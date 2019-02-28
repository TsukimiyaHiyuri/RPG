#pragma once
#include "Map.h"
#include "Player.h"
#define GRASSNUM 3 * 13
#define SEANUM 5

class Player;

class WorldMap : public Map {
	int grass[GRASSNUM];
	int sea[SEANUM];
	std::vector<std::vector<int>> mapGrass;
	std::vector<std::vector<int>> mapSea;
public:
	WorldMap();
	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
	virtual void setNPC();
	virtual void setEnemy();
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy);
};

extern WorldMap world;

