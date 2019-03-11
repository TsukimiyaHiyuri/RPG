#include "ComandWindow.h"
#include "Key.h"
#include "DxLib.h"

// �R���X�g���N�^
ComandWindow::ComandWindow(Player *player, Enemy *enemy[], int enemyNum, Sound *sound) {
	this->player = player;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = enemy[i];
	}
	this->enemyNum = enemyNum;
	this->isFinish = false;
	this->isHide = false;
	this->isEscape = false;
	this->selectNum = 0;
	this->setList();
	this->sound = sound;
	this->enemyListWindow = new EnemyListWindow();
	this->itemWindow = new ItemWindow();
	this->magicWindow = new MagicWindow();
}

// �`�悷�镶�����ݒ�
void ComandWindow::setList() {
	this->list = std::vector<std::string>(COMANDTYPENUM);
	this->list[TypeFight] = "��������";
	this->list[TypeMagic] = "�܂ق�";
	this->list[TypeItem] = "�ǂ���";
	this->list[TypeEscape] = "�ɂ���";
}

// �R�}���h�̍��ڂ�`��
void ComandWindow::drawComandWindow() {
	DrawBox(COMANDWINDOWX1, COMANDWINDOWY1, COMANDWINDOWX2, COMANDWINDOWY2, GetColor(0, 0, 0), true);

	for (int i = 0; i < this->list.size(); i++) {
		if (i == this->selectNum) {
			DrawFormatString(COMANDWINDOWX1 + 5, COMANDWINDOWY1 + 5 + COMANDWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", list[i].c_str());
		}
		else {
			DrawFormatString(COMANDWINDOWX1 + 5, COMANDWINDOWY1 + 5 + COMANDWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
		}
	}
}

// ���ݑI�����Ă��鍀�ڂ̈ړ�
void ComandWindow::moveSelector() {
	if (!this->isHide && this->enemyListWindow->getIsHide() && this->itemWindow->getIsHide() && this->magicWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);
			
			// �J�[�\���𓮂���
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = COMANDTYPENUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			// �J�[�\���𓮂���
			this->selectNum++;
			if (this->selectNum >= COMANDTYPENUM) {
				this->selectNum = 0;
			}
		}
	}
}

// ����L�[�������ꂽ�Ƃ��̏���
bool ComandWindow::select() {
	if (!this->isHide && this->enemyListWindow->getIsHide() && this->itemWindow->getIsHide() && this->magicWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			// SE���Ȃ炷
			this->sound->playSE(DecideSE, true);

			switch (this->selectNum) {
			case TypeFight:
				delete this->enemyListWindow;
				this->enemyListWindow = new EnemyListWindow(
					this->player,
					this->enemy,
					this->enemyNum,
					-1,
					TypeFight,
					this->sound
				);
				return false;

			case TypeMagic:
				delete this->magicWindow;
				this->magicWindow = new MagicWindow(this->player, this->enemy, this->enemyNum, this->sound);
				return false;

			case TypeItem:
				delete this->itemWindow;
				this->itemWindow = new ItemWindow(this->player, this->sound);
				return false;

			case TypeEscape:
				this->escape();
				return true;

			}
		}
	}
	return false;
}

// �`���L�[�̊Ď����܂Ƃ߂�����
// �R�}���h���͂��I���������Ԃ�
bool ComandWindow::drawAll() {
	this->drawComandWindow();
	this->moveSelector();

	bool isFinish = this->select();

	// �e�E�B���h�E�̕`��
	if (!isFinish) {
		isFinish = this->enemyListWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->magicWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->itemWindow->drawAll();
	}

	// �o�g���E�B���h�E�̓��e��ݒ�
	if (this->battleWindowStr.empty()) {
		this->battleWindowStr = this->enemyListWindow->getBattleWindowStr();
	}
	if (this->battleWindowStr.empty()) {
		this->battleWindowStr = this->magicWindow->getBattleWindowStr();
	}
	if (this->battleWindowStr.empty()) {
		this->battleWindowStr = this->itemWindow->getBattleWindowStr();
	}

	return isFinish;
}

// �e�p�����[�^�������l�ɖ߂�
void ComandWindow::init() {
	this->selectNum = 0;
	this->enemyListWindow->init();
	this->itemWindow->init();
	this->magicWindow->init();
	this->battleWindowStr = "";
	this->isEscape = false;
}

void ComandWindow::escape() {
	this->isEscape = true;
}