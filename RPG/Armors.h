#pragma once
#include "Item.h"
class Armors : public Item {
public:
	Armors();

	virtual void addBelongings(Player *p);
	virtual void equip(Player *p);
	virtual void remove(Player *p);
};

