#pragma once
#include "Item.h"

class Stick : public Item {
public:
	Stick();
	virtual void addBelongings(Player *p);
	virtual void equip(Player *p);
	virtual void remove(Player *p);
	virtual void use(Player *p, std::string *str);
};

