#include "Mummy.h"
#include "DxLib.h"

Mummy::Mummy(int x, Sound *sound) {
	this->setStatus(
		"マミー",
		6,
		35,
		35,
		5,
		5,
		16,
		9,
		30,
		14
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Mummy::loadGraphic() {
	this->graphic = LoadGraph("Enemy/mummy.png");
}

std::string Mummy::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Mummy::getEnemy(int x) {
	return new Mummy(x, this->sound);
}
