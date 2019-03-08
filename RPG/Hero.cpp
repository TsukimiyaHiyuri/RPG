#include "Hero.h"

Hero::Hero(Sound *sound) {
	// status‚Ì‰Šú’l
	this->status.name = "—EŽÒ";
	this->status.lv = 1;
	this->status.maxHp = 20;
	this->status.maxMp = 5;
	this->status.hp = 20;
	this->status.mp = 5;
	this->status.str = 7;
	this->status.def = 2;
	this->status.exp = 0;
	this->status.gold = 100;

	// ŠŽ•iŒn‚Ì‰Šú’l
	this->belongingsNum = 0;
	this->armor = false;
	this->weapon = false;
	this->weaponStr = 0;
	this->weaponDef = 0;
	this->armorStr = 0;
	this->armorDef = 0;

	// •`‰æŒn‚Ì‰Šú’l
	this->direction = UP;
	this->isMove = false;
	setPlayer(10, 10);
	this->moveX = 0, this->moveY = 0;
	loadGraphic();

	// –‚–@Œn‚Ì‰Šú’l
	this->learnMagicNum = 0;

	this->isSpeak = false;
	this->setLevelTable();

	this->sound = sound;
}

// ƒŒƒxƒ‹ƒe[ƒuƒ‹‚ðÝ’è‚·‚é
void Hero::setLevelTable() {
	this->levelTable[0] = 12;
	for (int i = 1; i < MAXLEVEL - 1; i++) {
		this->levelTable[i] = int(this->levelTable[i - 1] * 1.5) + this->levelTable[i - 1];
	}
}