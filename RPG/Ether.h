#pragma once
#include "Item.h"
#define ETHER 15
class Ether : public Item {
public:
	Ether();
	virtual void use(Player *p);
	virtual void use(Player *p, std::string *str);
	virtual void addBelongings(Player *p);
};

