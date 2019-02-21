#include "BattleWindow.h"
#include "DxLib.h"

BattleWindow::BattleWindow() {
	this->str = "";
	this->isFinish = true;
	this->isHide = true;
}

void BattleWindow::setStr(std::string str) {
	this->str = str;
}

void BattleWindow::drawBattleWindow() {
	if (!this->isHide) {
		DrawBox(BATTLEWINDOWX1, BATTLEWINDOWY1, BATTLEWINDOWX2, BATTLEWINDOWY2, GetColor(0, 0, 0), true);

		if (!this->isFinish) {
			DrawFormatString(BATTLEWINDOWX1 + 10, BATTLEWINDOWY1 + 10, GetColor(255, 255, 255), "%s", this->str.c_str());

			cnt++;
			if (cnt >= INTERBAL) {
				cnt = 0;
				isFinish = true;
				this->setStr("");
			}
		}
	}
}

void BattleWindow::drawAll() {

}