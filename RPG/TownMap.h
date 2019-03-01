#pragma once
#include "Map.h"
#include "WorldMap.h"
#include "Player.h"

class Player;

class TownMap : public Map {
	int grass[GRASSNUM];
	int sea[SEANUM];
	std::vector<std::vector<int>> mapSea;
	std::vector<std::vector<int>> mapGrass;
	std::vector<std::vector<int>> mapBridge;

public:
	TownMap(Sound *sound);

	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
	virtual void setNPC();
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy);
};

extern TownMap town;
