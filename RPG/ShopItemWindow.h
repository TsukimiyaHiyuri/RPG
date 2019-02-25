#pragma once
#ifndef _ShopItemWindow_
#define _ShopItemWindow_

#include "Player.h"
#include "ShopNPC.h"

class Player;
class ShopNPC;

class ShopItemWindow {
	bool isHide;
	int selectNum;

public:
	ShopItemWindow();
	void drawShopItemWindow(Player *p);
	void drawShopItemWindow(ShopNPC *shopNPC);
	void moveSelector(Player *p);
	void moveSelector(ShopNPC *shopNPC);
	void select(Player *p);
	void select(Player *p, ShopNPC *shopNPC);
	void drawAll(Player *p);
	void drawAll(Player *p, ShopNPC *shopNPC);
	void init();

	bool getIsHide() { return this->isHide; }
	void changeIsHide() { this->isHide = !this->isHide; }
};

#endif