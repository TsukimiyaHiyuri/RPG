#include "EquipmentWindow.h"
#include "StatusWindow.h"
#include "SelectWindow.h"
#include "Key.h"
#include "DxLib.h"

EquipmentWindow::EquipmentWindow(Player *player, Sound *sound) {
	this->selectNum = 0;
	this->sound = sound;
	this->isHide = true;
	this->selectWindow = new SelectWindow(player, sound);
	this->player = player;
}

// 項目の描画
void EquipmentWindow::drawEquipmentWindow() {

	if (!this->isHide) {
		DrawBox(DRAWXSTATUS1 - 15, DRAWYSTATUS1 - 15, DRAWXSTATUS2, DRAWYSTATUS2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->player->getBelongingsNum(); i++) {
			std::string equipt;
			if (this->player->getBelonging(i)->getIsEquip()) {
				equipt = "E ";
			}
			else {
				equipt = "  ";
			}

			if (i == this->selectNum) {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(0, 255, 255), "%s", (equipt + this->player->getBelonging(i)->getName()).c_str());
			}
			else {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(255, 255, 255), "%s", (equipt + this->player->getBelonging(i)->getName()).c_str());
			}
		}

		// アイテムの説明欄を描画
		if (this->player->getBelongingsNum() > 0) {
			DrawBox(DRAWDESCRIPTIONX1 - 15, DRAWDESCRIPTIONY1 - 15, DRAWDESCRIPTIONX2, DRAWDESCRIPTIONY2, GetColor(0, 0, 0), true);
			DrawFormatString(DRAWDESCRIPTIONX1, DRAWDESCRIPTIONY1, GetColor(255, 255, 255), "%s", this->player->getBelonging(this->selectNum)->getDescription().c_str());
		}
	}
}

void EquipmentWindow::changeIsHide() {
	this->isHide = !this->isHide;
}

// カーソルの移動の処理
void EquipmentWindow::moveSelector() {
	if (this->canSelect()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->player->getBelongingsNum() - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= this->player->getBelongingsNum()) {
				this->selectNum = 0;
			}
		}

		
	}
}

// 決定ボタン、キャンセルボタンの処理
void EquipmentWindow::select() {
	if (this->canSelect()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			// SEをならす
			this->sound->playSE(DecideSE, true);

			// 所持品があれば
			if (this->player->getBelongingsNum() > 0) {
				this->selectWindow->setItemNum(this->selectNum);
				this->selectWindow->changeIsHide();
			}
		}
		if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			// SEをならす
			this->sound->playSE(CancelSE, true);
			this->init();
		}
	}
}

void EquipmentWindow::drawAll() {
	this->drawEquipmentWindow();
	this->moveSelector();
	this->select();

	if (this->selectWindow->drawAll()) {
		// アイテムが使われたときにselectNumが所持品の数を超えたときの処理
		if (this->selectNum >= this->player->getBelongingsNum()) {
			this->selectNum = this->player->getBelongingsNum() - 1;
		}
	}
}

bool EquipmentWindow::canSelect() {
	return !this->isHide && this->selectWindow->getIsHide();
}

void EquipmentWindow::init() {
	this->selectNum = 0;
	this->isHide = true;
}