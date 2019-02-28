#include "EnemyListWindow.h"
#include "Key.h"
#include "DxLib.h"

EnemyListWindow::EnemyListWindow(Player *p, Enemy *e[], int eneNum, int magicNum, ComandType comandType) {
	this->player = p;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = e[i];
	}
	this->enemyNum = eneNum;
	this->magicNum = magicNum;
	this->comandType = comandType;
	this->liveNum = this->setEnemy();
	this->selectNum = 0;
	this->isHide = false;
	this->battleWindowStr = "";
}

int EnemyListWindow::setEnemy() {
	int liveNum = 0;
	for (int i = 0; i < this->enemyNum; i++) {
		if (this->enemy[i]->getHp() <= 0) {
			for (int j = i; j < this->enemyNum; j++) {
				if (this->enemy[j]->getHp() > 0) {
					Enemy *tmp = enemy[j];
					enemy[j] = enemy[i];
					enemy[i] = tmp;
					liveNum++;
					break;
				}
			}
		}
		else {
			liveNum++;
		}
	}

	return liveNum;
}

void EnemyListWindow::drawEnemyListWindow() {
	if (!this->isHide) {
		DrawBox(ENEMYLISTWINDOWX1, ENEMYLISTWINDOWY1, ENEMYLISTWINDOWX2, ENEMYLISTWINDOWY2, GetColor(0, 0, 0), true);
		for (int i = 0; i < this->liveNum; i++) {
			if (i == this->selectNum) {
				DrawFormatString(ENEMYLISTWINDOWX1, ENEMYLISTWINDOWY1 + ENEMYLISTWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", this->enemy[i]->getName().c_str());
			}
			else {
				DrawFormatString(ENEMYLISTWINDOWX1, ENEMYLISTWINDOWY1 + ENEMYLISTWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", this->enemy[i]->getName().c_str());
			}
		}
	}
}

void EnemyListWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->liveNum - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= this->liveNum) {
				this->selectNum = 0;
			}
		}
	}
}

bool EnemyListWindow::select() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			switch (this->comandType) {
			case TypeFight:
				this->player->attack(this->enemy[this->selectNum], &this->battleWindowStr);
				this->liveNum = this->setEnemy();
				break;
			case TypeMagic:
				if (this->player->getMagic(this->magicNum)->use(this->player, this->enemy[this->selectNum], &this->battleWindowStr) == false) {
					return false;
				}
				this->liveNum = this->setEnemy();
				break;
			}
			Key[KEY_INPUT_Z]++;

			return true;
		}
		else if (Key[KEY_INPUT_X] == 1) {
			this->init();
			Key[KEY_INPUT_X]++;
		}
	}

	return false;
}

bool EnemyListWindow::drawAll() {

	this->drawEnemyListWindow();
	this->moveSelector();
	return this->select();
}

void EnemyListWindow::init() {
	this->selectNum = 0;
	this->battleWindowStr = "";
	this->isHide = true;
}