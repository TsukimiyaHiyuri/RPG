#include "ComandWindow.h"
#include "Key.h"
#include "DxLib.h"

// �R���X�g���N�^
ComandWindow::ComandWindow(Player *player, Enemy *enemy[], int enemyNum) {
	this->player = player;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = enemy[i];
	}
	this->enemyNum = enemyNum;
	this->isFinish = false;
	this->isHide = false;
	this->selectNum = 0;
	this->setList();
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
			DrawFormatString(COMANDWINDOWX1, COMANDWINDOWY1 + COMANDWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", list[i].c_str());
		}
		else {
			DrawFormatString(COMANDWINDOWX1, COMANDWINDOWY1 + COMANDWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
		}
	}
}

// ���ݑI�����Ă��鍀�ڂ̈ړ�
void ComandWindow::moveSelector() {
	if (!this->isHide && this->enemyListWindow->getIsHide() && this->itemWindow->getIsHide() && this->magicWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = COMANDTYPENUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
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

			switch (this->selectNum) {
			case TypeFight:
				this->enemyListWindow = new EnemyListWindow(
					this->player,
					this->enemy,
					this->enemyNum,
					-1,
					TypeFight
				);
				return false;

			case TypeMagic:
				this->magicWindow = new MagicWindow(this->player, this->enemy, this->enemyNum);
				return false;

			case TypeItem:
				this->itemWindow = new ItemWindow(this->player);
				return false;

			case TypeEscape:
				return true;

			}
		}
	}
	return false;
}

// �`���L�[�̊Ď����܂Ƃ߂�����
bool ComandWindow::drawAll() {
	this->drawComandWindow();
	this->moveSelector();

	bool isFinish = this->select();

	if (!isFinish) {
		isFinish = this->enemyListWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->magicWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->itemWindow->drawAll();
	}

	return isFinish;
}

// �e�p�����[�^�������l�ɖ߂�
void ComandWindow::init() {
	this->selectNum = 0;
	this->enemyListWindow->init();
	this->itemWindow->init();
	this->magicWindow->init();
}