#include "Player.h"
#include "Dim.h"
#include "DxLib.h"
#include "Map.h"
#include "Key.h"

int moveX, moveY;
Player *player[PLAYERNUM];

Player::Player(Sound *sound) {
	// statusの初期値
	this->status.name = "勇者";
	this->status.lv = 1;
	this->status.maxHp = 20;
	this->status.maxMp = 5;
	this->status.hp = 20;
	this->status.mp = 5;
	this->status.str = 10;
	this->status.def = 10;
	this->status.exp = 0;
	this->status.gold = 100;

	// 所持品系の初期値
	this->belongingsNum = 0;
	this->armor = false;
	this->weapon = false;
	this->weaponStr = 0;
	this->weaponDef = 0;
	this->armorStr = 0;
	this->armorDef = 0;
	
	// 描画系の初期値
	this->direction = UP;
	this->isMove = false;
	setPlayer(10, 10);
	moveX = 0, moveY = 0;
	loadGraphic();

	// 魔法系の初期値
	this->learnMagicNum = 0;

	this->isSpeak = false;
	this->setLevelTable();

	this->sound = sound;
}

// 各キー入力にしたがって移動方向を取得
void Player::move() {
	if (Key[KEY_INPUT_RIGHT] >= 1 && !this->isMove) {
		moveX += 1;
		this->direction = RIGHT;
		this->isMove = true;
	}
	if (Key[KEY_INPUT_LEFT] >= 1 && !this->isMove) {
		moveX -= 1;
		this->direction = LEFT;
		this->isMove = true;
	}
	if (Key[KEY_INPUT_DOWN] >= 1 && !this->isMove) {
		moveY += 1;
		this->direction = DOWN;
		this->isMove = true;
	}
	if (Key[KEY_INPUT_UP] >= 1 && !this->isMove) {
		moveY -= 1;
		this->direction = UP;
		this->isMove = true;
	}
}

void Player::stop() {
	moveX = 0, moveY = 0;
	this->isMove = false;
}

// 主人公のマップチップをロード
void Player::loadGraphic() {
	LoadDivGraph("歩行ドットキャラ.bmp", 3 * 4, 3, 4, 32, 32, this->graphic);//画像を分割してimage配列に保存
}

// 主人公の描画
void Player::drawHero(int *moveCounter) {
	// 動いてるときはアニメーション
	if (this->isMove) {
		if (*moveCounter < MOVE_FRAME / 3) {
			DrawGraph(320, 220, graphic[this->direction - 1], TRUE);
		}
		else if (*moveCounter > MOVE_FRAME - (MOVE_FRAME / 3)) {
			DrawGraph(320, 220, graphic[this->direction + 1], TRUE);
		}
		else {
			DrawGraph(320, 220, graphic[this->direction], TRUE);
		}
	}
	else {
		DrawGraph(320, 220, graphic[this->direction], TRUE);
	}
}

// スクロール量を計算してスクロール終了時にプレイヤーの座標を移動
void Player::scroll(int *MoveCounter, int *ScrollX, int *ScrollY, int *EncountNum) {
	if(this->isMove) {
		*MoveCounter += 1;

		// 移動処理が終了したら停止中にする
		if (*MoveCounter == MOVE_FRAME) {
			isMove = false;

			// プレイヤーの位置を変更する
			this->position.x += moveX;
			this->position.y += moveY;

			moveX = 0, moveY = 0;
			*MoveCounter = 0;

			*EncountNum += 1;

			// 停止中は画面のスクロールは行わない
			*ScrollX = 0;
			*ScrollY = 0;
		}
		else {
			// 経過時間からスクロール量を算出する
			*ScrollX = -(moveX * MAP_SIZE * *MoveCounter / MOVE_FRAME);
			*ScrollY = -(moveY * MAP_SIZE * *MoveCounter / MOVE_FRAME);
		}
	}
}

// プレイヤーの座標のセッタ
void Player::setPlayer(int x, int y) {
	this->position.x = x;
	this->position.y = y;
}

// 所持品がいっぱいじゃなかったら引数のアイテムを所持させる
void Player::addBelongings(Item *item) {
  	if (this->getBelongingsNum() < MAXBELONGINGS) {
		this->belongings[this->getBelongingsNum()] = item;
		this->setBelongingsNum(this->getBelongingsNum() + 1);
	}
}

// 所持しているアイテムを売却する
bool Player::sellItem(int n) {
	if (this->getBelongingsNum() > 0 && !this->belongings[n]->getIsEquip()) {
		this->status.gold += this->belongings[n]->getSellGold();
		this->throwItem(n);
		return true;
	}
	return false;
}

