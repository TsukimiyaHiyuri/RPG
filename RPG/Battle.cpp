#include "Battle.h"
#include "Slime.h"
#include "WorldMap.h"
#include "Bat.h"
#include "DxLib.h"

Battle::Battle(Sound *sound) {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isMyTurn = true;
	this->isFinish = true;
	this->finishWindowFlag = false;
	this->isBoss = false;
	this->sound = sound;

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

		this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum, this->sound);	// コマンドウィンドウのインスタンスを生成
		this->battleWindow = new BattleWindow();
		this->finishWindow = new BattleWindow();
		this->isFinish = false;
		this->isMyTurn = true;
		return this->enemyNum;
	}
	return 0;
}

int Battle::bossEncount(Player *player) {
	// 敵の追加
	// 追加した敵の数をenemyNumに代入

	this->enemyNum = 1;
	this->enemy[0] = new Bat(WIDTH / (this->enemyNum * 2));

	this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum, this->sound);	// コマンドウィンドウのインスタンスを生成
	this->battleWindow = new BattleWindow();
	this->finishWindow = new BattleWindow();
	this->isFinish = false;
	this->isMyTurn = true;
	this->isBoss = true;
	return this->enemyNum;
	
	return 0;
}

void Battle::battle(Player *player, bool *clearFlag, Map *nowMap) {
	if (!this->isFinish) {
		this->drawStatus(player);

		for (int i = 0; i < this->enemyNum; i++) {
			this->enemy[i]->drawGraphic();
		}

		if (!this->battleWindow->strIsEmpty() && !this->battleWindow->getIsHide()) {
			this->battleWindow->drawBattleWindow();
		}
		else if (this->battleWindow->strIsEmpty() && !this->battleWindow->getIsHide()) {
			this->battleWindow->changeIsHide();
		}

		if (!this->finishWindow->strIsEmpty() && this->battleWindow->strIsEmpty()) {
			this->finishWindow->drawBattleWindow();
		}

		// 自分のターンだったらコマンドウィンドウを表示
		if (this->isMyTurn && this->battleWindow->strIsEmpty()) {
			this->isMyTurn = !this->comandWindow->drawAll();

			if (!this->isMyTurn) {
				
				this->sortEnemy();

				// 生きている敵の数を更新
				this->enemyNum = this->countLiveEnemy();

				this->battleWindow->setStr(this->comandWindow->getBattleWindowStr());
				this->battleWindow->changeIsHide();

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

			player->setHp(player->getMaxHp());
			player->setMp(player->getMaxMp());
			player->setGold(player->getGold() / 2);
			nowMap = new WorldMap();

			this->init();
		}
		else if (this->enemyNum <= 0 && this->finishWindow->strIsEmpty()) {
			if (this->finishWindowFlag) {
				if (this->isBoss) {
					*clearFlag = true;
				}
				this->init();
			}
			else if (battleWindow->getIsHide()) {
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

void Battle::drawStatus(Player *player) {
	DrawBox(STATUSX1, STATUSY1, STATUSX2, STATUSY2, GetColor(0, 0, 0), true);

	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10, GetColor(255, 255, 255), "%s", player->getName().c_str());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL, GetColor(255, 255, 255), "Lv: %d", player->getLv());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL*2, GetColor(255, 255, 255), "HP: %d", player->getHp());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL*3, GetColor(255, 255, 255), "MP: %d", player->getMp());
}