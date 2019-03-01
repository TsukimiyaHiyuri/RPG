#pragma once
#include "Enemy.h"
#include <string>
class Slime : public Enemy {

public:
	Slime(int x, Sound *sound);

	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

