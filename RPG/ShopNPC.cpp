#include "ShopNPC.h"
#include "DxLib.h"
#include "Key.h"

ShopNPC::ShopNPC(int x, int y, std::string fileName, std::vector<std::string> speak, direct direction, Item *item[], int n, Sound *sound) {
	this->set(x, y);
	this->loadGraphic(fileName);
	this->setSpeak(speak);
	this->init();
	this->direction = direction;
	this->setItem(item, n);
	this->sound = sound;
	this->shopWindow = new ShopWindow(sound);
}

void ShopNPC::speaking(Player *player) {
	if (this->isSpeak && this->shopWindow->getIsHide()) {
		DrawBox(SPEAKWINDOWX1, SPEAKWINDOWY1, SPEAKWINDOWX2, SPEAKWINDOWY2, GetColor(0, 0, 0), true);
		DrawFormatString(SPEAKWINDOWX1 + 10, SPEAKWINDOWY1 + 10, GetColor(255, 255, 255), "%s", this->speak[this->index].c_str());
	}
	this->select();

	if (!this->shopWindow->getIsHide()) {
		this->isSpeak = this->shopWindow->drawAll(player, this);
		player->setIsSpeak(this->isSpeak);
	}

	if (!this->isSpeak) {
		this->init();
	}
}

void ShopNPC::select() {
	if (this->isSpeak && this->shopWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			this->index++;
			if (this->index >= this->speak.size()) {
				this->shopWindow->changeIsHide();
			}
		}
	}
}

void ShopNPC::setItem(Item *item[], int n) {
	for (int i = 0; i < n; i++) {
		this->item[i] = item[i];
	}
	this->itemNum = n;
}