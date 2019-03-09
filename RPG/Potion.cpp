#include "Potion.h"

Potion::Potion(){
	this->canEquip = false;
	this->canUse = true;
	this->str = 0;
	this->def = 0;
	this->name = "ポーション";
	this->description = "回復する";
	this->isEquipt = false;
	this->buyGold = 15;
	this->sellGold = 7;
	this->setDescription();
}

void Potion::use(Player *player) {
	if (player->getHp() + POTION > player->getMaxHp()) {
		player->setHp(player->getMaxHp());
	}
	else {
		player->setHp(player->getHp() + POTION);
	}
}

void Potion::use(Player *player, std::string *str) {
	this->use(player);
	*str += player->getName() + "は" + this->getName() + "を使った！\n";
	*str += player->getName() + "のHPが" + std::to_string(POTION) + "回復した！";
}

void Potion::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Potion());
	}
}