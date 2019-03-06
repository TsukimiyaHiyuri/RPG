#include "Enemy.h"
#include "DxLib.h"


Enemy::Enemy()
{
}

void Enemy::setStatus(std::string n, int lv, int mh, int h, int mm, int m, int str, int def, long g, long ex) {
	this->status.name = n;
	this->status.lv = lv;
	this->status.maxHp = mh;
	this->status.hp = h;
	this->status.maxMp = mm;
	this->status.mp = m;
	this->status.str = str;
	this->status.def = def;
	this->status.gold = g;
	this->status.exp = ex;
}

void Enemy::drawGraphic() {
	DrawGraph(this->x - 50, CORDINATEY, this->graphic, true);
}

void Enemy::setCordinate(int x, int y) {
	this->x = x;
	this->y = y;
}

int Enemy::culculateDamage(Player *player) {
	int damage = this->status.str;
	damage += rand() % this->status.lv;

	damage = damage > player->getAllDef() ? damage - player->getAllDef() : 1;
	return damage;
}

// �o�g���E�B���h�E�p�̕������Ԃ�
std::string Enemy::getAttackString(int damage, Player *player) {
	std::string ans;
	ans += this->getName() + "�̍U��\n";
	ans += player->getName() + "��" + std::to_string(damage) + "�̃_���[�W";
	return ans;
}