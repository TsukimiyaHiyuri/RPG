#include "StatusWindow.h"
#include "DxLib.h"
#include "Player.h"
#include "Key.h"

StatusWindow::StatusWindow() {
	this->selectNum = 0;
	this->isHide = true;
}

StatusWindow::StatusWindow(Player *who) {
	this->selectNum = 0;
	this->isHide = true;
	this->who = who;
	this->setList();
}

void StatusWindow::setList() {
	this->list = std::vector<std::string>(MENUNUM);
	this->list[hp] = "HP: " + std::to_string(who->getHp());
	this->list[lv] = "LV: " + std::to_string(who->getLv());
	this->list[maxHp] = "MAX HP: " + std::to_string(who->getMaxHp());
	this->list[maxMp] = "MAX MP: " + std::to_string(who->getMaxMp());
	this->list[mp] = "MP: " + std::to_string(who->getMp());
	this->list[str] = "STR: " + std::to_string(who->getStr() + who->getWeaponStr() + who->getArmorStr());
	this->list[def] = "DEF: " + std::to_string(who->getDef() + who->getWeaponDef() + who->getArmorDef());
	this->list[experience] = "EXP: " + std::to_string(who->getExp());
	this->list[gold] = "GOLD: " + std::to_string(who->getGold());
}

void StatusWindow::drawStatusWindow() {
	if (!this->isHide) {
		DrawBox(DRAWXSTATUS1 - 15, DRAWYSTATUS1 - 15, DRAWXSTATUS2, DRAWYSTATUS2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->list.size(); i++) {
			DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + INTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
		}

		if (Key[KEY_INPUT_X] == 1) {
			this->changeIsHide();
			Key[KEY_INPUT_X]++;
		}
	}
}

void StatusWindow::changeIsHide() {
	if (this->isHide) {
		this->isHide = false;
	}
	else {
		this->isHide = true;
	}
}

void StatusWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = MENUNUM - 1;
			}
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= MENUNUM) {
				this->selectNum = 0;
			}
		}
	}
}