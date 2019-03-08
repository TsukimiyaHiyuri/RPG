#pragma once
#include "Enemy.h"
class Skeleton : public Enemy {
public:
	Skeleton(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

