#include "Goburin.h"
#include "DxLib.h"

Goburin::Goburin(int x, Sound *sound) {
	this->setStatus(
		"ƒSƒuƒŠƒ“",
		5,
		35,
		35,
		5,
		5,
		15,
		8,
		40,
		20
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Goburin::loadGraphic() {
	this->graphic = LoadGraph("Enemy/goburin.png");
}

std::string Goburin::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Goburin::getEnemy(int x) {
	return new Goburin(x, this->sound);
}