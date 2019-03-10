#include "Alraune.h"
#include "DxLib.h"

Alraune::Alraune(int x, Sound *sound) {
	this->setStatus(
		"�A�����E�l",
		1,
		6,
		6,
		3,
		3,
		6,
		2,
		5,
		2
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Alraune::loadGraphic() {
	this->graphic = LoadGraph("Enemy/alraune.png");
}

std::string Alraune::attack(Player *player) {
	// SE���Ȃ炷
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Alraune::getEnemy(int x) {
	return new Alraune(x, this->sound);
}