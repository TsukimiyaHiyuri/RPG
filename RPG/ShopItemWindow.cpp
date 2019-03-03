#include "ShopItemWindow.h"
#include "EquipmentWindow.h"	// アイテム説明のウィンドウの座標のdefineをもってくるため
#include "StatusWindow.h"		// アイテムウィンドウの座標のdefineをもってくるため
#include "Key.h"
#include "DxLib.h"

ShopItemWindow::ShopItemWindow() {
	this->selectNum = 0;
	this->isHide = true;
}

void ShopItemWindow::drawShopItemWindow(Player *player) {
	if (!this->isHide) {
		DrawBox(DRAWXSTATUS1 - 15, DRAWYSTATUS1 - 15, DRAWXSTATUS2, DRAWYSTATUS2, GetColor(0, 0, 0), true);
		for (int i = 0; i < player->getBelongingsNum(); i++) {
			std::string equipt;
			if (player->getBelonging(i)->getIsEquip()) {
				equipt = "E ";
			}
			else {
				equipt = "  ";
			}

			if (i == this->selectNum) {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(0, 255, 255), "%s", (equipt + player->getBelonging(i)->getName()).c_str());
			}
			else {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(255, 255, 255), "%s", (equipt + player->getBelonging(i)->getName()).c_str());
			}
		}

		if (player->getBelongingsNum() > 0) {
			DrawBox(DRAWDESCRIPTIONX1 - 15, DRAWDESCRIPTIONY1 - 15, DRAWDESCRIPTIONX2, DRAWDESCRIPTIONY2, GetColor(0, 0, 0), true);
			DrawFormatString(DRAWDESCRIPTIONX1, DRAWDESCRIPTIONY1, GetColor(255, 255, 255), "%s", player->getBelonging(this->selectNum)->getDescription().c_str());
		}
	}
}

void ShopItemWindow::drawShopItemWindow(ShopNPC *shopNPC) {
	if (!this->isHide) {
		DrawBox(DRAWXSTATUS1 - 15, DRAWYSTATUS1 - 15, DRAWXSTATUS2, DRAWYSTATUS2, GetColor(0, 0, 0), true);
		for (int i = 0; i < shopNPC->getItemNum(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(0, 255, 255), "%s", (shopNPC->getItem(i)->getName()).c_str());
			}
			else {
				DrawFormatString(DRAWXSTATUS1, DRAWYSTATUS1 + STATUSINTERBAL * i, GetColor(255, 255, 255), "%s", (shopNPC->getItem(i)->getName()).c_str());
			}
		}

		if (shopNPC->getItemNum() > 0) {
			DrawBox(DRAWDESCRIPTIONX1 - 15, DRAWDESCRIPTIONY1 - 15, DRAWDESCRIPTIONX2, DRAWDESCRIPTIONY2, GetColor(0, 0, 0), true);
			DrawFormatString(DRAWDESCRIPTIONX1, DRAWDESCRIPTIONY1, GetColor(255, 255, 255), "%s", shopNPC->getItem(this->selectNum)->getDescription().c_str());
		}
	}
}

void ShopItemWindow::moveSelector(Player *player) {
	if (!this->isHide) {
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

void ShopItemWindow::moveSelector(ShopNPC *shopNPC) {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = shopNPC->getItemNum() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= shopNPC->getItemNum()) {
				this->selectNum = 0;
			}
		}
	}
}

void ShopItemWindow::select(Player *player) {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;
			if (player->sellItem(this->selectNum) && this->selectNum > 0) {
				this->selectNum--;
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;
			this->init();
		}
	}
}

void ShopItemWindow::select(Player *player, ShopNPC *shopNPC) {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;
			player->buyItem(shopNPC->getItem(this->selectNum));
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;
			this->init();
		}
	}
}

void ShopItemWindow::drawAll(Player *player) {
	this->drawShopItemWindow(player);
	this->moveSelector(player);
	this->select(player);
}

void ShopItemWindow::drawAll(Player *player, ShopNPC *shopNPC) {
	this->drawShopItemWindow(shopNPC);
	this->moveSelector(shopNPC);
	this->select(player, shopNPC);
}

void ShopItemWindow::init() {
	this->selectNum = 0;
	this->isHide = true;
}