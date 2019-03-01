#include "Slime.h"
#include "DxLib.h"

Slime::Slime(int x, Sound *sound) {
	this->setStatus(
		"スライム",
		1,
		15,
		15,
		5,
		5,
		2,
		2,
		2,
		2
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
	this->sound = sound;
}

void Slime::loadGraphic() {
	this->graphic = LoadGraph("sraim.png");
}

std::string Slime::attack(Player *player) {
	// SEをならす
	this->sound->playSE(DamageSE, true);

	int d = this->status.str < player->getAllDef() ? 1 : this->status.str - player->getAllDef();
	player->damege(d);

	std::string ans;
	ans += this->getName() + "の攻撃\n";
	ans += player->getName() + "に" + std::to_string(d) + "のダメージ";
	return ans;
}

Enemy *Slime::getEnemy(int x) {
	return new Slime(x, this->sound);
}