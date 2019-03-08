#pragma once
#include "Enemy.h"
class Lizardman : public Enemy {
public:
	Lizardman(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

