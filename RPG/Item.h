#pragma once
#ifndef _Item_
#define _Item_

#include "Player.h"
#include <string>

class Player;

enum Equipment {
	Weapon = 0,
	Armor = 1,
};

class Item {
protected:
	std::string name;
	std::string description;
	bool canEquip;
	bool canUse;
	int str;
	int def;
	Equipment type;
	bool isEquipt;
public:

	Item();
	virtual void use(Player *p);
	virtual void equip(Player *p) {}
	virtual void addBelongings() {}
	virtual void remove(Player *p) {}
	std::string getName() { return this->name; }
	std::string getDescription() { return this->description; }
	bool getIsEquip() { return isEquipt; }
	Equipment getType() { return type; }
	void changeIsEquript();
	bool getCanEquip() { return canEquip; }
	bool getCanUse() { return canUse; }
	void setIsEquip(bool f) { isEquipt = f; }
};

#endif
