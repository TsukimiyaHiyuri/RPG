#include "Battle.h"
#include "Slime.h"

Battle::Battle() {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isMyTurn = true;
	this->isFinish = true;
	this->finishWindowFlag = false;
	
	for (int i = 0; i < MAXENEMYNUM; i++) {
		this->enemy[i] = new Enemy();
	}
}

int Battle::encount(Player *player, Map *nowMap) {
	if (nowMap->getIsEncount() && this->isFinish == true) {
		// 敵の追加
		// 追加した敵の数をenemyNumに代入

		this->enemyNum = (rand() % 3) + 1;
		for (int i = 0; i < this->enemyNum; i++) {
			if (i == 0) {
				this->enemy[i] = nowMap->getEnemy(rand() % nowMap->getEnemyNum(), WIDTH / (this->enemyNum * 2));
			}
			else {
				this->enemy[i] = nowMap->getEnemy(rand() % nowMap->getEnemyNum(), this->enemy[i - 1]->getCordinateX() + (WIDTH / this->enemyNum));
			}
		}

		this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum);	// コマンドウィンドウのインスタンスを生成
		this->battleWindow = new BattleWindow();
		this->finishWindow = new BattleWindow();
		this->isFinish = false;
		this->isMyTurn = true;
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

		if (!this->battleWindow->strIsEmpty()) {
			this->battleWindow->drawBattleWindow();
		}
		if (!this->finishWindow->strIsEmpty() && this->battleWindow->strIsEmpty()) {
			this->finishWindow->drawBattleWindow();
		}

		if (this->isMyTurn && this->battleWindow->strIsEmpty()) {
			this->isMyTurn = !this->comandWindow->drawAll();

			if (!this->isMyTurn) {
				
				this->sortEnemy();

				// 生きている敵の数を更新
				this->enemyNum = this->countLiveEnemy();

				this->battleWindow->setStr(this->comandWindow->getBattleWindowStr());

				// コマンドウィンドウの初期化
				this->comandWindow->init();
			}
		}
		else {
			if (this->lookEnemyNum < this->enemyNum) {
				if (this->battleWindow->strIsEmpty()) {
					this->battleWindow->setStr(enemy[this->lookEnemyNum]->attack(player));
					this->lookEnemyNum++;
					if (this->lookEnemyNum >= enemyNum) {

						this->lookEnemyNum = 0;

						// 自分のターンに切り替える
						this->isMyTurn = true;
					}
				}
			}
		}

		if (player->getHp() <= 0 && this->battleWindow->strIsEmpty()) {
			// ゲームオーバーの処理
			this->init();
		}
		else if (this->enemyNum <= 0 && this->finishWindow->strIsEmpty()) {
			if (this->finishWindowFlag) {
				this->init();
			}
			else {
				// 倒した敵の経験値とお金をプレイヤーに加算
				player->addExp(this->exp);
				player->addGold(this->gold);

				std::string tmp;
				tmp = "経験値" + std::to_string(this->exp) + "と" + std::to_string(this->gold) + "ゴールドを獲得！\n";

				/* レベルアップの処理 */
				player->levelUp(&tmp);

				this->finishWindow->setStr(tmp);
				this->finishWindowFlag = true;
			}
		}
	}
}

// 生きてる敵を先頭に持ってくる
void Battle::sortEnemy() {
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
}

int Battle::countLiveEnemy() {
	int liveNum = 0;

	// 死んでいる敵が所持している経験値とお金を蓄積
	for (int i = 0; i < this->enemyNum; i++) {
		if (this->enemy[i]->getHp() > 0) {
			liveNum++;
		}
		else {
			this->exp += this->enemy[i]->getExp();
			this->gold += this->enemy[i]->getGold();
		}
	}
	return liveNum;
}

void Battle::battleFinish() {
	
}

void Battle::init() {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isFinish = true;
	this->finishWindowFlag = false;
}