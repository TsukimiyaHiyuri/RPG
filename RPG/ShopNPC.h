#pragma once
#ifndef _ShopNPC_
#define _ShopNPC_

#include "NonPlayerCharacter.h"
#include "Player.h"
#include "Item.h"
#include "ShopWindow.h"
#define MAXITEMNUM 8

class ShopWindow;

class ShopNPC : public NonPlayerCharacter {
	Item *item[MAXITEMNUM];
	int itemNum;		// NPCが販売するアイテムの種類数
	ShopWindow *shopWindow;

public:
	ShopNPC() {}
	ShopNPC(int x, int y, std::string fileName, std::vector<std::string> speak, direct direction, Item *item[], int n);
	virtual void speaking(Player *p);
	void select();
	void setItem(Item *item[], int n);

	int getItemNum() { return this->itemNum; }
	Item *getItem(int i) { return this->item[i]; }

};

#endif