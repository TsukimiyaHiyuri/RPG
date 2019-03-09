#include "Ether.h"

Ether::Ether() {
	this->canEquip = false;
	this->canUse = true;
	this->str = 0;
	this->def = 0;
	this->name = "エーテル水";
	this->description = "MPを15回復する";
	this->isEquipt = false;
	this->buyGold = 30;
	this->sellGold = 15;
	this->setDescription();
}

void Ether::use(Player *player) {
	if (player->getMp() + ETHER > player->getMaxMp()) {
		player->setMp(player->getMaxMp());
	}
	else {
		player->setMp(player->getMp() + ETHER);
	}
}

void Ether::use(Player *player, std::string *str) {
	this->use(player);
	*str += player->getName() + "は" + this->getName() + "を使った！\n";
	*str += player->getName() + "のMPが" + std::to_string(ETHER) + "回復した！";
}

void Ether::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Ether());
	}
}