#pragma once
#include "Enemy.h"

class Cassowary : public Enemy {
public:
	Cassowary(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

