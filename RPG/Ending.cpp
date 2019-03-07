#include "Ending.h"
#include "Key.h"
#include "DxLib.h"

Ending::Ending(Sound *sound, BackGround *backGround) {
	this->cnt = 0;
	this->alpha = 0;
	this->soundFlag = false;
	this->setList();
	this->setFont();
	this->sound = sound;
	this->backGround = backGround;
}

void Ending::setList() {
	this->list = std::vector<std::string>(ENDINGLISTNUM);
	this->list[0] = "・プログラム\n　　月宮ひゆり";
	this->list[1] = "・サウンド\n　　魔王魂　様";
	this->list[2] = "・敵イラスト\n　　Material World　様";
	this->list[3] = "・マップチップ\n　　ぴぽや倉庫　様";
	this->list[4] = "・背景イラスト\n　　ぴぽや倉庫　様";
}

void Ending::setFont() {
	this->endingFont = CreateFontToHandle("メイリオ", 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Ending::drawEndind() {
	float y = float(ENDINGSPEED) * cnt;

	if (ENDINGDRAWY + ENDINGINTERBAL * (ENDINGLISTNUM - 1) - y > -80) {
		for (int i = 0; i < ENDINGLISTNUM; i++) {
			this->cnt++;
			// 画面内なら描画する
			if (this->canDraw(i, y)) {
				DrawStringFToHandle(ENDINGDRAWX, float(ENDINGDRAWY + ENDINGINTERBAL * i - y), this->list[i].c_str(), GetColor(255, 255, 255), this->endingFont);
			}
		}
	}
	else {
		if (this->alpha < 255) {
			this->alpha += 1;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->alpha);
			DrawStringFToHandle(230, 200, "Thank you for playing.", GetColor(255, 255, 255), this->endingFont);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, this->alpha);
		}
		else {
			DrawStringFToHandle(230, 200, "Thank you for playing.", GetColor(255, 255, 255), this->endingFont);
		}
	}
}

bool Ending::canDraw(int i, float y) {
	return ENDINGDRAWY + ENDINGINTERBAL * i - y >= -80 && ENDINGDRAWY + ENDINGINTERBAL * i - y <= 480;
}

void Ending::drawBackGround() {

}

void Ending::playEndingBGM() {
	if (!this->sound->checkBGM(EndingBGM) && !this->soundFlag) {
		this->sound->playBGMNotLoop(EndingBGM);
		this->soundFlag = true;
	}
}

bool Ending::select() {
	if (this->alpha >= 255) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			return true;
		}
	}
	return false;
}

bool Ending::drawAll() {
	this->playEndingBGM();
	this->drawBackGround();
	this->drawEndind();
	return this->select();
}