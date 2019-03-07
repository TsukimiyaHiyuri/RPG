#include "Ending.h"
#include "DxLib.h"

Ending::Ending(Sound *sound, BackGround *backGround) {
	this->cnt = 0;
	this->setList();
	this->setFont();
	this->sound = sound;
	this->backGround = backGround;
}

void Ending::setList() {
	this->list = std::vector<std::string>(ENDINGLISTNUM);
	this->list[0] = "�E�v���O����\n�@�@���{�Ђ��";
	this->list[1] = "�E�T�E���h\n�@�@�������@�l";
}

void Ending::setFont() {
	this->endingFont = CreateFontToHandle("���C���I", 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Ending::drawEndind() {
	this->cnt++;
	float y = float(ENDINGSPEED) * cnt;

	for (int i = 0; i < ENDINGLISTNUM; i++) {
		// ��ʓ��Ȃ�`�悷��
		if (this->canDraw(i, y)) {
			DrawStringFToHandle(ENDINGDRAWX, float(ENDINGDRAWY + ENDINGINTERBAL * (i + 1) - y), this->list[i].c_str(), GetColor(255, 255, 255), this->endingFont);
		}
	}
}

bool Ending::canDraw(int i, float y) {
	return ENDINGDRAWY + ENDINGINTERBAL * (i + 1) - y >= -100 && ENDINGDRAWY + ENDINGINTERBAL * (i + 1) - y <= 480;
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