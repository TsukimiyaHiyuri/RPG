#include "Magic.h"

Magic::Magic()
{
}

Fire::Fire() {
	this->name = "ファイア";
	this->learnLv = 1;
	this->type = AttackSolo;
	this->useMp = 5;
}

bool Fire::use(Player *player, Enemy *e) {
	if (player->getMp() >= this->useMp) {
		e->damage(20);
		player->addMp(-this->useMp);
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

bool Thunder::use(Player *player, Enemy *e[]) {
	if (player->getMp() >= this->useMp) {
		for (int i = 0; i < MAXENEMYNUM; i++) {
			e[i]->damage(15);
		}
		player->addMp(-this->useMp);
		return true;
	}
	return false;
}