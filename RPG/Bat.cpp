#include "Bat.h"
#include "DxLib.h"

Bat::Bat(int x) {
	this->setStatus(
		"こうもり",
		1,
		20,
		20,
		5,
		5,
		4,
		3,
		4,
		4
	);
	this->loadGraphic();
	this->setCordinate(x, CORDINATEY);
}

void Bat::loadGraphic() {
	this->graphic = LoadGraph("bat.png");
}

std::string Bat::attack(Player *player) {
	int d = 4;
	player->damege(d);

	std::string ans;
	ans += this->getName() + "の攻撃\n";
	ans += player->getName() + "に" + std::to_string(d) + "のダメージ";
	return ans;
}

Enemy *Bat::getEnemy(int x) {
	return new Bat(x);
}