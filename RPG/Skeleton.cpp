#include "Skeleton.h"
#include "DxLib.h"

Skeleton::Skeleton(int x, Sound *sound) {
	this->setStatus(
		"ƒXƒPƒ‹ƒgƒ“",
		10,
		60,
		60,
		5,
		5,
		24,
		20,
		100,
		30
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Skeleton::loadGraphic() {
	this->graphic = LoadGraph("Enemy/skeleton.png");
}

std::string Skeleton::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Skeleton::getEnemy(int x) {
	return new Skeleton(x, this->sound);
}