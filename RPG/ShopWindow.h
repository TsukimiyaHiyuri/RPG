#pragma once
#ifndef _ShopWindow_
#define _ShopWindow_

#include "Player.h"
#include "ShopNPC.h"
#include "ShopItemWindow.h"
#include <vector>
#include <string> 
#define TYPESHOPNUM 2
#define SHOPWINDOWX1 50
#define SHOPWINDOWY1 50
#define SHOPWINDOWX2 120
#define SHOPWINDOWY2 120

class Player;
class ShopNPC;
class ShopItemWindow;

enum TypeShop {
	Buy = 0,
	Sell = 1
};

class ShopWindow {
	bool isHide;
	int selectNum;
	std::vector<std::string> list;
	ShopItemWindow *shopItemWindow;

public:
	ShopWindow();
	void setList();
	void drawShopWindow();
	void moveSelector();
	bool select();
	bool drawAll(Player *player, ShopNPC *shopNPC);

	bool getIsHide() { return this->isHide; }
	void changeIsHide() { this->isHide = !this->isHide; }

};

#endif