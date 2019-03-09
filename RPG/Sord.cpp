#include "Sord.h"

Sord::Sord() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 15;
	this->def = 0;
	this->name = "剣";
	this->description = "一般的な剣";
	this->type = Weapon;
	this->isEquipt = false;
	this->buyGold = 15;
	this->sellGold = 7;
	this->setDescription();
}

void Sord::use(Player *p, std::string *str) {
	*str += p->getName() + "は" + this->getName() + "を使った！\n";
	*str += "しかし何も起こらなかった！";
}


void Sord::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Sord());
	}
}

void Sord::equip(Player *player) {
	player->setWeaponStr(player->getWeaponStr() + this->str);
	player->setWeaponDef(player->getWeaponDef() + this->def);
}

void Sord::remove(Player *player) {
	player->setWeaponStr(0);
	player->setWeaponDef(0);
}