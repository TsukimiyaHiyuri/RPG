#include "Title.h"
#include "Key.h"
#include "DxLib.h"

Title::Title(BackGround *bg, Sound *sound) {
	this->isHide = false;
	this->selectNum = 0;
	this->setList();
	this->setTitleName("勇者の冒険(仮)");
	this->setFont();
	this->backGround = bg;
	this->sound = sound;
}

// タイトルメニューの項目の設定
void Title::setList() {
	this->list = std::vector<std::string>(TITLEMENUNUM);
	this->list[Start] = "Start";
	this->list[Load] = "Load";
	this->list[Exit] = "Exit";
}

// タイトルの名前を設定
void Title::setTitleName(std:: string titleName) {
	this->titleName = titleName;
}

// フォントの設定
void Title::setFont() {
	this->titleFont = CreateFontToHandle("メイリオ", 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE);
	this->menuFont = CreateFontToHandle("メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

// 表示切り替え
void Title::changeIsHide() {
	this->isHide = !this->isHide;
}

// タイトル名を描画
void Title::drawTitleName() {
	DrawStringToHandle(TITLENAMEX, TITLENAMEY, this->titleName.c_str(), GetColor(255, 255, 255), this->titleFont);
}

// タイトルの背景を描画
void Title::drawTitleGraph() {
	this->backGround->drawTitleGraph();
}

// タイトルメニューの描画
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

// 決定キーが押されたときの処理
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

// カーソル移動の処理
void Title::moveSelector() {
	if (!this->isHide) {
		if (Key[KEY_INPUT_UP] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum--;
			if (this->selectNum < 0) {
				this->selectNum = TITLEMENUNUM - 1;
			}
		}
		else if (Key[KEY_INPUT_DOWN] == 1) {
			// SEをならす
			this->sound->playSE(CursorSE, true);

			this->selectNum++;
			if (this->selectNum >= TITLEMENUNUM) {
				this->selectNum = 0;
			}
		}
	}
}

// 描画、カーソル移動、決定の処理をまとめたもの
bool Title::drawAll(bool *isFinish) {
	this->drawTitleGraph();
	this->drawTitleName();
	this->drawTitleMenu();
	this->moveSelector();
	return this->select(isFinish);
}