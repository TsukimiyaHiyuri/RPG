#include "NonPlayerCharacter.h"
#include "Key.h"
#include "DxLib.h"

NonPlayerCharacter::NonPlayerCharacter(int x, int y, std::string fileName, std::vector<std::string> speak, direct direction) {
	this->set(x, y);
	this->loadGraphic(fileName);
	this->setSpeak(speak);
	this->init();
	this->direction = direction;
}

void NonPlayerCharacter::loadGraphic(std::string fileName) {
	LoadDivGraph(fileName.c_str(), 3 * 4, 3, 4, 32, 32, this->graphic);//‰æ‘œ‚ð•ªŠ„‚µ‚Äimage”z—ñ‚É•Û‘¶
}

void NonPlayerCharacter::setSpeak(std::vector<std::string> s) {
	this->speak = s;
}

void NonPlayerCharacter::set(int x, int y) {
	this->x = x;
	this->y = y;
}

void NonPlayerCharacter::select(Player *player) {
	if (this->isSpeak) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			index++;
			if (this->index >= this->speak.size()) {
				this->init();
				player->changeIsSpeak();
			}
		}
	}
}

NonPlayerCharacter *NonPlayerCharacter::speakStart(Player *player, NonPlayerCharacter *npc) {
	if (!this->isSpeak) {
		// ˜b‚µ‚©‚¯‚ç‚ê‚½•ûŒü‚ðŒü‚­‚æ‚¤‚É‚·‚é
		if (player->getx() == this->x) {
			if (player->gety() - this->y == 1 && player->getDirect() == UP) {
				if (Key[KEY_INPUT_Z] == 1) {
					Key[KEY_INPUT_Z]++;

					this->direction = DOWN;
					this->isSpeak = true;
					player->changeIsSpeak();
					return this;
				}

			}
			if (this->y - player->gety() == 1 && player->getDirect() == DOWN) {
				if (Key[KEY_INPUT_Z] == 1) {
					Key[KEY_INPUT_Z]++;

					this->direction = UP;
					this->isSpeak = true;
					player->changeIsSpeak();
					return this;
				}
			}
		}
		if (player->gety() == this->y) {
			if (player->getx() - this->x == 1 && player->getDirect() == LEFT) {
				if (Key[KEY_INPUT_Z] == 1) {
					Key[KEY_INPUT_Z]++;

					this->direction = RIGHT;
					this->isSpeak = true;
					player->changeIsSpeak();
					return this;
				}
			}
			if (this->x - player->getx() == 1 && player->getDirect() == RIGHT) {
				if (Key[KEY_INPUT_Z] == 1) {
					Key[KEY_INPUT_Z]++;

					this->direction = LEFT;
					this->isSpeak = true;
					player->changeIsSpeak();
					return this;
				}
			}
		}
	}

	return NULL;
}

void NonPlayerCharacter::speaking(Player *player) {
	if (this->isSpeak) {
		DrawBox(SPEAKWINDOWX1, SPEAKWINDOWY1, SPEAKWINDOWX2, SPEAKWINDOWY2, GetColor(0, 0, 0), true);
		DrawFormatString(SPEAKWINDOWX1 + 10, SPEAKWINDOWY1 + 10, GetColor(255, 255, 255), "%s", this->speak[this->index].c_str());
	}
	this->select(player);
}

void NonPlayerCharacter::init() {
	this->isSpeak = false;
	this->index = 0;
}