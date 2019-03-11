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

// アイテムのリストの描画の処理
void ItemWindow::drawItemWindow() {
	if (!this->isHide) {
		DrawBox(ITEMWINDOWX1, ITEMWINDOWY1, ITEMWINDOWX2, ITEMWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->player->getBelongingsNum(); i++) {

			// 装備しているアイテムには先頭に「E」をつける
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

		// アイテムの説明を描画
		if (this->player->getBelonging(this->selectNum) > 0) {
			DrawBox(ITEMWINDOWDISCRIPTIONX1, ITEMWINDOWDISCRIPTIONY1, ITEMWINDOWDISCRIPTIONX2, ITEMWINDOWDISCRIPTIONY2, GetColor(0, 0, 0), true);
			DrawFormatString(ITEMWINDOWDISCRIPTIONX1 + 5, ITEMWINDOWDISCRIPTIONY1 + 5, GetColor(255, 255, 255), "%s", player->getBelonging(this->selectNum)->getDescription().c_str());
		}
	}
}

// カーソル移動の処理
void ItemWindow::moveSelector() {
	if (!this->isHide && this->itemSelectWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = player->getBelongingsNum() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= player->getBelongingsNum()) {
				this->selectNum = 0;
			}
		}
	}
}

// 決定ボタン、キャンセルボタンの処理
void ItemWindow::select() {
	if (!this->isHide && this->itemSelectWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			// SEをならす
			this->sound->playSE(DecideSE, true);

			if (this->player->getBelongingsNum() > 0) {
				this->itemSelectWindow = new ItemSelectWindow(this->player, this->selectNum, this->sound);
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			// SEをならす
			this->sound->playSE(CancelSE, true);

			this->init();
		}
	}
}

// 描画、カーソル移動、選択の処理をまとめたもの
bool ItemWindow::drawAll() {
	this->drawItemWindow();
	this->moveSelector();
	this->select();

	// アイテムが使われたら、バトルウィンドウの文字列を更新する
	if (this->itemSelectWindow->drawAll()) {
		this->battleWindowStr = this->itemSelectWindow->getBattleWindowStr();
		return true;
	}
	return false;
}

// 初期化関数
void ItemWindow::init() {
	this->isHide = true;
	this->selectNum = 0;
	this->battleWindowStr = "";
	this->itemSelectWindow->init();
}