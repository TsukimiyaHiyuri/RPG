#include "Magic.h"

Magic::Magic() {

}

void Magic::setStr(std::string *n, int damage, Enemy *e, Player *p) {
	*n += p->getName() + "��" + this->getName() + "���������I\n";
	*n += e->getName() + "��" + std::to_string(damage) + "�̃_���[�W�I";
}

void Magic::setDiscription() {
	this->discription += "\n\n����MP: " + std::to_string(this->useMp);
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
		int damage = FIRE;
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
		int damage = THUNDER;
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
	this->useMp = 4;
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

MegFire::MegFire() {
	this->name = "���K�t�@�C�A";
	this->learnLv = 1;
	this->type = AttackSolo;
	this->useMp = 11;
	this->discription = "�G�P�̂ɑ�_���[�W";
	this->setDiscription();
}

bool MegFire::use(Player *player, Enemy *e, std::string *n) {
	if (player->getMp() >= this->useMp) {
		int damage = MEGFIRE;
		e->damage(damage);
		player->addMp(-this->useMp);

		this->setStr(n, damage, e, player);

		return true;
	}
	return false;
}

MegThunder::MegThunder() {
	this->name = "���K�T���_�[";
	this->learnLv = 1;
	this->type = AttackAll;
	this->useMp = 14;
	this->discription = "�G�S�̂ɑ�_���[�W";
	this->setDiscription();
}

bool MegThunder::use(Player *player, Enemy *e[], std::string *n) {
	if (player->getMp() >= this->useMp) {
		int damage = MEGTHUNDER;
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

MegCure::MegCure() {
	this->name = "���K�L���A�[";
	this->learnLv = 1;
	this->type = CureSolo;
	this->useMp = 8;
	this->discription = "��������";
	this->setDiscription();
}

bool MegCure::use(Player *player, std::string *n) {
	if (player->getMp() >= this->useMp) {
		player->addMp(-this->useMp);

		if (player->getHp() + MEGCURE <= player->getMaxHp()) {
			player->addHp(MEGCURE);
		}
		else {
			player->setHp(player->getMaxHp());
		}

		*n += player->getName() + "��" + this->getName() + "���������I\n";
		*n += player->getName() + "��HP��" + std::to_string(MEGCURE) + "�񕜂���";

		return true;
	}
	return false;
}

MaxCure::MaxCure() {
	this->name = "�}�b�N�X�L���A�[";
	this->learnLv = 1;
	this->type = CureSolo;
	this->useMp = 10;
	this->discription = "������S��";
	this->setDiscription();
}

bool MaxCure::use(Player *player, std::string *n) {
	if (player->getMp() >= this->useMp) {
		player->addMp(-this->useMp);

			player->setHp(player->getMaxHp());

		*n += player->getName() + "��" + this->getName() + "���������I\n";
		*n += player->getName() + "��HP���S�񕜂���";

		return true;
	}
	return false;
}