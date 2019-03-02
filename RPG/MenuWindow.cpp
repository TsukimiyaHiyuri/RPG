#include "MenuWindow.h"
#include "DxLib.h"
#include "Key.h"

MenuWindow::MenuWindow(Player *p, Sound *sound) {
	this->selectNum = 0;
	this->sound = sound;
	this->isHide = true;
	this->setList();
	this->statusWindow = StatusWindow();
	this->equipmentWindow = EquipmentWindow();
	this->fromPlayer = p;
}

// ���j���[���ڂ̐ݒ�
void MenuWindow::setList() {
	this->list = std::vector<std::string>(MENUNUM);
	this->list[Equipment] = "�ǂ���";
	this->list[Paramater] = "�X�e�[�^�X";
	this->list[Save] = "�Z�[�u";
}

// ���ڂ̕`��̏���
void MenuWindow::drawMenuWindow() {
	if (!this->isHide) {
		DrawBox(DRAWX1 - 15, DRAWY1 - 15, DRAWX2, DRAWY2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->list.size(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(DRAWX1, DRAWY1 + INTERBAL * i, GetColor(0, 255, 255), "%s", list[i].c_str());
			}
			else {
				DrawFormatString(DRAWX1, DRAWY1 + INTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
			}
		}

		// �X�e�[�^�X�A����E�B���h�E�̕\��
		this->statusWindow.drawStatusWindow();
		this->equipmentWindow.drawEquipmentWindow();

		if (!this->isHide && statusWindow.getIsHide() && equipmentWindow.getIsHide()) {
			this->moveSelector();
			this->select();
		}
	}
}

void MenuWindow::changeIsHide() {
	this->isHide = !this->isHide;
}

// �J�[�\���ړ��̏���
void MenuWindow::moveSelector() {
	if (this->equipmentWindow.getIsHide() && this->statusWindow.getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = MENUNUM - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= MENUNUM) {
				this->selectNum = 0;
			}
		}
	}
}

// ����{�^���A�L�����Z���{�^���̏���
void MenuWindow::select() {
	if (this->equipmentWindow.getIsHide() && this->statusWindow.getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			// SE���Ȃ炷
			this->sound->playSE(DecideSE, true);

			// �e�E�B���h�E��\������
			switch (this->selectNum) {
			case Equipment:
				this->equipmentWindow = EquipmentWindow(this->fromPlayer, this->sound);
				this->equipmentWindow.changeIsHide();
				break;
			case Paramater:
				this->statusWindow = StatusWindow(this->fromPlayer, this->sound);
				this->statusWindow.changeIsHide();
				break;
			case Save: break;
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			// SE���Ȃ炷
			this->sound->playSE(CancelSE, true);

			this->isHide = false;
		}
	}
}