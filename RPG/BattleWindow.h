#pragma once
#ifndef _BattleWindow_
#define _BattleWindow_

#include <string>
#define INTERBAL 30
#define BATTLEWINDOWX1 200
#define BATTLEWINDOWY1 300
#define BATTLEWINDOWX2 550
#define BATTLEWINDOWY2 400

class BattleWindow {
	std::string str;	// ウィンドウの内容
	bool isHide;		// ウィンドウを隠すか？
	bool isFinish;		// 表示が終わったか？
	int cnt;			// インターバルのカウント用

public:
	BattleWindow();
	void setStr(std::string str);
	void drawBattleWindow();
	void drawAll();
};

#endif
