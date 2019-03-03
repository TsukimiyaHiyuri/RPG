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
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

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

		// ゲームクリアのときの処理
		if (clearFlag) {
			DrawFormatString(200, 220, GetColor(255, 255, 255), "クリアおめでとう！");
		}
		else {
			// 非戦闘時の処理
			if (battle->getIsFinish()) {
				if (window->getIsHide() && !hero->getIsSpeak()) {
					hero->move();

					// 壁(障害物)とのあたり判定
					// 当たったら止まる
					if (nowMap->judgeWall(hero->gety() + hero->getMoveY(), hero->getx() + hero->getMoveX())) {
						hero->stop();
					}

					// 移動時のスクロールの計算
					hero->scroll(&moveCounter, &ScrollX, &ScrollY, &moveEncountNum);
				}

				// Xキーが押されたらメニューウィンドウの表示を切り替える
				if (Key[KEY_INPUT_X] == 1 && window->getIsHide() && !hero->getIsSpeak()) {
					Key[KEY_INPUT_X]++;

					sound->playSE(MenuSE, true);
					window->changeIsHide();
				}

				// BGMをならす
				if (!sound->checkBGM(FieldBGM)) {
					sound->playBGM(FieldBGM);
				}

				// マップの切り替え
				nowMap->changeMap(hero);

				// マップと主人公の描画
				nowMap->drawMap(ScrollX, ScrollY, hero);
				hero->drawHero(&moveCounter);

				// メニューウィンドウの描画
				window->drawAll();

				// マップにいるNPCの処理
				if (window->getIsHide()) {
					nowMap->npcAction(hero);
				}

				// 敵とのエンカウントの処理
				if (nowMap->bossIsEncount(hero->gety(), hero->getx()) && battle->getIsFinish()) {
					battle->bossEncount(hero);
				}
				if (moveEncountNum > BATTLEINTEBAL) {
					battle->encount(hero, nowMap);
				}
			}

			// 戦闘時の処理
			if (!battle->getIsFinish()) {
				// 背景の描画
				bg->drawGraph(0);

				// 戦闘曲の再生
				if (sound->checkBGM(FieldBGM)) {
					sound->stopBGM(FieldBGM);
					if (battle->getIsBoss()) {
						sound->playBGM(BossBattleBGM);
					}
					else {
						sound->playBGM(BattleBGM);
					}
				}

				// 戦闘の処理
				battle->battle(hero, &clearFlag, nowMap);
				if (battle->getIsFinish()) {
					sound->stopBGM(BattleBGM);
					sound->stopBGM(BossBattleBGM);
					moveEncountNum = 0;
				}
			}

			// プレイヤーの座標を表示
			DrawFormatString(0, 0, GetColor(255, 255, 255), "X: %d, Y: %d", hero->getx(), hero->gety());
		}
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}