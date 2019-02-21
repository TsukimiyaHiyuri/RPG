#include "MagicWindow.h"
#include "Key.h"
#include "DxLib.h"

MagicWindow::MagicWindow() {
	this->isHide = true;
	this->enemyListWindow = new EnemyListWindow();
}

MagicWindow::MagicWindow(Player *player, Enemy *enemy[], int enemyNum) {
	this->player = player;

	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = enemy[i];
	}

	this->enemyNum = enemyNum;
	this->isHide = false;
	this->selectNum = 0;
	this->enemyListWindow = new EnemyListWindow();
}

void MagicWindow::drawMagicWindow() {
	if (!this->isHide) {
		DrawBox(MAGICWINDOWX1, MAGICWINDOWY1, MAGICWINDOWX2, MAGICWINDOWY2, GetColor(0, 0, 0), true);

		for (int i = 0; i < this->player->getLearnMagicNum(); i++) {
			if (i == this->selectNum) {
				DrawFormatString(MAGICWINDOWX1, MAGICWINDOWY1 + MAGICWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", this->player->getMagic(i)->getName().c_str());
			}
			else {
				DrawFormatString(MAGICWINDOWX1, MAGICWINDOWY1 + MAGICWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", this->player->getMagic(i)->getName().c_str());
			}

			/* –‚–@‚Ìà–¾—“‚Ì•`‰æ‚Í‚±‚±‚É‹L“ü */

		}
	}
}

void MagicWindow::moveSelector() {
	if (!this->isHide && this->enemyListWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->player->getLearnMagicNum() - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= this->player->getLearnMagicNum()) {
				this->selectNum = 0;
			}
		}
	}
}

bool MagicWindow::selsect() {
	if (!this->isHide && this->enemyListWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1 && this->player->getLearnMagicNum() > 0) {
			Key[KEY_INPUT_Z]++;

			MagicType tmp = this->player->getMagic(this->selectNum)->getType();
			
			switch (tmp) {
			case AttackSolo:
				this->enemyListWindow = new EnemyListWindow(
					this->player,
					this->enemy,
					this->enemyNum,
					this->selectNum,
					TypeMagic
				);
				return false;

			case AttackAll:
				return this->player->getMagic(this->selectNum)->use(this->player, this->enemy);

			case CureSolo:
				return this->player->getMagic(this->selectNum)->use(this->player);
				

			case CureAll:
				return this->player->getMagic(this->selectNum)->use(this->player);
				
			}
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			this->init();
		}
	}
	return false;
}

bool MagicWindow::drawAll() {
	this->drawMagicWindow();
	this->moveSelector();
	if (this->enemyListWindow->drawAll()) {
		return true;
	}
	return this->selsect();
}

void MagicWindow::init() {
	this->isHide = true;
	this->selectNum = 0;
	this->enemyListWindow->init();
}