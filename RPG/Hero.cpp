#include "Hero.h"

Hero::Hero(Sound *sound) {
	// statusの初期値
	this->status.name = "勇者";
	this->status.lv = 1;
	this->status.maxHp = 20;
	this->status.maxMp = 5;
	this->status.hp = 20;
	this->status.mp = 5;
	this->status.str = 7;
	this->status.def = 2;
	this->status.exp = 0;
	this->status.gold = 100;

	// 所持品系の初期値
	this->belongingsNum = 0;
	this->armor = false;
	this->weapon = false;
	this->weaponStr = 0;
	this->weaponDef = 0;
	this->armorStr = 0;
	this->armorDef = 0;

	// 描画系の初期値
	this->direction = UP;
	this->isMove = false;
	setPlayer(10, 10);
	this->moveX = 0, this->moveY = 0;
	loadGraphic();

	// 魔法系の初期値
	this->learnMagicNum = 0;

	this->isSpeak = false;
	this->setLevelTable();

	this->sound = sound;
}

// レベルテーブルを設定する
void Hero::setLevelTable() {
	this->levelTable[0] = 12;
	for (int i = 1; i < MAXLEVEL - 1; i++) {
		this->levelTable[i] = int(this->levelTable[i - 1] * 1.5) + this->levelTable[i - 1];
	}
}

// レベルアップ時の関数
void Hero::levelUp(std::string *s) {
	if (this->status.lv < MAXLEVEL) {
		if (this->status.exp >= this->levelTable[this->status.lv - 1]) {
			// レベルアップのSEをならす
			this->sound->playSE(LevelUpSE, false);

			// レベルをひとつあげる
			this->status.lv++;

			// 各ステータスを上げる
			this->addMaxHp(15);
			this->addMaxMp(5);
			this->addStr(3);
			this->addDef(2);
			this->setHp(this->getMaxHp());
			this->setMp(this->getMaxMp());

			*s += this->getName() + "は Lv" + std::to_string(this->getLv()) + " になった！\n";

			// レベルによって魔法を習得
			switch (this->getLv()) {
			case 2:
				this->learnMagic(new Cure());
				*s += this->magic[this->learnMagicNum - 1]->getName() + "の魔法を習得した！\n";
				break;
			case 5:
				this->learnMagic(new Thunder());
				*s += this->magic[this->learnMagicNum - 1]->getName() + "の魔法を習得した！\n";
				break;
			}
		}
	}
}