#include "BattleWindow.h"
#include "DxLib.h"

BattleWindow::BattleWindow() {
	this->str = "";
	this->isHide = true;
	this->cnt = 0;
}

void BattleWindow::setStr(std::string str) {
	this->str = str;
}

void BattleWindow::drawBattleWindow() {
	DrawBox(BATTLEWINDOWX1, BATTLEWINDOWY1, BATTLEWINDOWX2, BATTLEWINDOWY2, GetColor(0, 0, 0), true);

	DrawFormatString(BATTLEWINDOWX1 + 10, BATTLEWINDOWY1 + 10, GetColor(255, 255, 255), "%s", this->str.c_str());

	cnt++;
	if (cnt >= INTERBAL) {
		cnt = 0;
		this->setStr("");
	}
}

bool BattleWindow::strIsEmpty() {
	return this->str.empty();
}

void BattleWindow::changeIsHide() {
	this->isHide = !this->isHide;
}

void BattleWindow::drawAll() {
	this->drawBattleWindow();
}