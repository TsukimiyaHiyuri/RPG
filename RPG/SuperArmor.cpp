#include "SuperArmor.h"

SuperArmor::SuperArmor() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 1;
	this->def = 8;
	this->name = "�b����ꂽ�Z";
	this->description = "�������Z";
	this->type = Armor;
	this->isEquipt = false;
	this->buyGold = 1000;
	this->sellGold = 500;
	this->setDescription();
}

void SuperArmor::use(Player *p, std::string *str) {
	*str += p->getName() + "��" + this->getName() + "���g�����I\n";
	*str += "�����������N����Ȃ������I";
}

void SuperArmor::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new SuperArmor());
	}
}

void SuperArmor::equip(Player *player) {
	player->setArmorStr(player->getArmorStr() + this->str);
	player->setArmorDef(player->getArmorDef() + this->def);
}

void SuperArmor::remove(Player *player) {
	player->setArmorStr(0);
	player->setArmorDef(0);
}