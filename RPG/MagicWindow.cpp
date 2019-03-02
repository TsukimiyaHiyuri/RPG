#include "MagicWindow.h"
#include "Key.h"
#include "DxLib.h"

MagicWindow::MagicWindow() {
	this->isHide = true;
	this->enemyListWindow = new EnemyListWindow();
}

MagicWindow::MagicWindow(Player *player, Enemy *enemy[], int enemyNum, Sound *sound) {
	this->player = player;
	this->sound = sound;

	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = enemy[i];
	}

	this->enemyNum = enemyNum;
	this->isHide = false;
	this->selectNum = 0;
	this->enemyListWindow = new EnemyListWindow();
}

// ���@�̈ꗗ��`�悷��
void MagicWindow::drawMagicWindow() {
	if (!this->isHide) {
		DrawBox(MAGICWINDOWX1, MAGICWINDOWY1, MAGICWINDOWX2, MAGICWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->player->getLearnMagicNum(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(MAGICWINDOWX1, MAGICWINDOWY1 + MAGICWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", this->player->getMagic(i)->getName().c_str());
			}
			else {
				DrawFormatString(MAGICWINDOWX1, MAGICWINDOWY1 + MAGICWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", this->player->getMagic(i)->getName().c_str());
			}

			/* ���@�̐������̕`��͂����ɋL�� */

		}
	}
}

// �J�[�\���ړ��̏���
void MagicWindow::moveSelector() {
	if (!this->isHide && this->enemyListWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->player->getLearnMagicNum() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= this->player->getLearnMagicNum()) {
				this->selectNum = 0;
			}
		}
	}
}

// ����{�^���ƃL�����Z���{�^���̏���
bool MagicWindow::selsect() {
	if (!this->isHide && this->enemyListWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1 && this->player->getLearnMagicNum() > 0) {
			Key[KEY_INPUT_Z]++;

			// SE���Ȃ炷
			this->sound->playSE(DecideSE, true);

			MagicType tmp = this->player->getMagic(this->selectNum)->getType();
			
			switch (tmp) {
			case AttackSolo:
				this->enemyListWindow = new EnemyListWindow(
					this->player,
					this->enemy,
					this->enemyNum,
					this->selectNum,
					TypeMagic,
					this->sound
				);
				return false;

			case AttackAll:
				return this->player->getMagic(this->selectNum)->use(this->player, this->enemy, &this->battleWindowStr);

			case CureSolo:
				return this->player->getMagic(this->selectNum)->use(this->player, &this->battleWindowStr);
				
			case CureAll:
				return this->player->getMagic(this->selectNum)->use(this->player);
				
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			// SE���Ȃ炷
			this->sound->playSE(CancelSE, true);

			this->init();
		}
	}
	return false;
}

// �`��A�J�[�\���ړ��A�I���̏������܂Ƃ߂�����
bool MagicWindow::drawAll() {
	this->drawMagicWindow();
	this->moveSelector();
	if (this->enemyListWindow->drawAll()) {
		this->battleWindowStr = this->enemyListWindow->getBattleWindowStr();
		return true;
	}
	return this->selsect();
}

// �������֐�
void MagicWindow::init() {
	this->isHide = true;
	this->battleWindowStr = "";
	this->selectNum = 0;
	this->enemyListWindow->init();
}