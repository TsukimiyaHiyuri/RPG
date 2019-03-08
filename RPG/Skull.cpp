#include "Skull.h"
#include "DxLib.h"

Skull::Skull(int x, Sound *sound) {
	this->setStatus(
		"ƒXƒJƒ‹",
		7,
		20,
		20,
		5,
		5,
		11,
		18,
		35,
		12
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Skull::loadGraphic() {
	this->graphic = LoadGraph("Enemy/skull.png");
}

std::string Skull::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Skull::getEnemy(int x) {
	return new Skull(x, this->sound);
}
