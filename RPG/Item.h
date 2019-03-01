#pragma once
#ifndef _Item_
#define _Item_

#include "Player.h"
#include <string>

class Player;

enum EquipmentType {
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
	int buyGold;
	int sellGold;
	EquipmentType type;
	bool isEquipt;
public:

	Item();
	virtual void use(Player *p);
	virtual void use(Player *p, std::string *str);
	virtual void equip(Player *p) {}
	virtual void addBelongings(Player *p) {}
	virtual void remove(Player *p) {}
	std::string getName() { return this->name; }
	std::string getDescription() { return this->description; }
	bool getIsEquip() { return isEquipt; }
	EquipmentType getType() { return type; }
	void changeIsEquript();
	bool getCanEquip() { return canEquip; }
	bool getCanUse() { return canUse; }
	void setIsEquip(bool f) { isEquipt = f; }
	int getSellGold() { return this->sellGold; }
	int getBuyGold() { return this->buyGold; }
};

#endif
