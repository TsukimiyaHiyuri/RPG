#pragma once
#include "Player.h"
#include <string>
#include <vector>
#define SELECTNUM 3
#define DRAWSELECTX1 30
#define DRAWSELECTY1 80
#define DRAWSELECTX2 100
#define DRAWSELECTY2 200
#define INTERBALSELECT 30

class Player;
class SelectWhoWindow;

enum Select {
	Use = 0,
	Equip = 1,
	Throw = 2,
	Defalt = 3,
};

class SelectWindow {
	int selectNum;
	int itemNum;
	bool isHide;
	Select selection;
	Player *who;
	Player *to;
	std::vector<std::string> list;	// ���j���[�E�B���h�E�̍��ڂ̕�����

public:
	SelectWindow() {}
	SelectWindow(Player *p);
	void setList();
	void drawSelectWindow();
	void changeIsHide();
	void moveSelector();
	Select select();
	void setItemNum(int n) { itemNum = n; }
	bool getIsHide() { return isHide; }
	int getselectNum() { return selectNum; }
};

