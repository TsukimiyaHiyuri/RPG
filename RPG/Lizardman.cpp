#include "Lizardman.h"
#include "DxLib.h"

Lizardman::Lizardman(int x, Sound *sound) {
	this->setStatus(
		"リザードマン",
		8,
		35,
		35,
		10,
		10,
		15,
		15,
		40,
		16
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Lizardman::loadGraphic() {
	this->graphic = LoadGraph("Enemy/lizardman.png");
}

std::string Lizardman::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Lizardman::getEnemy(int x) {
	return new Lizardman(x, this->sound);
}