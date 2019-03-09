#include "Ether.h"

Ether::Ether() {
	this->canEquip = false;
	this->canUse = true;
	this->str = 0;
	this->def = 0;
	this->name = "�G�[�e����";
	this->description = "MP��15�񕜂���";
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
	*str += player->getName() + "��" + this->getName() + "���g�����I\n";
	*str += player->getName() + "��MP��" + std::to_string(ETHER) + "�񕜂����I";
}

void Ether::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Ether());
	}
}