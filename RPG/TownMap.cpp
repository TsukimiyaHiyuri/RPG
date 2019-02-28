#include "TownMap.h"
#include "Player.h"
#include "WorldMap.h"
#include "DxLib.h"
#include "ShopNPC.h"
#include "Item.h"
#include "Potion.h"
#include "Armors.h"
#include "Sord.h"
#include <iostream>

TownMap::TownMap() {
	this->loadMapTip();
	this->setMap();
	this->isEncount = false;
	this->setNPC();
}

void TownMap::setMap() {
	this->map = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 22, 23, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 38, 39, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 22, 23, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 38, 39, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 22, 23, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 38, 39, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	this->height = this->map.size();
	this->width = this->map[0].size();
}

void TownMap::loadMapTip() {
	LoadDivGraph("FieldMapTip.png", 16 * 12, 16, 12, 32, 32, this->mapTip);//画像を分割してimage配列に保存
}

// 壁の判定
bool TownMap::judgeWall(int x, int y) {

	if (x >= 0 && y >= 0 && x < this->map.size() && y < this->map[0].size()) {
		if (this->map[x][y] == 22 || this->map[x][y] == 23 || this->map[x][y] == 38 || this->map[x][y] == 39) {

			return true;
		}
	}

	return this->judgeWallNPC(x, y);
}

//	次のマップに移動するかを監視する
//	移動する前に次のマップのどの座標に主人公を描画するかを描いておく
void TownMap::changeMap(Player *player) {
	int x = player->getx();
	int y = player->gety();
	if (y < 0 && (x == 8 || x == 9)) {
		player->setPlayer(13, 16);
		delete nowMap;
		nowMap = new WorldMap();
	}
}

void TownMap::setNPC() {
	this->npcNum = 1;
	std::vector<std::string> tmp;
	tmp.push_back("ここは何でも屋です");
	tmp.push_back("何か買っていきませんか？");

	Item *item[3] = { new Potion(), new Armors(), new Sord()};

	this->npc[0] = new ShopNPC(5, 5, "歩行ドットキャラ.bmp", tmp, DOWN, item, 3);
}

void TownMap::drawMapTip(int drawx, int drawy, int pointx, int pointy) {
	DrawGraph(drawx, drawy, this->mapTip[this->map[pointx][pointy]], true);
}