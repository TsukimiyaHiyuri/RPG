#include "Mummy.h"
#include "DxLib.h"

Mummy::Mummy(int x, Sound *sound) {
	this->setStatus(
		"ƒ}ƒ~[",
		6,
		35,
		35,
		5,
		5,
		15,
		9,
		30,
		20
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Mummy::loadGraphic() {
	this->graphic = LoadGraph("Enemy/mummy.png");
}

std::string Mummy::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Mummy::getEnemy(int x) {
	return new Mummy(x, this->sound);
}
