#include "Magic.h"

Magic::Magic() {

}

void Magic::setStr(std::string *n, int damage, Enemy *e, Player *p) {
	*n += p->getName() + "��" + this->getName() + "���������I\n";
	*n += e->getName() + "��" + std::to_string(damage) + "�̃_���[�W�I";
}

void Magic::setDiscription() {
	this->discription += "\n����MP: " + std::to_string(this->useMp);
}

Fire::Fire() {
	this->name = "�t�@�C�A";
	this->learnLv = 1;
	this->type = AttackSolo;
	this->useMp = 5;
	this->discription = "�G�P�̂ɏ��_���[�W";
	this->setDiscription();
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
	this->discription = "�G�S�̂ɏ��_���[�W";
	this->setDiscription();
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

Cure::Cure() {
	this->name = "�L���A�[";
	this->learnLv = 1;
	this->type = CureSolo;
	this->useMp = 5;
	this->discription = "����������";
	this->setDiscription();
}

bool Cure::use(Player *player, std::string *n) {
	if (player->getMp() >= this->useMp) {
		player->addMp(-this->useMp);

		if (player->getHp() + CURE <= player->getMaxHp()) {
			player->addHp(CURE);
		}
		else {
			player->setHp(player->getMaxHp());
		}

		*n += player->getName() + "��" + this->getName() + "���������I\n";
		*n += player->getName() + "��HP��" + std::to_string(CURE) + "�񕜂���";

		return true;
	}
	return false;
}