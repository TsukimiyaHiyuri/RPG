#include "BossEnemy.h"
#include "DxLib.h"

BossEnemy::BossEnemy(int x, Sound *sound) {
	this->setStatus(
		"鉄の巨人",
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
	this->graphic = LoadGraph("iron_man.png");
}

std::string BossEnemy::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int d = this->status.str < player->getAllDef() ? 1 : this->status.str - player->getAllDef();
	player->damege(d);

	std::string ans;
	ans += this->getName() + "の攻撃\n";
	ans += player->getName() + "に" + std::to_string(d) + "のダメージ！";
	return ans;
}

Enemy *BossEnemy::getEnemy(int x) {
	return new BossEnemy(x, this->sound);
}