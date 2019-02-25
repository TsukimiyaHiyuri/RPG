#include "Magic.h"

Magic::Magic()
{
}

void Magic::setStr(std::string *n, int damage, Enemy *e, Player *p) {
	*n += p->getName() + "は" + this->getName() + "を唱えた！\n";
	*n += e->getName() + "に" + std::to_string(damage) + "のダメージ！";
}

Fire::Fire() {
	this->name = "ファイア";
	this->learnLv = 1;
	this->type = AttackSolo;
	this->useMp = 5;
}

bool Fire::use(Player *player, Enemy *e, std::string *n) {
	if (player->getMp() >= this->useMp) {
		int damage = 20;
		e->damage(damage);
		player->addMp(-this->useMp);

		this->setStr(n, damage, e, player);

		return true;
	}
	return false;
}

Thunder::Thunder() {
	this->name = "サンダー";
	this->learnLv = 1;
	this->type = AttackAll;
	this->useMp = 7;
}

bool Thunder::use(Player *player, Enemy *e[], std::string *n) {
	if (player->getMp() >= this->useMp) {
		int damage = 15;
		for (int i = 0; i < MAXENEMYNUM; i++) {
			e[i]->damage(damage);
		}
		player->addMp(-this->useMp);

		*n += player->getName() + "は" + this->getName() + "を唱えた！\n";
		*n += "敵全体に" + std::to_string(damage) + "のダメージ！";

		return true;
	}
	return false;
}