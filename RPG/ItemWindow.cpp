#include "ItemWindow.h"
#include "Key.h"
#include "DxLib.h"

ItemWindow::ItemWindow() {
	this->isHide = true;
	this->battleWindowStr = "";
	this->itemSelectWindow = new ItemSelectWindow();
}

ItemWindow::ItemWindow(Player *player, Sound *sound) {
	this->isHide = false;
	this->sound = sound;
	this->player = player;
	this->selectNum = 0;
	this->itemSelectWindow = new ItemSelectWindow();
}

// �A�C�e���̃��X�g�̕`��̏���
void ItemWindow::drawItemWindow() {
	if (!this->isHide) {
		DrawBox(ITEMWINDOWX1, ITEMWINDOWY1, ITEMWINDOWX2, ITEMWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->player->getBelongingsNum(); i++) {

			// �������Ă���A�C�e���ɂ͐擪�ɁuE�v������
			std::string equipt;
			if (this->player->getBelonging(i)->getIsEquip()) {
				equipt = "E ";
			}
			else {
				equipt = "  ";
			}

			if (i == this->selectNum) {
				DrawFormatString(ITEMWINDOWX1 + 5, ITEMWINDOWY1 + ITEMWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", (equipt + player->getBelonging(i)->getName()).c_str());
			}
			else {
				DrawFormatString(ITEMWINDOWX1 + 5, ITEMWINDOWY1 + ITEMWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", (equipt + player->getBelonging(i)->getName()).c_str());
			}
		}

		// �A�C�e���̐�����`��
		if (this->player->getBelonging(this->selectNum) > 0) {
			DrawBox(ITEMWINDOWDISCRIPTIONX1, ITEMWINDOWDISCRIPTIONY1, ITEMWINDOWDISCRIPTIONX2, ITEMWINDOWDISCRIPTIONY2, GetColor(0, 0, 0), true);
			DrawFormatString(ITEMWINDOWDISCRIPTIONX1 + 5, ITEMWINDOWDISCRIPTIONY1 + 5, GetColor(255, 255, 255), "%s", player->getBelonging(this->selectNum)->getDescription().c_str());
		}
	}
}

// �J�[�\���ړ��̏���
void ItemWindow::moveSelector() {
	if (!this->isHide && this->itemSelectWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = player->getBelongingsNum() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= player->getBelongingsNum()) {
				this->selectNum = 0;
			}
		}
	}
}

// ����{�^���A�L�����Z���{�^���̏���
void ItemWindow::select() {
	if (!this->isHide && this->itemSelectWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			// SE���Ȃ炷
			this->sound->playSE(DecideSE, true);

			if (this->player->getBelongingsNum() > 0) {
				this->itemSelectWindow = new ItemSelectWindow(this->player, this->selectNum, this->sound);
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
bool ItemWindow::drawAll() {
	this->drawItemWindow();
	this->moveSelector();
	this->select();

	// �A�C�e�����g��ꂽ��A�o�g���E�B���h�E�̕�������X�V����
	if (this->itemSelectWindow->drawAll()) {
		this->battleWindowStr = this->itemSelectWindow->getBattleWindowStr();
		return true;
	}
	return false;
}

// �������֐�
void ItemWindow::init() {
	this->isHide = true;
	this->selectNum = 0;
	this->battleWindowStr = "";
	this->itemSelectWindow->init();
}