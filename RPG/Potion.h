#pragma once
#include "Item.h"
#include "Player.h"
#define POTION 30

class Potion : public Item {
public:
	Potion();
	virtual void use(Player *p);
	virtual void use(Player *p, std::string *str);
	virtual void addBelongings(Player *p);
};