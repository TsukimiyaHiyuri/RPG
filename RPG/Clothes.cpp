#include "Clothes.h"

Clothes::Clothes() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 0;
	this->def = 2;
	this->name = "�z�̕�";
	this->description = "�����̕�";
	this->type = Armor;
	this->isEquipt = false;
	this->buyGold = 60;
	this->sellGold = 30;
	this->setDescription();
}

void Clothes::use(Player *p, std::string *str) {
	*str += p->getName() + "��" + this->getName() + "���g�����I\n";
	*str += "�����������N����Ȃ������I";
}

void Clothes::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Clothes());
	}
}

void Clothes::equip(Player *player) {
	player->setArmorStr(player->getArmorStr() + this->str);
	player->setArmorDef(player->getArmorDef() + this->def);
}

void Clothes::remove(Player *player) {
	player->setArmorStr(0);
	player->setArmorDef(0);
}