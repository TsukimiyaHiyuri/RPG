#include "Stick.h"

Stick::Stick() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 4;
	this->def = 0;
	this->name = "木の棒";
	this->description = "ただの棒きれ";
	this->type = Weapon;
	this->isEquipt = false;
	this->buyGold = 70;
	this->sellGold = 35;
	this->setDescription();
}

void Stick::use(Player *p, std::string *str) {
	*str += p->getName() + "は" + this->getName() + "を使った！\n";
	*str += "しかし何も起こらなかった！";
}


void Stick::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Stick());
	}
}

void Stick::equip(Player *player) {
	player->setWeaponStr(player->getWeaponStr() + this->str);
	player->setWeaponDef(player->getWeaponDef() + this->def);
}

void Stick::remove(Player *player) {
	player->setWeaponStr(0);
	player->setWeaponDef(0);
}