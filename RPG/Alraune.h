#pragma once
#include "Enemy.h"
class Alraune : public Enemy {
public:
	Alraune(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

