#pragma once
#include "Map.h"
#include "WorldMap.h"

class SnowMap : public Map {
	int grass[GRASSNUM];
	int sea[SEANUM];
	std::vector<std::vector<int>> mapSea;
	std::vector<std::vector<int>> mapGrass;
	std::vector<std::vector<int>> mapBridge;

	int boss;
public:
	SnowMap(Sound *sound);

	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
	virtual void setNPC();
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy);
	virtual bool bossIsEncount(int x, int y);
};

