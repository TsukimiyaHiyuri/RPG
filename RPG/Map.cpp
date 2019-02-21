#include "Map.h"
#include "DxLib.h"

Map *nowMap;

// コンストラクタ
Map::Map(int hei, int wid) 
{
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
	for (int i = -1; i < DrawMapChipNumY; i++)
	{
		for (int j = -1; j < DrawMapChipNumX; j++)
		{
			// 画面からはみ出た位置なら描画しない
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= this->width || i + MapDrawPointY >= this->height) continue;

			// マップデータを描画する
			DrawGraph(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY, this->mapTip[this->map[i + MapDrawPointY][j + MapDrawPointX]], TRUE);
		}
	}
}

bool Map::judgeWall(int x, int y) {
	return true;
}