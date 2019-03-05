#include "BackGround.h"
#include "DxLib.h"

BackGround::BackGround() {
	this->graphics.push_back(LoadGraph("background/pipo-battlebg001.jpg"));
	this->setTitleGraphic();
}

void BackGround::drawGraph(int n) {
	DrawGraph(0, 0, this->graphics[n], true);
}

void BackGround::setTitleGraphic() {
	this->titleGraphic = LoadGraph("background/pipo-battlebg002.jpg");
}

// ƒ^ƒCƒgƒ‹‚Ì”wŒi‚ð•`‰æ
void BackGround::drawTitleGraph() {
	DrawGraph(0, 0, this->titleGraphic, true);
}