#include "Mummy.h"
#include "DxLib.h"

Mummy::Mummy(int x, Sound *sound) {
	this->setStatus(
		"ƒ}ƒ~[",
		6,
		25,
		25,
		5,
		5,
		11,
		10,
		20,
		10
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
