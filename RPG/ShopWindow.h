#pragma once
#ifndef _ShopWindow_
#define _ShopWindow_

#include "Player.h"
#include "ShopNPC.h"
#include "ShopItemWindow.h"
#include "Sound.h"
#include <vector>
#include <string> 
#define TYPESHOPNUM 2
#define SHOPWINDOWX1 30
#define SHOPWINDOWY1 50
#define SHOPWINDOWX2 100
#define SHOPWINDOWY2 120
#define GOLDWINDWX1 110
#define GOLDWINDWY1 50
#define GOLDWINDWX2 200
#define GOLDWINDWY2 150


class Player;
class ShopNPC;
class ShopItemWindow;
class Sound;

enum TypeShop {
	Buy = 0,
	Sell = 1
};

class ShopWindow {
	bool isHide;
	int selectNum;
	std::vector<std::string> list;
	ShopItemWindow *shopItemWindow;
	Sound *sound;

public:
	ShopWindow(Sound *sound);
	void setList();
	void drawShopWindow();
	void moveSelector();
	bool select();
	bool drawAll(Player *player, ShopNPC *shopNPC);
	void drawMyGold(Player *player);

	bool getIsHide() { return this->isHide; }
	void changeIsHide() { this->isHide = !this->isHide; }

};

#endif