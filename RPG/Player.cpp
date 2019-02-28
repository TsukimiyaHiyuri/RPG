#include "Player.h"
#include "Dim.h"
#include "DxLib.h"
#include "Map.h"
#include "Key.h"

int moveX, moveY;
Player *player[PLAYERNUM];

Player::Player() {
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
	moveX = 0, moveY = 0;
	loadGraphic();

	// ���@�n�̏����l
	this->learnMagicNum = 0;

	this->isSpeak = false;
	this->setLevelTable();
}

// �e�L�[���͂ɂ��������Ĉړ��������擾
void Player::move() {
	if (Key[KEY_INPUT_RIGHT] >= 1 && !this->isMove) {
		moveX += 1;
		this->direction = RIGHT;
		this->isMove = true;
	}
	if (Key[KEY_INPUT_LEFT] >= 1 && !this->isMove) {
		moveX -= 1;
		this->direction = LEFT;
		this->isMove = true;
	}
	if (Key[KEY_INPUT_DOWN] >= 1 && !this->isMove) {
		moveY += 1;
		this->direction = DOWN;
		this->isMove = true;
	}
	if (Key[KEY_INPUT_UP] >= 1 && !this->isMove) {
		moveY -= 1;
		this->direction = UP;
		this->isMove = true;
	}
}

void Player::stop() {
	moveX = 0, moveY = 0;
	this->isMove = false;
}

// ��l���̃}�b�v�`�b�v�����[�h
void Player::loadGraphic() {
	LoadDivGraph("���s�h�b�g�L����.bmp", 3 * 4, 3, 4, 32, 32, this->graphic);//�摜�𕪊�����image�z��ɕۑ�
}

// ��l���̕`��
void Player::drawHero(int *moveCounter) {
	// �����Ă�Ƃ��̓A�j���[�V����
	if (this->isMove) {
		if (*moveCounter < MOVE_FRAME / 3) {
			DrawGraph(320, 220, graphic[this->direction - 1], TRUE);
		}
		else if (*moveCounter > MOVE_FRAME - (MOVE_FRAME / 3)) {
			DrawGraph(320, 220, graphic[this->direction + 1], TRUE);
		}
		else {
			DrawGraph(320, 220, graphic[this->direction], TRUE);
		}
	}
	else {
		DrawGraph(320, 220, graphic[this->direction], TRUE);
	}
}

// �X�N���[���ʂ��v�Z���ăX�N���[���I�����Ƀv���C���[�̍��W���ړ�
void Player::scroll(int *MoveCounter, int *ScrollX, int *ScrollY, int *EncountNum) {
	if(this->isMove) {
		*MoveCounter += 1;

		// �ړ��������I���������~���ɂ���
		if (*MoveCounter == MOVE_FRAME) {
			isMove = false;

			// �v���C���[�̈ʒu��ύX����
			this->position.x += moveX;
			this->position.y += moveY;

			moveX = 0, moveY = 0;
			*MoveCounter = 0;

			*EncountNum += 1;

			// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
			*ScrollX = 0;
			*ScrollY = 0;
		}
		else {
			// �o�ߎ��Ԃ���X�N���[���ʂ��Z�o����
			*ScrollX = -(moveX * MAP_SIZE * *MoveCounter / MOVE_FRAME);
			*ScrollY = -(moveY * MAP_SIZE * *MoveCounter / MOVE_FRAME);
		}
	}
}

// �v���C���[�̍��W�̃Z�b�^
void Player::setPlayer(int x, int y) {
	this->position.x = x;
	this->position.y = y;
}

// �����i�������ς�����Ȃ�����������̃A�C�e��������������
void Player::addBelongings(Item *item) {
  	if (this->getBelongingsNum() < MAXBELONGINGS) {
		this->belongings[this->getBelongingsNum()] = item;
		this->setBelongingsNum(this->getBelongingsNum() + 1);
	}
}

bool Player::sellItem(int n) {
	if (this->getBelongingsNum() > 0 && !this->belongings[n]->getIsEquip()) {
		this->status.gold += this->belongings[n]->getSellGold();
		this->throwItem(n);
		return true;
	}
	return false;
}

void Player::buyItem(Item *item) {
	if (this->status.gold >= item->getBuyGold() && this->getBelongingsNum() < MAXBELONGINGS) {
		this->status.gold -= item->getBuyGold();
		item->addBelongings(this);
	}
}

