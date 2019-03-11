#include "Hero.h"
#include "DxLib.h"

Hero::Hero(Sound *sound) {
	// status�̏����l
	this->status.name = "�E��";
	this->status.lv = 1;
	this->status.maxHp = 30;
	this->status.maxMp = 10;
	this->status.hp = 30;
	this->status.mp = 10;
	this->status.str = 1000;
	this->status.def = 4;
	this->status.exp = 1000;
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
	this->setPlayer(12, 14, UP);
	this->moveX = 0, this->moveY = 0;
	loadGraphic();

	// ���@�n�̏����l
	this->learnMagicNum = 0;

	this->isSpeak = false;
	this->setLevelTable();

	this->sound = sound;
}

// ��l���̃}�b�v�`�b�v�����[�h
void Hero::loadGraphic() {
	LoadDivGraph("Character/pipo-charachip001a.png", 3 * 4, 3, 4, 32, 32, this->graphic);//�摜�𕪊�����image�z��ɕۑ�
}

// ���x���e�[�u����ݒ肷��
void Hero::setLevelTable() {
	this->levelTable[0] = 12;
	for (int i = 1; i < MAXLEVEL - 1; i++) {
		this->levelTable[i] = this->levelTable[i - 1] + int(this->levelTable[0] * 1.3 * i);
	}
}

// ���x���A�b�v���̊֐�
void Hero::levelUp(std::string *s) {
	if (this->status.lv < MAXLEVEL) {
		int originLv = this->getLv();
		bool isLevelUp = false;
		while (this->status.exp >= this->levelTable[this->status.lv - 1]) {
			// ���x���A�b�v��SE���Ȃ炷
			this->sound->playSE(LevelUpSE, false);

			// ���x�����ЂƂ�����
			this->status.lv++;

			// �e�X�e�[�^�X���グ��
			this->addMaxHp(7);
			this->addMaxMp(3);
			this->addStr(2);
			this->addDef(1);
			this->setHp(this->getMaxHp());
			this->setMp(this->getMaxMp());

			isLevelUp = true;
		}

		if(isLevelUp) {
			*s += this->getName() + "�� Lv" + std::to_string(this->getLv()) + " �ɂȂ����I\n";

			// ���x���ɂ���Ė��@���K��
			while (originLv < this->getLv()) {
				switch (++originLv) {
				case 2:
					this->learnMagic(new Cure());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;

				case 4:
					this->learnMagic(new Fire());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;

				case 6:
					this->learnMagic(new Thunder());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;

				case 8:
					this->learnMagic(new MegCure());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;

				case 10:
					this->learnMagic(new MegThunder());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;

				case 12:
					this->learnMagic(new MegFire());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;

				case 14:
					this->learnMagic(new MaxCure());
					*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
					break;
				}
			}
		}
	}
}