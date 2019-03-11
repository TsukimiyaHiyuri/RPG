#include "Cassowary.h"
#include "DxLib.h"

Cassowary::Cassowary(int x, Sound *sound) {
	this->setStatus(
		"‚Ğ‚Æ‚­‚¢‚Ç‚è",
		13,
		50,
		50,
		10,
		10,
		22,
		14,
		75,
		25
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Cassowary::loadGraphic() {
	this->graphic = LoadGraph("Enemy/cassowary.png");
}

std::string Cassowary::attack(Player *player) {
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);;
}

Enemy *Cassowary::getEnemy(int x) {
	return new Cassowary(x, this->sound);
}