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
		// �G�̒ǉ�
		// �ǉ������G�̐���enemyNum�ɑ��

		this->enemyNum = (rand() % 3) + 1;
		for (int i = 0; i < this->enemyNum; i++) {
			if (i == 0) {
				this->enemy[i] = nowMap->getEnemy(rand() % nowMap->getEnemyNum(), WIDTH / (this->enemyNum * 2));
			}
			else {
				this->enemy[i] = nowMap->getEnemy(rand() % nowMap->getEnemyNum(), this->enemy[i - 1]->getCordinateX() + (WIDTH / this->enemyNum));
			}
		}

		this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum, this->sound);	// �R�}���h�E�B���h�E�̃C���X�^���X�𐶐�
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
	// �G�̒ǉ�
	// �ǉ������G�̐���enemyNum�ɑ��

	this->enemyNum = 1;
	this->enemy[0] = new BossEnemy(WIDTH / (this->enemyNum * 2), this->sound);

	this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum, this->sound);	// �R�}���h�E�B���h�E�̃C���X�^���X�𐶐�
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
		// �v���C���[�̃X�e�[�^�X��`��
		this->drawStatus(player);

		// �G��`��
		for (int i = 0; i < this->enemyNum; i++) {
			this->enemy[i]->drawGraphic();
		}

		// �o�g���E�B���h�E�̕`��
		this->battleWindow->drawBattleWindow();

		// �Ō�̃E�B���h�E�̕`��
		if (this->battleWindow->strIsEmpty()) {
			this->finishWindow->drawBattleWindow();
		}

		// �����̃^�[����������R�}���h�E�B���h�E��\��
		if (this->isMyTurn && this->battleWindow->strIsEmpty()) {
			this->isMyTurn = !this->comandWindow->drawAll();

			if (!this->isMyTurn) {
				
				this->sortEnemy();

				// �����Ă���G�̐����X�V
				this->enemyNum = this->countLiveEnemy();

				// �o�g���E�B���h�E�̕������ݒ�
				this->battleWindow->setStr(this->comandWindow->getBattleWindowStr());
				this->escape(player);

				// �R�}���h�E�B���h�E�̏�����
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

						// �����̃^�[���ɐ؂�ւ���
						this->isMyTurn = true;
					}
				}
			}
		}

		// �Q�[���I�[�o�[�̏���
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

// �����Ă�G��擪�Ɏ����Ă���
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

// �����Ă�G�𐔂���
int Battle::countLiveEnemy() {
	int liveNum = 0;

	// ����ł���G���������Ă���o���l�Ƃ�����~��
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

// �������֐�
void Battle::init() {
	// �������̉��
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

// �X�e�[�^�X�̕`��
void Battle::drawStatus(Player *player) {
	DrawBox(STATUSX1, STATUSY1, STATUSX2, STATUSY2, GetColor(0, 0, 0), true);

	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10, GetColor(255, 255, 255), "%s", player->getName().c_str());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL, GetColor(255, 255, 255), "Lv: %d", player->getLv());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL*2, GetColor(255, 255, 255), "HP: %d", player->getHp());
	DrawFormatString(STATUSX1 + 10, STATUSY1 + 10 + STATUSINTERBAL*3, GetColor(255, 255, 255), "MP: %d", player->getMp());
}

// �������I�������Ƃ��̃o�g���E�B���h�E�̕�����ݒ�
void Battle::escape(Player *player) {
	if (this->comandWindow->getIsEscape()) {
		if (this->isBoss) {
			this->battleWindow->setStr(player->getName() + "�͓����o�����I\n�������������Ȃ������I");
			this->battleWindow->changeIsHide();
		}
		else {
			this->finishWindow->setStr(player->getName() + "�͓����o�����I");
			this->finishWindowFlag = true;
			this->isEscape = true;
			this->finishWindow->changeIsHide();
		}
	}
}

// �Q�[���I�[�o�[�̏���
void Battle::gameOver(Player *player, Map *nowMap) {
	if (player->getHp() <= 0 && this->battleWindow->strIsEmpty()) {
		// �Q�[���I�[�o�[�̏���

		player->setHp(player->getMaxHp());
		player->setMp(player->getMaxMp());
		player->setGold(player->getGold() / 2);
		delete nowMap;
		nowMap = new WorldMap(this->sound);

		this->init();
	}
}

// �퓬�I�����̏���
void Battle::finishAction(Player *player) {
	// �|�����G�̌o���l�Ƃ������v���C���[�ɉ��Z
	player->addExp(this->exp);
	player->addGold(this->gold);

	std::string finishWindowStr;
	finishWindowStr = "�o���l" + std::to_string(this->exp) + "��" + std::to_string(this->gold) + "�S�[���h���l���I\n";

	// ���x���A�b�v�̏��� 
	player->levelUp(&finishWindowStr);

	this->finishWindow->setStr(finishWindowStr);
	this->finishWindowFlag = true;
}