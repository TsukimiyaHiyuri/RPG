#pragma once
#ifndef _BattleWindow_
#define _BattleWindow_

#include <string>
#define BTTLEWINDOWINTERBAL 100
#define BATTLEWINDOWX1 200
#define BATTLEWINDOWY1 300
#define BATTLEWINDOWX2 550
#define BATTLEWINDOWY2 400

class BattleWindow {
	std::string str;	// ウィンドウの内容
	bool isHide;		// ウィンドウを隠すか？
	int interbalCount;			// インターバルのカウント用

public:
	BattleWindow();
	void setStr(std::string str);
	void drawBattleWindow();
	void drawAll();
	void changeIsHide();
	void incrementInterbalCount();
	bool strIsEmpty();
	bool getIsHide() { return this->isHide; }
};

#endif
