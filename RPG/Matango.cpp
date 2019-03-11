#include "Matango.h"
#include "DxLib.h"

Matango::Matango(int x, Sound *sound) {
	this->setStatus(
		"ƒ}ƒ^ƒ“ƒS",
		2,
		10,
		10,
		5,
		5,
		8,
		2,
		10,
		5
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Matango::loadGraphic() {
	this->graphic = LoadGraph("Enemy/kinoko.png");
}

std::string Matango::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Matango::getEnemy(int x) {
	return new Matango(x, this->sound);
}
