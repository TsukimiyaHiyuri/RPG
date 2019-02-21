#include "Slime.h"
#include "DxLib.h"

Slime::Slime(int x) {
	this->setStatus(
		"ƒXƒ‰ƒCƒ€",
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
	int a;
	a = 0;
}

void Slime::attack(Player *player) {
	player->damege(2);
}