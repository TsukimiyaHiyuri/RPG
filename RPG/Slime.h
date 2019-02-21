#pragma once
#include "Enemy.h"
class Slime : public Enemy {

public:
	Slime(int x);

	virtual void loadGraphic();
	virtual void attack(Player *p);
};

