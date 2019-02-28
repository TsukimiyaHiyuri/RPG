#include "Map.h"
#include "DxLib.h"

Map *nowMap;
extern Player *player[PLAYERNUM];

// �R���X�g���N�^
Map::Map(int hei, int wid)  {
	this->width = wid;
	this->height = hei;
}

// �}�b�v�̕`��
void Map::drawMap(int ScrollX, int ScrollY, Player *player) {
	// �`�悷��}�b�v�`�b�v�̐����Z�b�g
	int DrawMapChipNumX = 640 / MAP_SIZE + 2;
	int DrawMapChipNumY = 480 / MAP_SIZE + 2;

	// ��ʍ���ɕ`�悷��}�b�v���W���Z�b�g
	int MapDrawPointX = player->getx() - (DrawMapChipNumX / 2 - 1);
	int MapDrawPointY = player->gety() - (DrawMapChipNumY / 2 - 1);

	// �}�b�v��`��
	for (int i = -1; i < DrawMapChipNumY; i++) {
		for (int j = -1; j < DrawMapChipNumX; j++) {
			// ��ʂ���͂ݏo���ʒu�Ȃ�`�悵�Ȃ�
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= this->width || i + MapDrawPointY >= this->height) continue;

			// �}�b�v�f�[�^��`�悷��
			this->drawMapTip(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY, i + MapDrawPointY, j + MapDrawPointX);
		}
	}

	for (int i = -1; i < DrawMapChipNumY; i++) {
		for (int j = -1; j < DrawMapChipNumX; j++) {
			// ��ʂ���͂ݏo���ʒu�Ȃ�`�悵�Ȃ�
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= this->width || i + MapDrawPointY >= this->height) continue;

			// NPC�̕`��
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