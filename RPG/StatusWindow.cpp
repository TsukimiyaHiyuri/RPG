#include "StatusWindow.h"
#include "DxLib.h"
#include "Player.h"
#include "Key.h"

StatusWindow::StatusWindow(Player *who, Sound *sound) {
	this->selectNum = 0;
	this->isHide = true;
	this->player = who;
	this->setList();
	this->sound = sound;
}

// 描画する項目の設定
void StatusWindow::setList() {
	this->list = std::vector<std::string>(STATUSMENUNUM);
	this->list[hp] = "HP: " + std::to_string(player->getHp());
	this->list[lv] = "LV: " + std::to_string(player->getLv());
	this->list[maxHp] = "MAX HP: " + std::to_string(player->getMaxHp());
	this->list[maxMp] = "MAX MP: " + std::to_string(player->getMaxMp());
	this->list[mp] = "MP: " + std::to_string(player->getMp());
	this->list[str] = "STR: " + std::to_string(player->getAllStr());
	this->list[def] = "DEF: " + std::to_string(player->getAllDef());
	this->list[experience] = "EXP: " + std::to_string(player->getExp());
	this->list[gold] = "GOLD: " + std::to_string(player->getGold());
}

// 項目の描画
void StatusWindow::drawStatusWindow() {
	if (!this->isHide) {
		DrawBox(DRAWXSTATUS1 - 15, DRAWYSTATUS1 - 15, DRAWXSTATUS2, DRAWYSTATUS2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->list.size(); i++) {
			DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
		}
	}

	this->select();
}

// 決定ボタンとキャンセルボタンの処理
void StatusWindow::select() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_X] == 1 || Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_X] += 2;
			Key[KEY_INPUT_Z] += 2;

			// SEをならす
			this->sound->playSE(CancelSE, true);

			this->changeIsHide();
		}
	}
}

void StatusWindow::changeIsHide() {
	this->isHide = !this->isHide;
}

void StatusWindow::drawAll() {
	this->drawStatusWindow();
	this->select();
}