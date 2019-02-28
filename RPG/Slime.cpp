#include "Slime.h"
#include "DxLib.h"

Slime::Slime(int x) {
	this->setStatus(
		"�X���C��",
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
	ans += this->getName() + "�̍U��\n";
	ans += player->getName() + "��" + std::to_string(d) + "�̃_���[�W";
	return ans;
}

Enemy *Slime::getEnemy(int x) {
	return new Slime(x);
}