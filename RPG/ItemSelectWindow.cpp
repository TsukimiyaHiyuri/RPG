#include "ItemSelectWindow.h"
#include "Key.h"
#include "DxLib.h"

ItemSelectWindow::ItemSelectWindow(Player *player, int itemNum, Sound *sound) {
	this->player = player;
	this->sound = sound;
	this->isHide = false;
	this->selectNum = 0;
	this->itemNum = itemNum;
	this->setList();
}

// ���ڂ̐ݒ�
void ItemSelectWindow::setList() {
	this->list = std::vector<std::string>(ITEMCOMANDNUM);
	this->list[ComandUse] = "����";
	this->list[ComandEquip] = "������";
}

// ���ڂ̕`��̏���
void ItemSelectWindow::drawItemSelectWindow() {
	if (!this->isHide) {
		DrawBox(ITEMSELECTWINDOWX1, ITEMSELECTWINDOWY1, ITEMSELECTWINDOWX2, ITEMSELECTWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->list.size(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(ITEMSELECTWINDOWX1 + 5, ITEMSELECTWINDOWY1 + 5 + ITEMSELECTWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", list[i].c_str());
			}
			else {
				DrawFormatString(ITEMSELECTWINDOWX1 + 5, ITEMSELECTWINDOWY1 + 5 + ITEMSELECTWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
			}
		}
	}
}

// �J�[�\���ړ��̏���
void ItemSelectWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = ITEMCOMANDNUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= ITEMCOMANDNUM) {
				this->selectNum = 0;
			}
		}
	}
}

// ����{�^���ƃL�����Z���{�^���������ꂽ�Ƃ��̏���
bool ItemSelectWindow::select() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			switch (this->selectNum) {
			case ComandUse:
				// SE���Ȃ炷
				this->sound->playSE(DecideSE, true);

				this->player->useItem(this->itemNum, this->player, &this->battleWindowStr);
				this->isHide = true;
				return true;

			case ComandEquip:
				this->player->equipItem(this->itemNum, this->player);
				this->isHide = true;
				return false;
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
bool ItemSelectWindow::drawAll() {
	this->drawItemSelectWindow();
	this->moveSelector();
	return this->select();
}

// �������֐�
void ItemSelectWindow::init() {
	this->isHide = true;
	this->selectNum = 0;
	this->battleWindowStr = "";
}