#include "Title.h"
#include "DxLib.h"

Title::Title(BackGround *bg, Sound *sound) {
	this->isHide = false;
	this->setList();
	this->setTitleName("—EŽÒ‚Ì–`Œ¯(‰¼)");
	this->setFont();
	this->backGround = bg;
	this->sound = sound;
}

void Title::setList() {
	this->list = std::vector<std::string>(TITLEMENUNUM);
	this->list[Start] = "Start";
	this->list[Load] = "Load";
	this->list[Exit] = "Exit";
}

void Title::setTitleName(std:: string titleName) {
	this->titleName = titleName;
}

void Title::setFont() {
	this->titleFont = CreateFontToHandle("ƒƒCƒŠƒI", 50, 10, DX_FONTTYPE_ANTIALIASING_EDGE);
	this->menuFont = CreateFontToHandle("ƒƒCƒŠƒI", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Title::changeIsHide() {
	this->isHide = !this->isHide;
}

void Title::drawTitleName() {
	DrawStringToHandle(TITLENAMEX, TITLENAMEY, this->titleName.c_str(), GetColor(255, 255, 255), this->titleFont);
}

void Title::drawTitleMenu() {
	for (int i = 0; i < TITLEMENUNUM; i++) {
		DrawStringToHandle(TITLEMENUX, TITLEMENUY + (i * TITLEMENUINTERBAL), this->list[i].c_str(), GetColor(255, 255, 255), this->menuFont);
	}
}

bool Title::select() {
	return true;
}

void Title::moveSelector() {

}

bool Title::drawAll() {
	this->drawTitleName();
	this->drawTitleMenu();
	this->moveSelector();
	return this->select();
}