// アイテムを購入する
void Player::buyItem(Item *item) {
	if (this->status.gold >= item->getBuyGold() && this->getBelongingsNum() < MAXBELONGINGS) {
		this->status.gold -= item->getBuyGold();
		item->addBelongings(this);
	}
}

// 指定された番号のアイテムを指定されたプレイヤーに使用する
// 使用したアイテムはなくなる
void Player::useItem(int n, Player *p) {
	if (!this->belongings[n]->getCanEquip()) {
		this->belongings[n]->use(p);

		this->throwItem(n);
	}
}

// アイテムを捨てる
void Player::throwItem(int n) {
	if (!this->belongings[n]->getIsEquip()) {
		for (int i = n; i < MAXBELONGINGS - 1; i++) {
			this->belongings[i] = this->belongings[i + 1];
		}

		this->setBelongingsNum(this->getBelongingsNum() - 1);
	}
}

// アイテムを装備する
void Player::equipItem(int n, Player *from) {
	if (!this->belongings[n]->getCanUse()) {
		if (this->belongings[n]->getIsEquip()) {
			this->belongings[n]->changeIsEquript();
			this->belongings[n]->remove(this);
			if (this->belongings[n]->getType() == Weapon) {
				this->weapon = false;
			}
			else if(this->belongings[n]->getType() == Armor) {
				this->armor = false;
			}
		}
		else if (this->weapon && this->belongings[n]->getType() == Weapon) {
			for (int i = 0; i < this->belongingsNum; i++) {
				if (this->belongings[i]->getIsEquip() && this->belongings[i]->getType() == Weapon) {
					this->belongings[i]->changeIsEquript();
					this->belongings[i]->remove(this);
				}
			}
			this->belongings[n]->changeIsEquript();
			this->belongings[n]->equip(this);
		}
		else if (this->armor && this->belongings[n]->getType() == Armor) {
			for (int i = 0; i < this->belongingsNum; i++) {
				if (this->belongings[i]->getIsEquip() && this->belongings[i]->getType() == Armor) {
					this->belongings[i]->changeIsEquript();
					this->belongings[i]->remove(this);
				}
			}
			this->belongings[n]->changeIsEquript();
			this->belongings[n]->equip(this);
		}
		else {
			if (this->belongings[n]->getType() == Armor) {
				this->belongings[n]->equip(this);
				this->belongings[n]->changeIsEquript();
				this->armor = true;
			}
			else if (this->belongings[n]->getType() == Weapon) {
				this->belongings[n]->equip(this);
				this->belongings[n]->changeIsEquript();
				this->weapon = true;
			}
		}
	}
}

// 装備を含めたSTRステータスの値を返す
int Player::getAllStr() {
	return this->status.str + this->weaponStr + this->armorStr;
}

// 引数の敵に攻撃する
void Player::attack(Enemy *e, std::string *n) {
	// SEをならす
	this->sound->playSE(AttackSE, true);
	int damage = this->getAllStr() - e->getDef() > 1 ? this->getAllStr() - e->getDef() : 1;
	e->damage(damage);

	*n = this->getName() + "の攻撃！\n";
	*n += e->getName() + "に" + std::to_string(damage) + "のダメージ！";
}

// 引数の魔法を習得する
void Player::learnMagic(Magic *magic) {
	this->magic[this->learnMagicNum] = magic;
	this->learnMagicNum++;
}

// レベルテーブルを設定する
void Player::setLevelTable() {
	for (int i = 0; i < MAXLEVEL - 1; i++) {
		this->levelTable[i] = (i + 1) * 6;
	}
}

// レベルアップ時の関数
void Player::levelUp(std::string *s) {
	if (this->status.exp >= this->levelTable[this->status.lv - 1]) {
		// レベルアップのSEをならす
		this->sound->playSE(LevelUpSE, false);

		// レベルをひとつあげる
		this->status.lv++;

		// 各ステータスを上げる
		this->addMaxHp(15);
		this->addMaxMp(5);
		this->addStr(3);
		this->addDef(2);
		this->setHp(this->getMaxHp());
		this->setMp(this->getMaxMp());

		*s += this->getName() + "は Lv" + std::to_string(this->getLv()) + " になった！\n";

		// レベルによって魔法を習得
		switch (this->getLv()) {
		case 2:
			this->learnMagic(new Fire());
			*s += this->magic[this->learnMagicNum - 1]->getName() + "の魔法を習得した！\n";
			break;
		case 5:
			this->learnMagic(new Thunder());
			*s += this->magic[this->learnMagicNum - 1]->getName() + "の魔法を習得した！\n";
			break;
		}
	}
}