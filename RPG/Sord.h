#pragma once
#include "Item.h"
#include "Player.h"

class Sord : public Item {

public:
	Sord();
	virtual void addBelongings(Player *p);
	virtual void equip(Player *p);
	virtual void remove(Player *p);
};

