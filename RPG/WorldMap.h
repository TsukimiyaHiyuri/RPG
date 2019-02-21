#pragma once
#include "Map.h"
#include "Player.h"

class Player;

class WorldMap : public Map
{
public:
	WorldMap() {
		this->loadMapTip();
		this->setMap();
		this->isEncount = true;
	}

	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
};

extern WorldMap world;

