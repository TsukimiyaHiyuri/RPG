#pragma once
#include "Map.h"
#include "Player.h"

class Player;

class WorldMap : public Map
{
public:
	WorldMap();
	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
	virtual void setNPC();
	virtual void setEnemy();
};

extern WorldMap world;

