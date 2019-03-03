#include "Hero.h"

Hero::Hero(Sound *sound) {
	// status�̏����l
	this->status.name = "�E��";
	this->status.lv = 1;
	this->status.maxHp = 20;
	this->status.maxMp = 5;
	this->status.hp = 20;
	this->status.mp = 5;
	this->status.str = 10;
	this->status.def = 10;
	this->status.exp = 0;
	this->status.gold = 100;

	// �����i�n�̏����l
	this->belongingsNum = 0;
	this->armor = false;
	this->weapon = false;
	this->weaponStr = 0;
	this->weaponDef = 0;
	this->armorStr = 0;
	this->armorDef = 0;

	// �`��n�̏����l
	this->direction = UP;
	this->isMove = false;
	setPlayer(10, 10);
	this->moveX = 0, this->moveY = 0;
	loadGraphic();

	// ���@�n�̏����l
	this->learnMagicNum = 0;

	this->isSpeak = false;
	this->setLevelTable();

	this->sound = sound;
}

