#pragma once
#include "Map.h"
#include "Sound.h"

class Sound;

class MazeMap : public Map {
public:
	MazeMap(Sound *sound);

	virtual void setMapGround();
	virtual void setMapBridge();
	virtual void setMapSea();

	virtual void loadMapTip();
	virtual bool judgeWall(int x, int y);
	virtual void changeMap(Player *p, Map *nowMap);
	virtual void setNPC();
	virtual void drawMapTip(int drawx, int drawy, int pointx, int pointy);
};

