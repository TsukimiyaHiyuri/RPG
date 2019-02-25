#include "Magic.h"

Magic::Magic()
{
}

void Magic::setStr(std::string *n, int damage, Enemy *e, Player *p) {
	*n += p->getName() + "��" + this->getName() + "���������I\n";
	*n += e->getName() + "��" + std::to_string(damage) + "�̃_���[�W�I";
}

Fire::Fire() {
	this->name = "�t�@�C�A";
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
	this->name = "�T���_�[";
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

		*n += player->getName() + "��" + this->getName() + "���������I\n";
		*n += "�G�S�̂�" + std::to_string(damage) + "�̃_���[�W�I";

		return true;
	}
	return false;
}