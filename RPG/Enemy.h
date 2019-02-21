#pragma once
#ifndef _Enemy_
#define _Enemy_

#include "Player.h"
#include "Status.h"
#include <string>
#define MAXENEMYNUM 8
#define CORDINATEY 200

class Player;

class Enemy {
protected:
	Status status;
	int graphic;
	bool isHide;
	int x, y;

public:
	Enemy();
	void setStatus(std::string, int, int, int, int, int, int, int, long, long);
	int getHp() { return this->status.hp; }
	int getDef() { return this->status.def; }
	long getGold() { return this->status.gold; }
	long getExp() { return this->status.exp; }
	std::string getName() { return this->status.name; }

	void setCordinate(int x, int y);
	void damage(int n) { this->status.hp -= n; }
	void drawGraphic();
	int getCordinateX() { return this->x; }
	virtual void loadGraphic() {}
	virtual void attack(Player *p) {}
};

#endif