#include "BossEnemy.h"
#include "DxLib.h"

BossEnemy::BossEnemy(int x, Sound *sound) {
	this->setStatus(
		"�S�̋��l",
		10,
		500,
		500,
		100,
		100,
		35,
		40,
		10,
		10
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void BossEnemy::loadGraphic() {
	this->graphic = LoadGraph("Enemy/iron_man.png");
}

std::string BossEnemy::attack(Player *player) {
	// SE���Ȃ炷
	this->sound->playSE(DamageSE, true);

	// �_���[�W���v�Z����player�Ƀ_���[�W��^����
	int damage = this->culculateDamage(player);
	player->damage(damage);

	return this->getAttackString(damage, player);
}

Enemy *BossEnemy::getEnemy(int x) {
	return new BossEnemy(x, this->sound);
}