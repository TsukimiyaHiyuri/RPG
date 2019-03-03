#pragma once
#include "Enemy.h"
#include "Sound.h"

class Sound;
class Enemy;

class BossEnemy : public Enemy {
public:
	BossEnemy(int x, Sound *sound);

	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

