#include "Map.h"
#include "DxLib.h"

Map *nowMap;
extern Player *player[PLAYERNUM];

// コンストラクタ
Map::Map(int hei, int wid)  {
	this->width = wid;
	this->height = hei;
}

// マップの描画
void Map::drawMap(int ScrollX, int ScrollY, Player *player) {
	// 描画するマップチップの数をセット
	int DrawMapChipNumX = 640 / MAP_SIZE + 2;
	int DrawMapChipNumY = 480 / MAP_SIZE + 2;

	// 画面左上に描画するマップ座標をセット
	int MapDrawPointX = player->getx() - (DrawMapChipNumX / 2 - 1);
	int MapDrawPointY = player->gety() - (DrawMapChipNumY / 2 - 1);

	// マップを描く
	for (int i = -1; i < DrawMapChipNumY; i++) {
		for (int j = -1; j < DrawMapChipNumX; j++) {
			// 画面からはみ出た位置なら描画しない
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= this->width || i + MapDrawPointY >= this->height) continue;

			// マップデータを描画する
			this->drawMapTip(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY, i + MapDrawPointY, j + MapDrawPointX);
		}
	}

	for (int i = -1; i < DrawMapChipNumY; i++) {
		for (int j = -1; j < DrawMapChipNumX; j++) {
			// 画面からはみ出た位置なら描画しない
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= this->width || i + MapDrawPointY >= this->height) continue;

			// NPCの描画
			for (int k = 0; k < this->npcNum; k++) {
				if (j + MapDrawPointX == this->npc[k]->getx() && i + MapDrawPointY == this->npc[k]->gety()) {
					DrawGraph(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY - 5, this->npc[k]->getGraphic(), true);
				}
			}
		}
	}
}

void Map::npcAction(Player *player) {
	for (int i = 0; i < this->npcNum; i++) {
		NonPlayerCharacter *tmp;
		tmp = this->npc[i]->speakStart(player, this->nowNPC);
		if (tmp != NULL) {
			this->nowNPC = tmp;
		}
	}

	if (nowNPC != NULL) {
		this->nowNPC->speaking(player);
	}
}

bool Map::judgeWall(int x, int y) {
	return true;
}

bool Map::judgeWallNPC(int x, int y) {
	for (int i = 0; i < this->npcNum; i++) {
		if (this->npc[i]->getx() == y && this->npc[i]->gety() == x) {
			return true;
		}
	}
	return false;
}