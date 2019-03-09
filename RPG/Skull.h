#pragma once
#include "Enemy.h"
class Skull : public Enemy {
public:
	Skull(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

