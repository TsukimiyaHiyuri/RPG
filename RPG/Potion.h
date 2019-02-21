#pragma once
#include "Item.h"
#include "Player.h"
#define POTION 30

class Potion : Item {
public:
	Potion();
	virtual void use(Player *p);
	virtual void addBelongings(Player *p);
};