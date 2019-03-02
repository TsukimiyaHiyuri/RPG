#include "EnemyListWindow.h"
#include "Key.h"
#include "DxLib.h"

EnemyListWindow::EnemyListWindow(Player *p, Enemy *e[], int eneNum, int magicNum, ComandType comandType, Sound *sound) {
	this->player = p;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = e[i];
	}
	this->enemyNum = eneNum;
	this->magicNum = magicNum;
	this->comandType = comandType;
	this->liveNum = this->setEnemy();
	this->sound = sound;
	this->selectNum = 0;
	this->isHide = false;
	this->battleWindowStr = "";
}

// 倒した敵を配列の後ろに入れ替える
// 生きている敵の数を返す
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

// 敵の一覧を表示する
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

// カーソル移動
void EnemyListWindow::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = this->liveNum - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= this->liveNum) {
				this->selectNum = 0;
			}
		}
	}
}

// 決定ボタン、キャンセルボタンを押されたときの処理
// コマンドが終わる時はtrueが返る
bool EnemyListWindow::select() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			// SEをならす
			this->sound->playSE(DecideSE, true);

			// コマンドウィンドウで「たたかう」を選んだときと「まほう」を選んだときの処理
			switch (this->comandType) {
			case TypeFight:
				// 選択した敵に攻撃して、バトルウィンドウの文字列を設定する
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
			
			return true;
		}
		else if (Key[KEY_INPUT_X] == 1) {
			Key[KEY_INPUT_X]++;

			// SEをならす
			this->sound->playSE(CancelSE, true);
			this->init();
		}
	}

	return false;
}

// 描画、カーソル移動、選択の処理をまとめたもの
// コマンドが終わったらtrueが返る
bool EnemyListWindow::drawAll() {
	this->drawEnemyListWindow();
	this->moveSelector();
	return this->select();
}

// 初期化関数
void EnemyListWindow::init() {
	this->selectNum = 0;
	this->battleWindowStr = "";
	this->isHide = true;
}