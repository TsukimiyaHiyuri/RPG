#include "Dragon.h"
#include "DxLib.h"

Dragon::Dragon(int x, Sound *sound) {
	this->setStatus(
		"ƒhƒ‰ƒSƒ“",
		16,
		75,
		75,
		10,
		10,
		24,
		18,
		90,
		28
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Dragon::loadGraphic() {
	this->graphic = LoadGraph("Enemy/dragon_f.png");
}

std::string Dragon::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Dragon::getEnemy(int x) {
	return new Dragon(x, this->sound);
}