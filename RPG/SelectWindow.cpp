#include "SelectWindow.h"
#include "DxLib.h"
#include "Player.h"
#include "Key.h"

SelectWindow::SelectWindow(Player *who, Sound *sound) {
	this->selectNum = 0;
	this->sound = sound;
	this->isHide = true;
	this->player = who;
	this->setList();
}

// ���ڂ̐ݒ�
void SelectWindow::setList() {
	this->list = std::vector<std::string>(SELECTNUM);
	this->list[Use] = "����";
	this->list[Equip] = "������";
	this->list[Throw] = "���Ă�";
}

// ���ڂ̕`��
void SelectWindow::drawSelectWindow() {
	if (!this->isHide) {
		DrawBox(DRAWSELECTX1 - 15, DRAWSELECTY1 - 15, DRAWSELECTX2, DRAWSELECTY2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->list.size(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(DRAWSELECTX1, DRAWSELECTY1 + INTERBALSELECT * i, GetColor(0, 255, 255), "%s", list[i].c_str());
			}
			else {
				DrawFormatString(DRAWSELECTX1, DRAWSELECTY1 + INTERBALSELECT * i, GetColor(255, 255, 255), "%s", list[i].c_str());
			}
		}
	}
}

void SelectWindow::changeIsHide() {
	this->isHide = !this->isHide;
}

// �J�[�\���ړ��̏���
void SelectWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = SELECTNUM - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= SELECTNUM) {
				this->selectNum = 0;
			}
		}
	}
}

// ����{�^���A�L�����Z���{�^���̏���
void SelectWindow::select() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			switch (this->selectNum) {
			case Use:
				// SE���Ȃ炷
				this->sound->playSE(DecideSE, true);

				player->useItem(this->itemNum, this->player);
				this->init();
				break;

			case Throw:
				// SE���Ȃ炷
				this->sound->playSE(DecideSE, true);

				player->throwItem(this->itemNum);
				this->init();
				break;

			case Equip:
				player->equipItem(this->itemNum, player);
				this->init();
				break;
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			// SE���Ȃ炷
			this->sound->playSE(CancelSE, true);

			this->init();
		}
	}
}

// �`��A�J�[�\���ړ��A�I���̏������܂Ƃ߂�����
void SelectWindow::drawAll() {
	this->drawSelectWindow();
	this->moveSelector();
	this->select();
}

void SelectWindow::init() {
	this->selectNum = 0;
	this->isHide = true;
}