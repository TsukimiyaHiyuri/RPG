#include "ShopWindow.h"
#include "Key.h"
#include "DxLib.h"

ShopWindow::ShopWindow() {
	this->isHide = true;
	this->selectNum = 0;
	this->setList();
	this->shopItemWindow = new ShopItemWindow();
}

void ShopWindow::setList() {
	this->list = std::vector<std::string>(TYPESHOPNUM);
	this->list[Buy] = "”ƒ‚¤";
	this->list[Sell] = "”„‚é";
}

void ShopWindow::drawShopWindow() {
	if (!this->isHide) {
		DrawBox(SHOPWINDOWX1, SHOPWINDOWY1, SHOPWINDOWX2, SHOPWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->list.size(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(SHOPWINDOWX1 + 10, SHOPWINDOWY1 + 10 + (20 * i), GetColor(0, 255, 255), "%s", this->list[i].c_str());
			}
			else {
				DrawFormatString(SHOPWINDOWX1 + 10, SHOPWINDOWY1 + 10 + (20 * i), GetColor(255, 255, 255), "%s", this->list[i].c_str());
			}
		}
	}
}

void ShopWindow::moveSelector() {
	if (!this->isHide && this->shopItemWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->list.size() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= this->list.size()) {
				this->selectNum = 0;
			}
		}
	}
}

bool ShopWindow::select() {
	if (!this->isHide && this->shopItemWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			this->shopItemWindow->changeIsHide();
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;
			this->isHide = true;
			return false;
		}
	}
	return true;
}

bool ShopWindow::drawAll(Player *player, ShopNPC *shopNPC) {
	this->drawShopWindow();
	this->moveSelector();
	bool ans = this->select();

	switch (this->selectNum) {
	case Buy:
		this->shopItemWindow->drawAll(player, shopNPC);
		break;

	case Sell:
		this->shopItemWindow->drawAll(player);
		break;
	}

	return ans;
}