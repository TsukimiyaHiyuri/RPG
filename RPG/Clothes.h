#pragma once
#include "Item.h"

class Clothes : public Item {
public:
	Clothes();
	virtual void addBelongings(Player *p);
	virtual void equip(Player *p);
	virtual void remove(Player *p);
	virtual void use(Player *p, std::string *str);
};

