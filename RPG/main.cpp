#include "DxLib.h"
#include "Map.h"
#include "WorldMap.h"
#include "TownMap.h"
#include "Player.h"
#include "Key.h"
#include "Potion.h"
#include "Armors.h"
#include "HighPotion.h"
#include "MenuWindow.h"
#include "EquipmentWindow.h"
#include "Sord.h"
#include "Battle.h"
#include "BackGround.h"
#include <vector>
#include <string>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	int mapNum = World;
	nowMap = new WorldMap();
	int ScrollX = 0, ScrollY = 0;
	int moveCounter = 0;

	int moveEncountNum = 0;
	player[0] = new Player();
	player[1] = new Player();
	player[2] = new Player();

	Potion *p = new Potion();
	HighPotion *hp = new HighPotion();
	Sord *sord = new Sord();
	Armors *armors = new Armors();
	MenuWindow window = MenuWindow(player[0]);

	Battle *tmp = new Battle();

	BackGround *bg = new BackGround();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && updatekey() == 0) {

		// ��l���̈ړ�
		if (tmp->getIsFinish()) {
			if (window.getIsHide() && !player[0]->getIsSpeak()) {
				player[0]->move();

				// ��(��Q��)�Ƃ̂����蔻��
				// ����������~�܂�
				if (nowMap->judgeWall(player[0]->gety() + moveY, player[0]->getx() + moveX)) {
					player[0]->stop();
				}

				// �ړ����̃X�N���[���̌v�Z
				player[0]->scroll(&moveCounter, &ScrollX, &ScrollY, &moveEncountNum);
			}

			if (Key[KEY_INPUT_X] == 1 && window.getEquipmentWindowIsHide() && window.getStatusWindowIsHide() && !player[0]->getIsSpeak()) {
				window.changeIsHide();
			}
		}

		// �}�b�v�̐؂�ւ�
		nowMap->changeMap(player[0]);
		
		// �}�b�v�Ǝ�l���̕`��
		nowMap->drawMap(ScrollX, ScrollY, player[0]);
		player[0]->drawHero(&moveCounter);

		window.drawMenuWindow();

		if (window.getEquipmentWindowIsHide() && window.getStatusWindowIsHide() && window.getIsHide()) {
			nowMap->npcAction(player[0]);
		}

		if (moveEncountNum > BATTLEINTEBAL) {
			tmp->encount(player[0], nowMap);

			if (!tmp->getIsFinish()) {
				bg->drawGraph(0);
			}

			tmp->battle(player[0]);
			if (tmp->getIsFinish()) {
				moveEncountNum = 0;
			}
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "HP:%d", player[0]->getHp());
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}