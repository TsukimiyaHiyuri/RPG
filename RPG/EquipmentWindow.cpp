#include "EquipmentWindow.h"
#include "StatusWindow.h"
#include "SelectWindow.h"
#include "Key.h"
#include "DxLib.h"

EquipmentWindow::EquipmentWindow() {
	this->selectNum = 0;
	this->isHide = true;
	this->selectWindow = SelectWindow();
}

EquipmentWindow::EquipmentWindow(Player *who) {
	this->selectNum = 0;
	this->isHide = true;
	this->selectWindow = SelectWindow(who);
	this->who = who;
	this->setList();
}

void EquipmentWindow::setList() {
	int num = this->who->getBelongingsNum();
	for (int i = 0; i < num; i++) {
		this->list[i] = this->who->getBelonging(i);
	}
}

void EquipmentWindow::drawEquipmentWindow() {

	if (!this->isHide) {
		DrawBox(DRAWXSTATUS1 - 15, DRAWYSTATUS1 - 15, DRAWXSTATUS2, DRAWYSTATUS2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->who->getBelongingsNum(); i++) {
			std::string equipt;
			if (list[i]->getIsEquip()) {
				equipt = "E ";
			}
			else {
				equipt = "  ";
			}

			if (i == this->selectNum) {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + INTERBAL * i, GetColor(0, 255, 255), "%s", (equipt + list[i]->getName()).c_str());
			}
			else {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + INTERBAL * i, GetColor(255, 255, 255), "%s", (equipt + list[i]->getName()).c_str());
			}
		}

		if (this->who->getBelongingsNum() > 0) {
			DrawBox(DRAWDESCRIPTIONX1 - 15, DRAWDESCRIPTIONY1 - 15, DRAWDESCRIPTIONX2, DRAWDESCRIPTIONY2, GetColor(0, 0, 0), true);
			DrawFormatString(DRAWDESCRIPTIONX1, DRAWDESCRIPTIONY1, GetColor(255, 255, 255), "%s", list[this->selectNum]->getDescription().c_str());
		}

		if (!this->selectWindow.getIsHide()) {
			this->selectWindow.drawSelectWindow();
			this->changeList();
			this->setList();
		}
		
		this->moveSelector();
		this->select();

		if (Key[KEY_INPUT_X] == 1 && this->selectWindow.getIsHide()) {
			this->changeIsHide();
			Key[KEY_INPUT_X]++;
		}
	}
}

void EquipmentWindow::changeIsHide() {
	if (this->isHide) {
		this->isHide = false;
	}
	else {
		this->isHide = true;
	}
}

void EquipmentWindow::moveSelector() {
	if (!this->isHide && this->selectWindow.getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->who->getBelongingsNum() - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= this->who->getBelongingsNum()) {
				this->selectNum = 0;
			}
		}
		if (this->selectNum >= this->who->getBelongingsNum()) {
			this->selectNum = this->who->getBelongingsNum() - 1;
		}
	}
}

void EquipmentWindow::select() {
	if (Key[KEY_INPUT_Z] == 1) {
		if (this->who->getBelongingsNum() > 0 && this->selectWindow.getIsHide()) {
			this->selectWindow.changeIsHide();
			this->selectWindow.setItemNum(this->selectNum);
		}
		Key[KEY_INPUT_Z]++;
	}
}

void EquipmentWindow::changeList() {
	switch (this->selectWindow.select()) {
	case Use: this->throwItem(this->selectNum); break;
	case Throw: this->throwItem(this->selectNum); break;
	}
}

void EquipmentWindow::throwItem(int n) {
	for (int i = n; i < this->who->getBelongingsNum(); i++) {
		this->list[i] = this->list[i + 1];
	}
	this->setList();
}