#include "DxLib.h"
#include "Map.h"
#include "WorldMap.h"
#include "TownMap.h"
#include "Hero.h"
#include "Key.h"
#include "MenuWindow.h"
#include "EquipmentWindow.h"
#include "Battle.h"
#include "BackGround.h"
#include "Sound.h"
#include "Title.h"
#include <vector>
#include <string>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	// ���y�֌W
	Sound *sound = new Sound();
	BackGround *bg = new BackGround();

	// �}�b�v�֌W
	Map *mapList[MAPNUM];
	createMap(mapList, sound);
	Map *nowMap = mapList[World];

	Title * title = new Title(bg, sound);

	int ScrollX = 0, ScrollY = 0;
	int moveCounter = 0;
	bool clearFlag = false;
	bool isTitle = true;	// ���̓^�C�g����ʂ��H
	bool isFinish = false;	// �Q�[���I�����H

	int moveEncountNum = 0;
	Player *hero = new Hero(sound);

	MenuWindow *window = new MenuWindow(hero, sound);
	Battle *battle = new Battle(sound);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && updatekey() == 0 && !isFinish) {

		// �Q�[���N���A�̂Ƃ��̏���
		if (clearFlag) {
			DrawFormatString(200, 220, GetColor(255, 255, 255), "�N���A���߂łƂ��I");
		}
		else if (isTitle) {
			isTitle = title->drawAll(&isFinish);
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
				nowMap = nowMap->changeMap(hero, nowMap, mapList);

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