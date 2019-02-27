#include "WorldMap.h"
#include "Player.h"
#include "TownMap.h"
#include "Slime.h"
#include "DxLib.h"
#include <iostream>

WorldMap::WorldMap() {
	this->loadMapTip();
	this->setMap();
	this->isEncount = true;
	this->setNPC();
	this->setEnemy();
}

void WorldMap::setMap() {
	this->map = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 23, 0, 51, 51, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 38, 39, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 51, 51, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 } ,
	};
	this->height = this->map.size();
	this->width = this->map[0].size();
}

void WorldMap::loadMapTip() {
	LoadDivGraph("FieldMapTip.png", 16 * 12, 16, 12, 32, 32, this->mapTip);//画像を分割してimage配列に保存
}

// 壁の判定
bool WorldMap::judgeWall(int x, int y) {
	if (x >= 0 && y >= 0 && x < this->map.size() && y < this->map[0].size()) {
		if (this->map[x][y] == 22 || this->map[x][y] == 23 || this->map[x][y] == 38 || this->map[x][y] == 39) {

			return true;
		}
	}

	return this->judgeWallNPC(x, y);
}

//	次のマップに移動するかを監視する
//	移動する前に次のマップのどの座標に主人公を描画するかを描いておく
void WorldMap::changeMap(Player *player) {
	int x = player->getx();
	int y = player->gety();
	if (y > 16 && (x == 12 || x == 13)) {
		player->setPlayer(9, 0);
		delete nowMap;
		nowMap = new TownMap();
	}
}

void WorldMap::setNPC() {
	this->npcNum = 2;
	std::vector<std::string> tmp;
	tmp.push_back("これはテストです。");
	tmp.push_back("上手くいきましたか？");

	this->npc[0] = new NonPlayerCharacter(5, 5, "歩行ドットキャラ.bmp", tmp, DOWN);

	tmp.push_back("おまけにもう一つ！");

	this->npc[1] = new NonPlayerCharacter(7, 7, "歩行ドットキャラ.bmp", tmp, DOWN);
}

void WorldMap::setEnemy() {
	this->enemy[0] = new Slime(0);
	this->enemyNum = 1;
}