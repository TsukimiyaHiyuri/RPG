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
		// �G�̒ǉ�
		// �ǉ������G�̐���enemyNum�ɑ��

		this->enemyNum = 2;
		for (int i = 0; i < this->enemyNum; i++) {
			if (i == 0) {
				this->enemy[i] = new Slime(WIDTH / (this->enemyNum * 2));
			}
			else {
				this->enemy[i] = new Slime(this->enemy[i - 1]->getCordinateX() + (WIDTH / this->enemyNum));
			}
		}

		this->comandWindow = new ComandWindow(player, this->enemy, this->enemyNum);	// �R�}���h�E�B���h�E�̃C���X�^���X�𐶐�
		this->battleWindow = new BattleWindow();
		this->isFinish = false;
		this->isMyTurn = true;
		return this->enemyNum;
	}
	return 0;
}

void Battle::battle(Player *player) {
	if (!this->isFinish) {
		// �����̃^�[����������R�}���h�E�B���h�E��\��

		for (int i = 0; i < this->enemyNum; i++) {
			this->enemy[i]->drawGraphic();
		}

		if (!this->battleWindow->strIsEmpty()) {
			this->battleWindow->drawBattleWindow();
		}

		if (this->isMyTurn && this->battleWindow->strIsEmpty()) {
			this->isMyTurn = !this->comandWindow->drawAll();

			if (!this->isMyTurn) {
				
				this->sortEnemy();

				// �����Ă���G�̐����X�V
				this->enemyNum = this->countLiveEnemy();

				this->battleWindow->setStr("�e�X�g����`");

				// �R�}���h�E�B���h�E�̏�����
				this->comandWindow->init();
			}
		}
		else {
			if (this->lookEnemyNum < this->enemyNum) {
				if (this->battleWindow->strIsEmpty()) {
					this->battleWindow->setStr("�G����̍U������`");
					this->lookEnemyNum++;
					if (this->lookEnemyNum >= enemyNum) {

						this->lookEnemyNum = 0;

						// �����̃^�[���ɐ؂�ւ���
						this->isMyTurn = true;
					}
				}
				else {
					;
				}
			}
		}

		if (player->getHp() <= 0) {
			// �Q�[���I�[�o�[�̏���
			this->init();
		}
		else if (this->enemyNum <= 0) {
			// �|�����G�̌o���l�Ƃ������v���C���[�ɉ��Z
			player->addExp(this->exp);
			player->addGold(this->gold);
			this->init();
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

void Battle::init() {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isFinish = true;
}