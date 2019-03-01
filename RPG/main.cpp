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
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

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

		// ゲームクリアのときの処理
		if (clearFlag) {
			DrawFormatString(200, 220, GetColor(255, 255, 255), "クリアおめでとう！");
		}
		else {
			// 非戦闘時の処理
			if (battle->getIsFinish()) {
				if (window.getIsHide() && !player[0]->getIsSpeak()) {
					player[0]->move();

					// 壁(障害物)とのあたり判定
					// 当たったら止まる
					if (nowMap->judgeWall(player[0]->gety() + moveY, player[0]->getx() + moveX)) {
						player[0]->stop();
					}

					// 移動時のスクロールの計算
					player[0]->scroll(&moveCounter, &ScrollX, &ScrollY, &moveEncountNum);
				}

				// Xキーが押されたらメニューウィンドウの表示を切り替える
				if (Key[KEY_INPUT_X] == 1 && window.getEquipmentWindowIsHide() && window.getStatusWindowIsHide() && !player[0]->getIsSpeak()) {
					sound->playSE(MenuSE, true);
					window.changeIsHide();
				}

				// BGMをならす
				if (!sound->checkBGM(FieldBGM)) {
					sound->playBGM(FieldBGM);
				}

				// マップの切り替え
				nowMap->changeMap(player[0]);

				// マップと主人公の描画
				nowMap->drawMap(ScrollX, ScrollY, player[0]);
				player[0]->drawHero(&moveCounter);

				// メニューウィンドウの描画
				window.drawMenuWindow();

				// マップにいるNPCの処理
				if (window.getEquipmentWindowIsHide() && window.getStatusWindowIsHide() && window.getIsHide()) {
					nowMap->npcAction(player[0]);
				}

				// 敵とのエンカウントの処理
				if (nowMap->bossIsEncount(player[0]->gety(), player[0]->getx()) && battle->getIsFinish()) {
					battle->bossEncount(player[0]);
				}
				if (moveEncountNum > BATTLEINTEBAL) {
					battle->encount(player[0], nowMap);
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
				battle->battle(player[0], &clearFlag, nowMap);
				if (battle->getIsFinish()) {
					sound->stopBGM(BattleBGM);
					sound->stopBGM(BossBattleBGM);
					moveEncountNum = 0;
				}
			}

			// プレイヤーの座標を表示
			DrawFormatString(0, 0, GetColor(255, 255, 255), "X: %d, Y: %d", player[0]->getx(), player[0]->gety());
		}
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}