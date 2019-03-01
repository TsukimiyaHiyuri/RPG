#include "Bat.h"
#include "DxLib.h"

Bat::Bat(int x, Sound *sound) {
	this->setStatus(
		"��������",
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
	this->sound = sound;
}

void Bat::loadGraphic() {
	this->graphic = LoadGraph("bat.png");
}

std::string Bat::attack(Player *player) {
	// SE���Ȃ炷
	this->sound->playSE(DamageSE, true);

	int d = 4;
	player->damege(d);

	std::string ans;
	ans += this->getName() + "�̍U��\n";
	ans += player->getName() + "��" + std::to_string(d) + "�̃_���[�W";
	return ans;
}

Enemy *Bat::getEnemy(int x) {
	return new Bat(x, this->sound);
}