#pragma once
#include "Map.h"
#include "Player.h"

class Player;

class TownMap : public Map {
public:
	TownMap();

	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
	virtual void setNPC();
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy);
};

extern TownMap town;
