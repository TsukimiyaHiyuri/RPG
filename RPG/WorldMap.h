#pragma once
#include "Map.h"
#include "Player.h"
#define GRASSNUM 3 * 13
#define SEANUM 5

class Player;
class Map;

class WorldMap : public Map {
public:
	WorldMap(Sound *sound);
	virtual void setMapGround();
	virtual void setMapBridge();
	virtual void setMapSea();

	virtual void loadMapTip();
	bool judgeWall(int x, int y);
	virtual void changeMap(Player *p, Map *nowMap);
	virtual void setNPC();
	virtual void setEnemy();
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy);
};

extern WorldMap world;

