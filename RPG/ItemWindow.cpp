#include "ItemWindow.h"
#include "Key.h"
#include "DxLib.h"

ItemWindow::ItemWindow() {
	this->isHide = true;
	this->itemSelectWindow = new ItemSelectWindow();
}

ItemWindow::ItemWindow(Player *player) {
	this->isHide = false;
	this->player = player;
	this->selectNum = 0;
	this->itemSelectWindow = new ItemSelectWindow();
}

void ItemWindow::drawItemWindow() {
	if (!this->isHide) {
		DrawBox(ITEMWINDOWX1, ITEMWINDOWY1, ITEMWINDOWX2, ITEMWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->player->getBelongingsNum(); i++) {

			std::string equipt;
			if (this->player->getBelonging(i)->getIsEquip()) {
				equipt = "E ";
			}
			else {
				equipt = "  ";
			}

			if (i == this->selectNum) {
				DrawFormatString(ITEMWINDOWX1, ITEMWINDOWY1 + ITEMWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", (equipt + player->getBelonging(i)->getName()).c_str());
			}
			else {
				DrawFormatString(ITEMWINDOWX1, ITEMWINDOWY1 + ITEMWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", (equipt + player->getBelonging(i)->getName()).c_str());
			}

			/* アイテムの説明欄の描画はここに記入 */

		}
	}
}

void ItemWindow::moveSelector() {
	if (!this->isHide && this->itemSelectWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = player->getBelongingsNum() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= player->getBelongingsNum()) {
				this->selectNum = 0;
			}
		}
	}
}

void ItemWindow::select() {
	if (!this->isHide && this->itemSelectWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			if (this->player->getBelongingsNum() > 0) {
				this->itemSelectWindow = new ItemSelectWindow(this->player, this->selectNum);
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			this->init();
		}
	}
}

bool ItemWindow::drawAll() {
	this->drawItemWindow();
	this->moveSelector();
	this->select();
	if (!this->itemSelectWindow->getIsHide()) {
		return this->itemSelectWindow->drawAll();
	}
	else {
		return false;
	}
}

void ItemWindow::init() {
	this->isHide = true;
	this->selectNum = 0;
	this->itemSelectWindow->init();
}