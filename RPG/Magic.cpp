#include "Magic.h"

Magic::Magic() {

}

void Magic::setStr(std::string *n, int damage, Enemy *e, Player *p) {
	*n += p->getName() + "は" + this->getName() + "を唱えた！\n";
	*n += e->getName() + "に" + std::to_string(damage) + "のダメージ！";
}

void Magic::setDiscription() {
	this->discription += "\n\n消費MP: " + std::to_string(this->useMp);
}

Fire::Fire() {
	this->name = "ファイア";
	this->learnLv = 1;
	this->type = AttackSolo;
	this->useMp = 5;
	this->discription = "敵１体に小ダメージ";
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
	this->name = "サンダー";
	this->learnLv = 1;
	this->type = AttackAll;
	this->useMp = 7;
	this->discription = "敵全体に小ダメージ";
	this->setDiscription();
}

bool Thunder::use(Player *player, Enemy *e[], std::string *n) {
	if (player->getMp() >= this->useMp) {
		int damage = THUNDER;
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

Cure::Cure() {
	this->name = "キュアー";
	this->learnLv = 1;
	this->type = CureSolo;
	this->useMp = 4;
	this->discription = "自分を小回復";
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

		*n += player->getName() + "は" + this->getName() + "を唱えた！\n";
		*n += player->getName() + "のHPが" + std::to_string(CURE) + "回復した";

		return true;
	}
	return false;
}

MegFire::MegFire() {
	this->name = "メガファイア";
	this->learnLv = 1;
	this->type = AttackSolo;
	this->useMp = 11;
	this->discription = "敵１体に大ダメージ";
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
	this->name = "メガサンダー";
	this->learnLv = 1;
	this->type = AttackAll;
	this->useMp = 14;
	this->discription = "敵全体に大ダメージ";
	this->setDiscription();
}

bool MegThunder::use(Player *player, Enemy *e[], std::string *n) {
	if (player->getMp() >= this->useMp) {
		int damage = MEGTHUNDER;
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

MegCure::MegCure() {
	this->name = "メガキュアー";
	this->learnLv = 1;
	this->type = CureSolo;
	this->useMp = 8;
	this->discription = "自分を大回復";
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

		*n += player->getName() + "は" + this->getName() + "を唱えた！\n";
		*n += player->getName() + "のHPが" + std::to_string(MEGCURE) + "回復した";

		return true;
	}
	return false;
}

MaxCure::MaxCure() {
	this->name = "マックスキュアー";
	this->learnLv = 1;
	this->type = CureSolo;
	this->useMp = 10;
	this->discription = "自分を全回復";
	this->setDiscription();
}

bool MaxCure::use(Player *player, std::string *n) {
	if (player->getMp() >= this->useMp) {
		player->addMp(-this->useMp);

			player->setHp(player->getMaxHp());

		*n += player->getName() + "は" + this->getName() + "を唱えた！\n";
		*n += player->getName() + "のHPが全回復した";

		return true;
	}
	return false;
}