#include "Map.h"
#include "DxLib.h"

Map *nowMap;

// �R���X�g���N�^
Map::Map(int hei, int wid) 
{
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
	for (int i = -1; i < DrawMapChipNumY; i++)
	{
		for (int j = -1; j < DrawMapChipNumX; j++)
		{
			// ��ʂ���͂ݏo���ʒu�Ȃ�`�悵�Ȃ�
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= this->width || i + MapDrawPointY >= this->height) continue;

			// �}�b�v�f�[�^��`�悷��
			DrawGraph(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY, this->mapTip[this->map[i + MapDrawPointY][j + MapDrawPointX]], TRUE);
		}
	}
}

bool Map::judgeWall(int x, int y) {
	return true;
}