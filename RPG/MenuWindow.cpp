#include "MenuWindow.h"
#include "DxLib.h"
#include "Key.h"

MenuWindow::MenuWindow(Player *p) {
	this->selectNum = 0;
	this->isHide = true;
	this->setList();
	this->statusWindow = StatusWindow();
	this->equipmentWindow = EquipmentWindow();
	this->fromPlayer = p;
}

void MenuWindow::setList() {
	this->list = std::vector<std::string>(MENUNUM);
	this->list[Equipment] = "�ǂ���";
	this->list[Paramater] = "�X�e�[�^�X";
	this->list[Save] = "�Z�[�u";
}

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
	if (this->isHide) {
		this->isHide = false;
	}
	else {
		this->isHide = true;
	}
}

void MenuWindow::moveSelector() {
	if (Key[KEY_INPUT_UP] == 1) {
		this->selectNum--;
		if (this->selectNum < 0) {
			this->selectNum = MENUNUM - 1;
		}
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		this->selectNum++;
		if (this->selectNum >= MENUNUM) {
			this->selectNum = 0;
		}
	}
}

void MenuWindow::select() {
	
	if (Key[KEY_INPUT_Z] == 1) {

		switch (this->selectNum) {
		case Equipment:
			this->equipmentWindow = EquipmentWindow(this->fromPlayer);
			this->equipmentWindow.changeIsHide();
			break;
		case Paramater:
			this->statusWindow = StatusWindow(this->fromPlayer);
			this->statusWindow.changeIsHide();
			break;
		case Save: break;
		}

		Key[KEY_INPUT_Z]++;
	}
}