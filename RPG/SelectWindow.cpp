#include "SelectWindow.h"
#include "DxLib.h"
#include "Player.h"
#include "Key.h"

SelectWindow::SelectWindow(Player *who) {
	this->selectNum = 0;
	this->isHide = true;
	this->who = who;
	this->setList();
}

void SelectWindow::setList() {
	this->list = std::vector<std::string>(SELECTNUM);
	this->list[Use] = "‚Â‚©‚¤";
	this->list[Equip] = "‚»‚¤‚Ñ";
	this->list[Throw] = "‚·‚Ä‚é";
}

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
		
		if (Key[KEY_INPUT_X] == 1) {
			this->changeIsHide();
			Key[KEY_INPUT_X]++;
		}
		this->moveSelector();
	}
}

void SelectWindow::changeIsHide() {
	if (this->isHide) {
		this->isHide = false;
	}
	else {
		this->isHide = true;
	}
}

void SelectWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = SELECTNUM - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= SELECTNUM) {
				this->selectNum = 0;
			}
		}
	}
}

Select SelectWindow::select() {

	if (Key[KEY_INPUT_Z] == 1) {
		Key[KEY_INPUT_Z]++;
		switch (this->selectNum) {
		case Use:
			this->selection = Use;
			who->useItem(this->itemNum, this->who);
			this->changeIsHide();
			return Use;
		case Throw:
			who->throwItem(this->itemNum);
			this->changeIsHide();
			return Throw;

		case Equip:
			who->equipItem(this->itemNum, who);
			this->selection = Equip;
			this->changeIsHide();
			return Equip;
		}
	}
	return Defalt;
}