#pragma once
#include "Item.h"
#include "Player.h"
#define HIGHPOTION 50

class Player;

class HighPotion : public Item
{
public:
	HighPotion();
	virtual void use(Player *p);
	virtual void addBelongings(Player *p);
};

