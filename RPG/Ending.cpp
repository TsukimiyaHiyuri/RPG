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
	this->list[0] = "�E�v���O����\n�@�@���{�Ђ��";
	this->list[1] = "�E�T�E���h\n�@�@�������@�l";
	this->list[2] = "�E�G�C���X�g\n�@�@Material World�@�l";
	this->list[3] = "�E�}�b�v�`�b�v\n�@�@�҂ۂ�q�Ɂ@�l";
	this->list[4] = "�E�w�i�C���X�g\n�@�@�҂ۂ�q�Ɂ@�l";
}

void Ending::setFont() {
	this->endingFont = CreateFontToHandle("���C���I", 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Ending::drawEndind() {
	float y = float(ENDINGSPEED) * cnt;

	if (ENDINGDRAWY + ENDINGINTERBAL * (ENDINGLISTNUM - 1) - y > -80) {
		for (int i = 0; i < ENDINGLISTNUM; i++) {
			this->cnt++;
			// ��ʓ��Ȃ�`�悷��
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