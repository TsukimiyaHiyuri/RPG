#include "BattleWindow.h"
#include "DxLib.h"

BattleWindow::BattleWindow() {
	this->str = "";
	this->isHide = true;
	this->interbalCount = 0;
}

void BattleWindow::setStr(std::string str) {
	this->str = str;
}

void BattleWindow::drawBattleWindow() {
	if (!this->strIsEmpty()) {
		DrawBox(BATTLEWINDOWX1, BATTLEWINDOWY1, BATTLEWINDOWX2, BATTLEWINDOWY2, GetColor(0, 0, 0), true);

		DrawFormatString(BATTLEWINDOWX1 + 10, BATTLEWINDOWY1 + 10, GetColor(255, 255, 255), "%s", this->str.c_str());

		this->incrementInterbalCount();
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

void BattleWindow::incrementInterbalCount() {
	interbalCount++;
	if (interbalCount >= BTTLEWINDOWINTERBAL) {
		interbalCount = 0;
		this->setStr("");
	}
}