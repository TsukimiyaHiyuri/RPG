#include "ComandWindow.h"
#include "Key.h"
#include "DxLib.h"

// コンストラクタ
ComandWindow::ComandWindow(Player *player, Enemy *enemy[], int enemyNum) {
	this->player = player;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = enemy[i];
	}
	this->enemyNum = enemyNum;
	this->isFinish = false;
	this->isHide = false;
	this->selectNum = 0;
	this->setList();
	this->enemyListWindow = new EnemyListWindow();
	this->itemWindow = new ItemWindow();
	this->magicWindow = new MagicWindow();
}

// 描画する文字列を設定
void ComandWindow::setList() {
	this->list = std::vector<std::string>(COMANDTYPENUM);
	this->list[TypeFight] = "たたかう";
	this->list[TypeMagic] = "まほう";
	this->list[TypeItem] = "どうぐ";
	this->list[TypeEscape] = "にげる";
}

// コマンドの項目を描画
void ComandWindow::drawComandWindow() {
	DrawBox(COMANDWINDOWX1, COMANDWINDOWY1, COMANDWINDOWX2, COMANDWINDOWY2, GetColor(0, 0, 0), true);

	for (int i = 0; i < this->list.size(); i++) {
		if (i == this->selectNum) {
			DrawFormatString(COMANDWINDOWX1, COMANDWINDOWY1 + COMANDWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", list[i].c_str());
		}
		else {
			DrawFormatString(COMANDWINDOWX1, COMANDWINDOWY1 + COMANDWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
		}
	}
}

// 現在選択している項目の移動
void ComandWindow::moveSelector() {
	if (!this->isHide && this->enemyListWindow->getIsHide() && this->itemWindow->getIsHide() && this->magicWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = COMANDTYPENUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			this->selectNum++;
			if (this->selectNum >= COMANDTYPENUM) {
				this->selectNum = 0;
			}
		}
	}
}

// 決定キーを押されたときの処理
bool ComandWindow::select() {
	if (!this->isHide && this->enemyListWindow->getIsHide() && this->itemWindow->getIsHide() && this->magicWindow->getIsHide()) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			switch (this->selectNum) {
			case TypeFight:
				this->enemyListWindow = new EnemyListWindow(
					this->player,
					this->enemy,
					this->enemyNum,
					-1,
					TypeFight
				);
				return false;

			case TypeMagic:
				this->magicWindow = new MagicWindow(this->player, this->enemy, this->enemyNum);
				return false;

			case TypeItem:
				this->itemWindow = new ItemWindow(this->player);
				return false;

			case TypeEscape:
				return true;

			}
		}
	}
	return false;
}

// 描画やキーの監視をまとめたもの
bool ComandWindow::drawAll() {
	this->drawComandWindow();
	this->moveSelector();

	bool isFinish = this->select();

	if (!isFinish) {
		isFinish = this->enemyListWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->magicWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->itemWindow->drawAll();
	}

	return isFinish;
}

// 各パラメータを初期値に戻す
void ComandWindow::init() {
	this->selectNum = 0;
	this->enemyListWindow->init();
	this->itemWindow->init();
	this->magicWindow->init();
}