// �w�肳�ꂽ�ԍ��̃A�C�e�����w�肳�ꂽ�v���C���[�Ɏg�p����
// �g�p�����A�C�e���͂Ȃ��Ȃ�
void Player::useItem(int n, Player *p) {
	if (!this->belongings[n]->getCanEquip()) {
		this->belongings[n]->use(p);

		this->throwItem(n);
	}
}

void Player::throwItem(int n) {
	if (!this->belongings[n]->getIsEquip()) {
		for (int i = n; i < MAXBELONGINGS - 1; i++) {
			this->belongings[i] = this->belongings[i + 1];
		}

		this->setBelongingsNum(this->getBelongingsNum() - 1);
	}
}

void Player::passItem(int n, Player *to) {
	if (to->getBelongingsNum() < MAXBELONGINGS && !this->belongings[n]->getIsEquip()) {
		to->addBelongings(this->belongings[n]);
		this->throwItem(n);
		to->belongingsNum++;
	}
}

void Player::equipItem(int n, Player *from) {
	if (!this->belongings[n]->getCanUse()) {
		if (this->belongings[n]->getIsEquip()) {
			this->belongings[n]->changeIsEquript();
			this->belongings[n]->remove(this);
			if (this->belongings[n]->getType() == Weapon) {
				this->weapon = false;
			}
			else if(this->belongings[n]->getType() == Armor) {
				this->armor = false;
			}
		}
		else if (this->weapon && this->belongings[n]->getType() == Weapon) {
			for (int i = 0; i < this->belongingsNum; i++) {
				if (this->belongings[i]->getIsEquip() && this->belongings[i]->getType() == Weapon) {
					this->belongings[i]->changeIsEquript();
					this->belongings[i]->remove(this);
				}
			}
			this->belongings[n]->changeIsEquript();
			this->belongings[n]->equip(this);
		}
		else if (this->armor && this->belongings[n]->getType() == Armor) {
			for (int i = 0; i < this->belongingsNum; i++) {
				if (this->belongings[i]->getIsEquip() && this->belongings[i]->getType() == Armor) {
					this->belongings[i]->changeIsEquript();
					this->belongings[i]->remove(this);
				}
			}
			this->belongings[n]->changeIsEquript();
			this->belongings[n]->equip(this);
		}
		else {
			if (this->belongings[n]->getType() == Armor) {
				this->belongings[n]->equip(this);
				this->belongings[n]->changeIsEquript();
				this->armor = true;
			}
			else if (this->belongings[n]->getType() == Weapon) {
				this->belongings[n]->equip(this);
				this->belongings[n]->changeIsEquript();
				this->weapon = true;
			}
		}
	}
}

int Player::getAllStr() {
	return this->status.str + this->weaponStr + this->armorStr;
}

void Player::attack(Enemy *e, std::string *n) {
	int damage = this->getAllStr() - e->getDef() > 1 ? this->getAllStr() - e->getDef() : 1;
	e->damage(damage);

	*n = this->getName() + "�̍U���I\n";
	*n += e->getName() + "��" + std::to_string(damage) + "�̃_���[�W�I";
}

void Player::learnMagic(Magic *magic) {
	this->magic[this->learnMagicNum] = magic;
	this->learnMagicNum++;
}

void Player::setLevelTable() {
	for (int i = 0; i < MAXLEVEL - 1; i++) {
		this->levelTable[i] = (i + 1) * 6;
	}
}

// ���x���A�b�v���̊֐�
void Player::levelUp(std::string *s) {
	if (this->status.exp >= this->levelTable[this->status.lv - 1]) {
		// ���x�����ЂƂ�����
		this->status.lv++;

		// �e�X�e�[�^�X���グ��
		this->addMaxHp(15);
		this->addMaxMp(5);
		this->addStr(3);
		this->addDef(2);
		this->setHp(this->getMaxHp());
		this->setMp(this->getMaxMp());

		*s += this->getName() + "�� Lv" + std::to_string(this->getLv()) + " �ɂȂ����I\n";

		// ���x���ɂ���Ė��@���K��
		switch (this->getLv()) {
		case 2:
			this->learnMagic(new Fire());
			*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
			break;
		case 5:
			this->learnMagic(new Thunder());
			*s += this->magic[this->learnMagicNum - 1]->getName() + "�̖��@���K�������I\n";
			break;
		}
	}
}