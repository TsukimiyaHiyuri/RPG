#include "Slime.h"
#include "DxLib.h"

Slime::Slime(int x) {
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
}

void Slime::loadGraphic() {
	this->graphic = LoadGraph("sraim.png");
}

std::string Slime::attack(Player *player) {
	int d = 2;
	player->damege(d);

	std::string ans;
	ans += this->getName() + "の攻撃\n";
	ans += player->getName() + "に" + std::to_string(d) + "のダメージ";
	return ans;
}

Enemy *Slime::getEnemy(int x) {
	return new Slime(x);
}