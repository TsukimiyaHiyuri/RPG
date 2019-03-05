#include "Title.h"
#include "Key.h"
#include "DxLib.h"

Title::Title(BackGround *bg, Sound *sound) {
	this->isHide = false;
	this->selectNum = 0;
	this->setList();
	this->setTitleName("�E�҂̖`��(��)");
	this->setFont();
	this->backGround = bg;
	this->sound = sound;
}

// �^�C�g�����j���[�̍��ڂ̐ݒ�
void Title::setList() {
	this->list = std::vector<std::string>(TITLEMENUNUM);
	this->list[Start] = "Start";
	this->list[Load] = "Load";
	this->list[Exit] = "Exit";
}

// �^�C�g���̖��O��ݒ�
void Title::setTitleName(std:: string titleName) {
	this->titleName = titleName;
}

// �t�H���g�̐ݒ�
void Title::setFont() {
	this->titleFont = CreateFontToHandle("���C���I", 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE);
	this->menuFont = CreateFontToHandle("���C���I", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

// �\���؂�ւ�
void Title::changeIsHide() {
	this->isHide = !this->isHide;
}

// �^�C�g������`��
void Title::drawTitleName() {
	DrawStringToHandle(TITLENAMEX, TITLENAMEY, this->titleName.c_str(), GetColor(255, 255, 255), this->titleFont);
}

// �^�C�g���̔w�i��`��
void Title::drawTitleGraph() {
	this->backGround->drawTitleGraph();
}

// �^�C�g�����j���[�̕`��
void Title::drawTitleMenu() {
	for (int i = 0; i < TITLEMENUNUM; i++) {
		if (i == this->selectNum) {
			DrawStringToHandle(TITLEMENUX, TITLEMENUY + (i * TITLEMENUINTERBAL), this->list[i].c_str(), GetColor(0, 255, 255), this->menuFont);
		}
		else {
			DrawStringToHandle(TITLEMENUX, TITLEMENUY + (i * TITLEMENUINTERBAL), this->list[i].c_str(), GetColor(255, 255, 255), this->menuFont);
		}
	}
}

// ����L�[�������ꂽ�Ƃ��̏���
bool Title::select(bool *isFinish) {
	if (!this->isHide) {
		if (Key[KEY_INPUT_Z] == 1) {
			Key[KEY_INPUT_Z]++;

			switch (this->selectNum) {
			case Start:
				return false;

			case Load:
				return true;

			case Exit:
				*isFinish = true;
			}
		}
	}
	return true;
}

// �J�[�\���ړ��̏���
void Title::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = TITLEMENUNUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SE���Ȃ炷
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= TITLEMENUNUM) {
				this->selectNum = 0;
			}
		}
	}
}

// �`��A�J�[�\���ړ��A����̏������܂Ƃ߂�����
bool Title::drawAll(bool *isFinish) {
	this->drawTitleGraph();
	this->drawTitleName();
	this->drawTitleMenu();
	this->moveSelector();
	return this->select(isFinish);
}