#pragma once
#ifndef _NonPlayerCharacter_
#define _NonPlayerCharacter_

#include "Dim.h"
#include "Player.h"
#include <vector>
#include <string>
#define SPEAKWINDOWX1 50
#define SPEAKWINDOWY1 300
#define SPEAKWINDOWX2 500
#define SPEAKWINDOWY2 400

class Player;

class NonPlayerCharacter {
	int x, y;
	int graphic[TIPSIZEP];
	direct direction;
	std::vector<std::string> speak;		// 会話の配列
	bool isSpeak;	//会話しているか
	int index;	// 会話の配列の番号

public:
	NonPlayerCharacter() {}
	NonPlayerCharacter(int x, int y, std::string fileName, std::vector<std::string> speak, direct direction);
	void set(int x, int y);
	void loadGraphic(std::string fileName);
	void setSpeak(std::vector<std::string> s);
	void select(Player *p);
	void speaking(Player *p);
	NonPlayerCharacter *speakStart(Player *p, NonPlayerCharacter * npc);
	void init();

	int getGraphic() { return this->graphic[this->direction]; }
	int getx() { return this->x; }
	int gety() { return this->y; }
};

#endif