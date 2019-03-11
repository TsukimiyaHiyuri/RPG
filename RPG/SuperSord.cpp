#include "SuperSord.h"

SuperSord::SuperSord() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 13;
	this->def = 1;
	this->name = "�b����ꂽ��";
	this->description = "�ƕ��̌�";
	this->type = Weapon;
	this->isEquipt = false;
	this->buyGold = 1200;
	this->sellGold = 600;
	this->setDescription();
}

void SuperSord::use(Player *p, std::string *str) {
	*str += p->getName() + "��" + this->getName() + "���g�����I\n";
	*str += "�����������N����Ȃ������I";
}


void SuperSord::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new SuperSord());
	}
}

void SuperSord::equip(Player *player) {
	player->setWeaponStr(player->getWeaponStr() + this->str);
	player->setWeaponDef(player->getWeaponDef() + this->def);
}

void SuperSord::remove(Player *player) {
	player->setWeaponStr(0);
	player->setWeaponDef(0);
}