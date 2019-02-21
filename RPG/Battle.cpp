#include "Battle.h"
#include "Slime.h"

Battle::Battle() {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isMyTurn = true;
	this->isFinish = true;
	
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = new Enemy();
	}
}

int Battle::encount(Player *player, Map *nowMap) {
	if (nowMap->getIsEncount() && this->isFinish == true) {
		// 敵の追加
		// 追加した敵の数をenemyNumに代入

		this->enemyNum = 2;
		for (int i = 0; i < this->enemyNum; i++) {
			if (i == 0) {
				this->enemy[i] = new Slime(WIDTH / (this->enemyNum * 2));
			}
			else {
				this->enemy[i] = new Slime(this->enemy[i - 1]->getCordinateX() + (WIDTH / this->enemyNum));
			}
		}

		this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum);	// コマンドウィンドウのインスタンスを生成
		this->isFinish = false;
		return this->enemyNum;
	}
	return 0;
}

void Battle::battle(Player *player) {
	if (!this->isFinish) {
		// 自分のターンだったらコマンドウィンドウを表示

		for (int i = 0; i < this->enemyNum; i++) {
			this->enemy[i]->drawGraphic();
		}

		if (this->isMyTurn) {
			this->isMyTurn = !this->comandWindow->drawAll();
		}
		else {
			// コマンドウィンドウの初期化
			this->comandWindow->init();

			int liveNum = 0;

			// 生きてる敵を先頭に持ってくる
			for (int i = 0; i < this->enemyNum; i++) {
				if (this->enemy[i]->getHp() <= 0) {
					for (int j = i; j < this->enemyNum; j++) {
						if (this->enemy[j]->getHp() > 0) {
							Enemy *tmp = enemy[j];
							enemy[j] = enemy[i];
							enemy[i] = tmp;
						}
					}
				}
			}

			// 生きている敵からの攻撃を実行
			// 死んでいる敵が所持している経験値とお金を蓄積
			for (int i = 0; i < this->enemyNum; i++) {
				if (this->enemy[i]->getHp() > 0) {

					this->enemy[i]->attack(player);

					liveNum++;
				}
				else {
					this->exp += this->enemy[i]->getExp();
					this->gold += this->enemy[i]->getGold();
				}
			}

			// 自分のターンに切り替える
			this->isMyTurn = true;

			// 生きている敵の数を更新
			this->enemyNum = liveNum;
		}

		if (player->getHp() <= 0) {
			// ゲームオーバーの処理
			this->init();
		}
		else if (this->enemyNum <= 0) {
			// 倒した敵の経験値とお金をプレイヤーに加算
			player->addExp(this->exp);
			player->addGold(this->gold);
			this->init();
		}
	}
}

void Battle::init() {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isFinish = true;
}