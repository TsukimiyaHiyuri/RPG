#include "Potion.h"

Potion::Potion(){
	this->canEquip = false;
	this->canUse = true;
	this->str = 0;
	this->def = 0;
	this->name = "ƒ|[ƒVƒ‡ƒ“";
	this->description = "‰ñ•œ‚·‚é";
	this->isEquipt = false;
	this->buyGold = 15;
	this->sellGold = 7;
}

void Potion::use(Player *player) {
	if (player->getHp() + POTION > player->getMaxHp()) {
		player->setHp(player->getMaxHp());
	}
	else {
		player->setHp(player->getHp() + POTION);
	}
}

void Potion::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Potion());
	}
}