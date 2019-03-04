#include "Battle.h"
#include "Slime.h"
#include "WorldMap.h"
#include "Bat.h"
#include "BossEnemy.h"
#include "DxLib.h"

Battle::Battle(Sound *sound) {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->originEnemyNum = 0;
	this->isMyTurn = true;
	this->isFinish = true;
	this->finishWindowFlag = false;
	this->isBoss = false;
	this->sound = sound;
	this->isEscape = false;

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
		this->originEnemyNum = this->enemyNum;
		return this->enemyNum;
	}
	return 0;
}

int Battle::bossEncount(Player *player) {
	// 敵の追加
	// 追加した敵の数をenemyNumに代入

	this->enemyNum = 1;
	this->enemy[0] = new BossEnemy(WIDTH / (this->enemyNum * 2), this->sound);

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
		// プレイヤーのステータスを描画
		this->drawStatus(player);

		// 敵を描画
		for (int i = 0; i < this->enemyNum; i++) {
			this->enemy[i]->drawGraphic();
		}

		// バトルウィンドウの描画
		this->battleWindow->drawBattleWindow();

		// 最後のウィンドウの描画
		if (this->battleWindow->strIsEmpty()) {
			this->finishWindow->drawBattleWindow();
		}

		// 自分のターンだったらコマンドウィンドウを表示
		if (this->isMyTurn && this->battleWindow->strIsEmpty()) {
			this->isMyTurn = !this->comandWindow->drawAll();

			if (!this->isMyTurn) {
				
				this->sortEnemy();

				// 生きている敵の数を更新
				this->enemyNum = this->countLiveEnemy();

				// バトルウィンドウの文字列を設定
				this->battleWindow->setStr(this->comandWindow->getBattleWindowStr());
				this->escape(player);

				// コマンドウィンドウの初期化
				this->comandWindow->init();
			}
		}
		else {
			if (this->lookEnemyNum < this->enemyNum) {
				if (this->battleWindow->strIsEmpty() && !this->isEscape) {
					this->battleWindow->setStr(enemy[this->lookEnemyNum]->attack(player));
					this->lookEnemyNum++;

					if (this->lookEnemyNum >= this->enemyNum) {
						this->lookEnemyNum = 0;

						// 自分のターンに切り替える
						this->isMyTurn = true;
					}
				}
			}
		}

		// ゲームオーバーの処理
		this->gameOver(player, nowMap);

		if ((this->enemyNum <= 0 || this->isEscape) && this->finishWindow->strIsEmpty()) {
			if (this->finishWindowFlag) {
				if (this->isBoss) {
					*clearFlag = true;
				}
				this->init();
			}
			else if (battleWindow->strIsEmpty()) {
				this->finishAction(player);
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

// 生きてる敵を数える
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

// 初期化関数
void Battle::init() {
	// メモリの解放
	for (int i = 0; i < this->originEnemyNum; i++) {
		delete this->enemy[i];
	}
	delete this->battleWindow;
	delete this->comandWindow;
	delete this->finishWindow;

	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->originEnemyNum = 0;
	this->isFinish = true;
	this->isBoss = false;
	this->finishWindowFlag = false;
	this->isEscape = false;
}

// ステータスの描画
void Battle::drawStatus(Player *player) {
	DrawBox(STATUSX1, STATUSY1, STATUSX2, STATUSY2, GetColor(0, 0, 0), true);

	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10, GetColor(255, 255, 255), "%s", player->getName().c_str());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL, GetColor(255, 255, 255), "Lv: %d", player->getLv());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL*2, GetColor(255, 255, 255), "HP: %d", player->getHp());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL*3, GetColor(255, 255, 255), "MP: %d", player->getMp());
}

// 逃げるを選択したときのバトルウィンドウの文字列設定
void Battle::escape(Player *player) {
	if (this->comandWindow->getIsEscape()) {
		if (this->isBoss) {
			this->battleWindow->setStr(player->getName() + "は逃げ出した！\nしかし逃げられなかった！");
			this->battleWindow->changeIsHide();
		}
		else {
			this->finishWindow->setStr(player->getName() + "は逃げ出した！");
			this->finishWindowFlag = true;
			this->isEscape = true;
			this->finishWindow->changeIsHide();
		}
	}
}

// ゲームオーバーの処理
void Battle::gameOver(Player *player, Map *nowMap) {
	if (player->getHp() <= 0 && this->battleWindow->strIsEmpty()) {
		// ゲームオーバーの処理

		player->setHp(player->getMaxHp());
		player->setMp(player->getMaxMp());
		player->setGold(player->getGold() / 2);
		delete nowMap;
		nowMap = new WorldMap(this->sound);

		this->init();
	}
}

// 戦闘終了時の処理
void Battle::finishAction(Player *player) {
	// 倒した敵の経験値とお金をプレイヤーに加算
	player->addExp(this->exp);
	player->addGold(this->gold);

	std::string finishWindowStr;
	finishWindowStr = "経験値" + std::to_string(this->exp) + "と" + std::to_string(this->gold) + "ゴールドを獲得！\n";

	// レベルアップの処理 
	player->levelUp(&finishWindowStr);

	this->finishWindow->setStr(finishWindowStr);
	this->finishWindowFlag = true;
}