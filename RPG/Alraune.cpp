#include "Alraune.h"
#include "DxLib.h"

Alraune::Alraune(int x, Sound *sound) {
	this->setStatus(
		"アルラウネ",
		1,
		6,
		6,
		3,
		3,
		7,
		2,
		6,
		3
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Alraune::loadGraphic() {
	this->graphic = LoadGraph("Enemy/alraune.png");
}

std::string Alraune::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Alraune::getEnemy(int x) {
	return new Alraune(x, this->sound);
}