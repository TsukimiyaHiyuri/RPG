#include "Goburin.h"
#include "DxLib.h"

Goburin::Goburin(int x, Sound *sound) {
	this->setStatus(
		"ゴブリン",
		5,
		35,
		35,
		5,
		5,
		18,
		8,
		35,
		15
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Goburin::loadGraphic() {
	this->graphic = LoadGraph("Enemy/goburin.png");
}

std::string Goburin::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Goburin::getEnemy(int x) {
	return new Goburin(x, this->sound);
}