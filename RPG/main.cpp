#include "DxLib.h"
#include "Map.h"
#include "WorldMap.h"
#include "TownMap.h"
#include "Hero.h"
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

	Sound *sound = new Sound();
	nowMap = new WorldMap(sound);
	int ScrollX = 0, ScrollY = 0;
	int moveCounter = 0;
	bool clearFlag = false;

	int moveEncountNum = 0;
	Player *hero = new Hero(sound);

	MenuWindow *window = new MenuWindow(hero, sound);
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
				if (window->getIsHide() && !hero->getIsSpeak()) {
					hero->move();

					// ��(��Q��)�Ƃ̂����蔻��
					// ����������~�܂�
					if (nowMap->judgeWall(hero->gety() + hero->getMoveY(), hero->getx() + hero->getMoveX())) {
						hero->stop();
					}

					// �ړ����̃X�N���[���̌v�Z
					hero->scroll(&moveCounter, &ScrollX, &ScrollY, &moveEncountNum);
				}

				// X�L�[�������ꂽ�烁�j���[�E�B���h�E�̕\����؂�ւ���
				if (Key[KEY_INPUT_X] == 1 && window->getIsHide() && !hero->getIsSpeak()) {
					Key[KEY_INPUT_X]++;

					sound->playSE(MenuSE, true);
					window->changeIsHide();
				}

				// BGM���Ȃ炷
				if (!sound->checkBGM(FieldBGM)) {
					sound->playBGM(FieldBGM);
				}

				// �}�b�v�̐؂�ւ�
				nowMap->changeMap(hero);

				// �}�b�v�Ǝ�l���̕`��
				nowMap->drawMap(ScrollX, ScrollY, hero);
				hero->drawHero(&moveCounter);

				// ���j���[�E�B���h�E�̕`��
				window->drawAll();

				// �}�b�v�ɂ���NPC�̏���
				if (window->getIsHide()) {
					nowMap->npcAction(hero);
				}

				// �G�Ƃ̃G���J�E���g�̏���
				if (nowMap->bossIsEncount(hero->gety(), hero->getx()) && battle->getIsFinish()) {
					battle->bossEncount(hero);
				}
				if (moveEncountNum > BATTLEINTEBAL) {
					battle->encount(hero, nowMap);
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
				battle->battle(hero, &clearFlag, nowMap);
				if (battle->getIsFinish()) {
					sound->stopBGM(BattleBGM);
					sound->stopBGM(BossBattleBGM);
					moveEncountNum = 0;
				}
			}

			// �v���C���[�̍��W��\��
			DrawFormatString(0, 0, GetColor(255, 255, 255), "X: %d, Y: %d", hero->getx(), hero->gety());
		}
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}