#include "BackGround.h"
#include "DxLib.h"

BackGround::BackGround() {
	this->graphics.push_back(LoadGraph("‘Œ´.jpg"));
}

void BackGround::drawGraph(int n) {
	DrawGraph(0, 0, this->graphics[n], true);
}