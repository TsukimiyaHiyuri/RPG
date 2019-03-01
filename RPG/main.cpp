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
#include "Sound.h"
#include <vector>
#include <string>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	int mapNum = World;
	nowMap = new WorldMap();
	int ScrollX = 0, ScrollY = 0;
	int moveCounter = 0;
	bool clearFlag = false;

	Sound *sound = new Sound();

	int moveEncountNum = 0;
	player[0] = new Player(sound);
	player[1] = new Player(sound);
	player[2] = new Player(sound);

	MenuWindow window = MenuWindow(player[0]);
	Battle *battle = new Battle(sound);
	BackGround *bg = new BackGround();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && updatekey() == 0) {

		// �Q�[���N���A�̂Ƃ��̏���
		if (clearFlag) {
			DrawFormatString(200, 220, GetColor(255, 255, 255), "�N���A���߂łƂ��I");
		}
		else {
			// ��퓬���̏���
			if (battle->getIsFinish()) {
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

				// X�L�[�������ꂽ�烁�j���[�E�B���h�E�̕\����؂�ւ���
				if (Key[KEY_INPUT_X] == 1 && window.getEquipmentWindowIsHide() && window.getStatusWindowIsHide() && !player[0]->getIsSpeak()) {
					sound->playSE(MenuSE, true);
					window.changeIsHide();
				}

				// BGM���Ȃ炷
				if (!sound->checkBGM(FieldBGM)) {
					sound->playBGM(FieldBGM);
				}

				// �}�b�v�̐؂�ւ�
				nowMap->changeMap(player[0]);

				// �}�b�v�Ǝ�l���̕`��
				nowMap->drawMap(ScrollX, ScrollY, player[0]);
				player[0]->drawHero(&moveCounter);

				// ���j���[�E�B���h�E�̕`��
				window.drawMenuWindow();

				// �}�b�v�ɂ���NPC�̏���
				if (window.getEquipmentWindowIsHide() && window.getStatusWindowIsHide() && window.getIsHide()) {
					nowMap->npcAction(player[0]);
				}

				// �G�Ƃ̃G���J�E���g�̏���
				if (nowMap->bossIsEncount(player[0]->gety(), player[0]->getx()) && battle->getIsFinish()) {
					battle->bossEncount(player[0]);
				}
				if (moveEncountNum > BATTLEINTEBAL) {
					battle->encount(player[0], nowMap);
				}
			}

			// �퓬���̏���
			if (!battle->getIsFinish()) {
				// �w�i�̕`��
				bg->drawGraph(0);

				// �퓬�Ȃ̍Đ�
				if (sound->checkBGM(FieldBGM)) {
					sound->stopBGM(FieldBGM);
					if (battle->getIsBoss()) {
						sound->playBGM(BossBattleBGM);
					}
					else {
						sound->playBGM(BattleBGM);
					}
				}

				// �퓬�̏���
				battle->battle(player[0], &clearFlag, nowMap);
				if (battle->getIsFinish()) {
					sound->stopBGM(BattleBGM);
					sound->stopBGM(BossBattleBGM);
					moveEncountNum = 0;
				}
			}

			// �v���C���[�̍��W��\��
			DrawFormatString(0, 0, GetColor(255, 255, 255), "X: %d, Y: %d", player[0]->getx(), player[0]->gety());
		}
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}