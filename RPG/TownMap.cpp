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
	LoadDivGraph("FieldMapTip.png", 16 * 12, 16, 12, 32, 32, this->mapTip);//�摜�𕪊�����image�z��ɕۑ�
}

// �ǂ̔���
bool TownMap::judgeWall(int x, int y) {

	if (x >= 0 && y >= 0 && x < this->map.size() && y < this->map[0].size()) {
		if (this->map[x][y] == 22 || this->map[x][y] == 23 || this->map[x][y] == 38 || this->map[x][y] == 39) {

			return true;
		}
	}

	return this->judgeWallNPC(x, y);
}

//	���̃}�b�v�Ɉړ����邩���Ď�����
//	�ړ�����O�Ɏ��̃}�b�v�̂ǂ̍��W�Ɏ�l����`�悷�邩��`���Ă���
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
	tmp.push_back("�����͉��ł����ł�");
	tmp.push_back("���������Ă����܂��񂩁H");

	Item *item[3] = { new Potion(), new Armors(), new Sord()};

	this->npc[0] = new ShopNPC(5, 5, "���s�h�b�g�L����.bmp", tmp, DOWN, item, 3);
}

void TownMap::drawMapTip(int drawx, int drawy, int pointx, int pointy) {
	DrawGraph(drawx, drawy, this->mapTip[this->map[pointx][pointy]], true);
}