#pragma once
#include "Item.h"

class SuperArmor : public Item {
public:
	SuperArmor();
	virtual void addBelongings(Player *p);
	virtual void equip(Player *p);
	virtual void remove(Player *p);
	virtual void use(Player *p, std::string *str);
};

