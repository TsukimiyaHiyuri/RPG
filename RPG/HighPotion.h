#pragma once
#include "Item.h"
#include "Player.h"
#define HIGHPOTION 70

class Player;

class HighPotion : public Item
{
public:
	HighPotion();
	virtual void use(Player *p);
	virtual void use(Player *player, std::string *str);
	virtual void addBelongings(Player *p);
};

