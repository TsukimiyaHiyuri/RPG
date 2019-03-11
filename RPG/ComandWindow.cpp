#include "ComandWindow.h"
#include "Key.h"
#include "DxLib.h"

// コンストラクタ
ComandWindow::ComandWindow(Player *player, Enemy *enemy[], int enemyNum, Sound *sound) {
	this->player = player;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = enemy[i];
	}
	this->enemyNum = enemyNum;
	this->isFinish = false;
	this->isHide = false;
	this->isEscape = false;
	this->selectNum = 0;
	this->setList();
	this->sound = sound;
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
			DrawFormatString(COMANDWINDOWX1 + 5, COMANDWINDOWY1 + 5 + COMANDWINDOWINTERBAL * i, GetColor(0, 255, 255), "%s", list[i].c_str());
		}
		else {
			DrawFormatString(COMANDWINDOWX1 + 5, COMANDWINDOWY1 + 5 + COMANDWINDOWINTERBAL * i, GetColor(255, 255, 255), "%s", list[i].c_str());
		}
	}
}

// 現在選択している項目の移動
void ComandWindow::moveSelector() {
	if (!this->isHide && this->enemyListWindow->getIsHide() && this->itemWindow->getIsHide() && this->magicWindow->getIsHide()) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);
			
			// カーソルを動かす
			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = COMANDTYPENUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			// カーソルを動かす
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

			// SEをならす
			this->sound->playSE(DecideSE, true);

			switch (this->selectNum) {
			case TypeFight:
				delete this->enemyListWindow;
				this->enemyListWindow = new EnemyListWindow(
					this->player,
					this->enemy,
					this->enemyNum,
					-1,
					TypeFight,
					this->sound
				);
				return false;

			case TypeMagic:
				delete this->magicWindow;
				this->magicWindow = new MagicWindow(this->player, this->enemy, this->enemyNum, this->sound);
				return false;

			case TypeItem:
				delete this->itemWindow;
				this->itemWindow = new ItemWindow(this->player, this->sound);
				return false;

			case TypeEscape:
				this->escape();
				return true;

			}
		}
	}
	return false;
}

// 描画やキーの監視をまとめたもの
// コマンド入力が終わったかを返す
bool ComandWindow::drawAll() {
	this->drawComandWindow();
	this->moveSelector();

	bool isFinish = this->select();

	// 各ウィンドウの描画
	if (!isFinish) {
		isFinish = this->enemyListWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->magicWindow->drawAll();
	}
	if (!isFinish) {
		isFinish = this->itemWindow->drawAll();
	}

	// バトルウィンドウの内容を設定
	if (this->battleWindowStr.empty()) {
		this->battleWindowStr = this->enemyListWindow->getBattleWindowStr();
	}
	if (this->battleWindowStr.empty()) {
		this->battleWindowStr = this->magicWindow->getBattleWindowStr();
	}
	if (this->battleWindowStr.empty()) {
		this->battleWindowStr = this->itemWindow->getBattleWindowStr();
	}

	return isFinish;
}

// 各パラメータを初期値に戻す
void ComandWindow::init() {
	this->selectNum = 0;
	this->enemyListWindow->init();
	this->itemWindow->init();
	this->magicWindow->init();
	this->battleWindowStr = "";
	this->isEscape = false;
}

void ComandWindow::escape() {
	this->isEscape = true;
}