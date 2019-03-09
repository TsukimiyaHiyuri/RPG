#include "Stick.h"

Stick::Stick() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 4;
	this->def = 0;
	this->name = "�؂̖_";
	this->description = "�����̖_����";
	this->type = Weapon;
	this->isEquipt = false;
	this->buyGold = 70;
	this->sellGold = 35;
	this->setDescription();
}

void Stick::use(Player *p, std::string *str) {
	*str += p->getName() + "��" + this->getName() + "���g�����I\n";
	*str += "�����������N����Ȃ������I";
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