#pragma once
#include "Player.h"
#include "Sound.h"

class Hero : public Player {
public:
	Hero(Sound *sound);
	virtual void setLevelTable();
	virtual void levelUp(std::string *s);
	virtual void loadGraphic();
};

