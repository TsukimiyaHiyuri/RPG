#include "HighPotion.h"

HighPotion::HighPotion() {
	this->canEquip = false;
	this->canUse = true;
	this->name = "�n�C�|�[�V����";
	this->description = "�傫���񕜂���";
	this->isEquipt = false;
	this->buyGold = 15;
	this->sellGold = 7;
}

void HighPotion::use(Player *player) {
	if (player->getHp() + HIGHPOTION > player->getMaxHp()) {
		player->setHp(player->getMaxHp());
	}
	else {
		player->setHp(player->getHp() + HIGHPOTION);
	}
}

// ��l���̎������ɒǉ�
void HighPotion::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new HighPotion());
	}
}