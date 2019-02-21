#include "HighPotion.h"

HighPotion::HighPotion() {
	this->canEquip = false;
	this->canUse = true;
	this->name = "ハイポーション";
	this->description = "大きく回復する";
	this->isEquipt = false;
}

void HighPotion::use(Player *player) {
	if (player->getHp() + HIGHPOTION > player->getMaxHp()) {
		player->setHp(player->getMaxHp());
	}
	else {
		player->setHp(player->getHp() + HIGHPOTION);
	}
}

// 主人公の持ち物に追加
void HighPotion::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new HighPotion());
		player->setBelongingsNum(player->getBelongingsNum() + 1);
	}
}