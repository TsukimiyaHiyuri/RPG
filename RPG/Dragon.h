#pragma once
#include "Enemy.h"

class Dragon : public Enemy {
public:
	Dragon(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

