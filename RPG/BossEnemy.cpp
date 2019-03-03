#include "BossEnemy.h"
#include "DxLib.h"

BossEnemy::BossEnemy(int x, Sound *sound) {
	this->setStatus(
		"“S‚Ì‹l",
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
	// SE‚ğ‚È‚ç‚·
	this->sound->playSE(DamageSE, true);

	int d = this->status.str < player->getAllDef() ? 1 : this->status.str - player->getAllDef();
	player->damege(d);

	std::string ans;
	ans += this->getName() + "‚ÌUŒ‚\n";
	ans += player->getName() + "‚É" + std::to_string(d) + "‚Ìƒ_ƒ[ƒWI";
	return ans;
}

Enemy *BossEnemy::getEnemy(int x) {
	return new BossEnemy(x, this->sound);
}