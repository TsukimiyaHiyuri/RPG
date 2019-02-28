#pragma once
#include "Enemy.h"
class Bat : public Enemy {
public:
	Bat(int x);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};
