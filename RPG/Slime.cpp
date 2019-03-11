#include "Slime.h"
#include "DxLib.h"

Slime::Slime(int x, Sound *sound) {
	this->setStatus(
		"スライム",
		1,
		8,
		8,
		5,
		5,
		6,
		2,
		4,
		2
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Slime::loadGraphic() {
	this->graphic = LoadGraph("Enemy/sraim.png");
}

std::string Slime::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	// ダメージを計算してplayerにダメージを与える
	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);
}

Enemy *Slime::getEnemy(int x) {
	return new Slime(x, this->sound);
}