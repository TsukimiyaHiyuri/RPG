#include "Sord.h"

Sord::Sord() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 15;
	this->def = 0;
	this->name = "Œ•";
	this->description = "ˆê”Ê“I‚ÈŒ•";
	this->type = Weapon;
	this->isEquipt = false;
	this->buyGold = 15;
	this->sellGold = 7;
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