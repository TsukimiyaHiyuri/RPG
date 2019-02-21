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
		this->isFinish = false;
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

		if (this->isMyTurn) {
			this->isMyTurn = !this->comandWindow->drawAll();
		}
		else {
			// �R�}���h�E�B���h�E�̏�����
			this->comandWindow->init();

			int liveNum = 0;

			// �����Ă�G��擪�Ɏ����Ă���
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

			// �����Ă���G����̍U�������s
			// ����ł���G���������Ă���o���l�Ƃ�����~��
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

			// �����̃^�[���ɐ؂�ւ���
			this->isMyTurn = true;

			// �����Ă���G�̐����X�V
			this->enemyNum = liveNum;
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

void Battle::init() {
	this->gold = 0;
	this->exp = 0;
	this->enemyNum = 0;
	this->isFinish = true;
}