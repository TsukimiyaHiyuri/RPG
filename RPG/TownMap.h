#pragma once
#include "Map.h"
#include "Player.h"

class Player;

class TownMap : public Map {
public:
	TownMap() {
		this->loadMapTip();
		this->setMap();
		this->isEncount = false;
	}

	virtual void setMap();
	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p);
};

extern TownMap town;
