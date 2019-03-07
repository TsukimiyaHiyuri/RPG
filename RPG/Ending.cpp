#include "Ending.h"
#include "DxLib.h"

Ending::Ending(Sound *sound, BackGround *backGround) {
	this->cnt = 0;
	this->setList();
	this->sound = sound;
	this->backGround = backGround;
}

void Ending::setList() {
	this->list = std::vector<std::string>(ENDINGLISTNUM);
	this->list[0] = "月宮ひゆり";
	this->list[1] = "サウンド\n魔王魂　様";
}

void Ending::drawEndind() {
	this->cnt++;
	float y = float(0.2) * cnt;

	for (int i = 0; i < ENDINGLISTNUM; i++) {
		// 画面内なら描画する
		if (this->canDraw(i, y)) {
			DrawFormatStringF(450.0, float(ENDINGDRAWY + ENDINGINTERBAL * (i + 1) - y), GetColor(255, 255, 255), "%s", this->list[i].c_str());
		}
	}
}

bool Ending::canDraw(int i, float y) {
	return ENDINGDRAWY + ENDINGINTERBAL * (i + 1) - y >= 0 && ENDINGDRAWY + ENDINGINTERBAL * (i + 1) - y <= 480;
}

void Ending::drawBackGround() {

}

void Ending::playEndingBGM() {
	if (!this->sound->checkBGM(EndingBGM)) {
		this->sound->playBGM(EndingBGM);
	}
}

void Ending::drawAll() {
	this->playEndingBGM();
	this->drawBackGround();
	this->drawEndind();
}