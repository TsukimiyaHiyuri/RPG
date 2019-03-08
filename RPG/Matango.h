#pragma once
#ifndef _Matango_
#define _Matango_

#include "Enemy.h"
#include "Sound.h"

class Sound;

class Matango : public Enemy {
public:
	Matango(int x, Sound *sound);

	virtual void loadGraphic();
	virtual std::string attack(Player *p);
	virtual Enemy *getEnemy(int x);
};

#endif