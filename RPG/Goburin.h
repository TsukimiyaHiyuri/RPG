#pragma once
#include "Enemy.h"
class Goburin :
	public Enemy
{
public:
	Goburin(int x, Sound *sound);
	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

