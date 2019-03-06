#include "Bat.h"
#include "DxLib.h"

Bat::Bat(int x, Sound *sound) {
	this->setStatus(
		"‚±‚¤‚à‚è",
		2,
		14,
		14,
		5,
		5,
		4,
		3,
		4,
		4
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Bat::loadGraphic() {
	this->graphic = LoadGraph("bat.png");
}

std::string Bat::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Bat::getEnemy(int x) {
	return new Bat(x, this->sound);
}