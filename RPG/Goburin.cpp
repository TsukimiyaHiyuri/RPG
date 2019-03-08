#include "Goburin.h"
#include "DxLib.h"

Goburin::Goburin(int x, Sound *sound) {
	this->setStatus(
		"ƒSƒuƒŠƒ“",
		5,
		30,
		30,
		5,
		5,
		13,
		10,
		20,
		10
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