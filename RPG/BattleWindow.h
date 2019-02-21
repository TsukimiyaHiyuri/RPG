#pragma once
#ifndef _BattleWindow_
#define _BattleWindow_

#include <string>
#define INTERBAL 100
#define BATTLEWINDOWX1 200
#define BATTLEWINDOWY1 300
#define BATTLEWINDOWX2 550
#define BATTLEWINDOWY2 400

class BattleWindow {
	std::string str;	// �E�B���h�E�̓��e
	bool isHide;		// �E�B���h�E���B�����H
	int cnt;			// �C���^�[�o���̃J�E���g�p

public:
	BattleWindow();
	void setStr(std::string str);
	void drawBattleWindow();
	void drawAll();
	void changeIsHide();
	bool strIsEmpty();
};

#endif
