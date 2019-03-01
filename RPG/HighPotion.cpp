#include "HighPotion.h"

HighPotion::HighPotion() {
	this->canEquip = false;
	this->canUse = true;
	this->name = "ハイポーション";
	this->description = "大きく回復する";
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

void HighPotion::use(Player *player, std::string *str) {
	this->use(player);
	*str += player->getName() + "は" + this->getName() + "を使った！\n";
	*str += player->getName() + "のHPが" + std::to_string(HIGHPOTION) + "回復した！";
}


// 主人公の持ち物に追加
void HighPotion::addBelongings(Player *player) {
	if (player->getBelongingsNum() < MAXBELONGINGS) {
		player->addBelongings(new HighPotion());
	}
}