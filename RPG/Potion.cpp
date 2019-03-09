#include "Potion.h"

Potion::Potion(){
	this->canEquip = false;
	this->canUse = true;
	this->str = 0;
	this->def = 0;
	this->name = "�|�[�V����";
	this->description = "�񕜂���";
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
	*str += player->getName() + "��" + this->getName() + "���g�����I\n";
	*str += player->getName() + "��HP��" + std::to_string(POTION) + "�񕜂����I";
}

void Potion::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Potion());
	}
}