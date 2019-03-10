#pragma once
#include "Enemy.h"

class Clown : public Enemy {
public:
	Clown(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

