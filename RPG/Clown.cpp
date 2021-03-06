#include "Clown.h"
#include "DxLib.h"

Clown::Clown(int x, Sound *sound) {
	this->setStatus(
		"クラウン",
		14,
		50,
		50,
		10,
		10,
		22,
		15,
		80,
		28
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Clown::loadGraphic() {
	this->graphic = LoadGraph("Enemy/clown.png");
}

std::string Clown::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Clown::getEnemy(int x) {
	return new Clown(x, this->sound);
}