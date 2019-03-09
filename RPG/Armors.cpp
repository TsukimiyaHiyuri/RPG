#include "Armors.h"

Armors::Armors() {
	this->canEquip = true;
	this->canUse = false;
	this->str = 0;
	this->def = 15;
	this->name = "�Z";
	this->description = "��ʓI�ȊZ";
	this->type = Armor;
	this->isEquipt = false;
	this->buyGold = 15;
	this->sellGold = 7;
	this->setDescription();
}

void Armors::use(Player *p, std::string *str) {
	*str += p->getName() + "��" + this->getName() + "���g�����I\n";
	*str += "�����������N����Ȃ������I";
}

void Armors::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new Armors());
	}
}

void Armors::equip(Player *player) {
	player->setArmorStr(player->getArmorStr() + this->str);
	player->setArmorDef(player->getArmorDef() + this->def);
}

void Armors::remove(Player *player) {
	player->setArmorStr(0);
	player->setArmorDef(0);
}