#include "SelectWindow.h"
#include "DxLib.h"
#include "Player.h"
#include "Key.h"

SelectWindow::SelectWindow(Player *who, Sound *sound) {
	this->selectNum = 0;
	this->sound = sound;
	this->isHide = true;
	this->who = who;
	this->setList();
}

// 項目の設定
void SelectWindow::setList() {
	this->list = std::vector<std::string>(SELECTNUM);
	this->list[Use] = "つかう";
	this->list[Equip] = "そうび";
	this->list[Throw] = "すてる";
}

// 項目の描画
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
		
		this->moveSelector();
	}
}

void SelectWindow::changeIsHide() {
	this->isHide = !this->isHide;
}

// カーソル移動の処理
void SelectWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = SELECTNUM - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= SELECTNUM) {
				this->selectNum = 0;
			}
		}
	}
}

// 決定ボタン、キャンセルボタンの処理
Select SelectWindow::select() {

	if (Key[KEY_INPUT_Z] == 1) {
		Key[KEY_INPUT_Z]++;

		switch (this->selectNum) {
		case Use:
			// SEをならす
			this->sound->playSE(DecideSE, true);

			this->selection = Use;
			who->useItem(this->itemNum, this->who);
			this->changeIsHide();
			return Use;
		case Throw:
			// SEをならす
			this->sound->playSE(DecideSE, true);

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
	else if (Key[KEY_INPUT_X] == 1) {
		Key[KEY_INPUT_X]++;

		// SEをならす
		this->sound->playSE(CancelSE, true);

		this->changeIsHide();
	}

	return Defalt;
}