#pragma once
#ifndef _Player_
#define _Player_

#include "Dim.h"
#include "Item.h"
#include "Magic.h"
#include "Enemy.h"
#include "Status.h"
#include <vector>
#include <string>
#define MAXBELONGINGS 8
#define MOVE_FRAME 15
#define PLAYERNUM 3
#define TIPSIZEP 128
#define MAXMAGICNUM 8

extern int moveX, moveY;
class Item;
class Magic;
class Enemy;

enum Character {
	Main = 0,
	Friend = 1,
	Bag = 2,
};

class Player {
	int graphic[TIPSIZEP];
	Status status;
	direct direction;
	Dim2 position;
	bool isMove;
	Item * belongings[MAXBELONGINGS];
	int belongingsNum;
	bool weapon;
	bool armor;
	int weaponStr, weaponDef;	// 装備武器のステータス
	int armorStr, armorDef;		// 装備防具のステータス

	Magic *magic[MAXMAGICNUM];
	int learnMagicNum;

public:
	Player();
	void move();
	void loadGraphic();
	void stop();
	void drawHero(int *moveCounter);
	void scroll(int *MoveCounter, int *ScrollX, int *ScrollY, int *EncountNum);
	void useItem(int n, Player *p);

	void setPlayer(int, int);
	int getx() { return position.x; }
	int gety() { return position.y; }
	int getLv() { return status.lv; }
	int getHp() { return status.hp; }
	int getMp() { return status.mp; }
	int getMaxHp() { return status.maxHp; }
	int getMaxMp() { return status.maxMp; }
	int getStr() { return status.str; }
	int getDef() { return status.def; }
	long getExp() { return status.exp; }
	long getGold() { return status.gold; }
	int getBelongingsNum() { return belongingsNum; }
	Item* getBelonging(int i) { return belongings[i]; }
	int getAllStr();
	direct getDirect() { return this->direction; }

	void setHp(int h) { status.hp = h; }
	void setMp(int m) { status.mp = m; }
	void setStr(int n) { status.str = n; }
	void setDef(int n) { status.def = n; }
	void addExp(long n) { status.exp += n; }
	void addGold(long n) { status.gold += n; }
	void setWeaponStr(int n) { weaponStr = n; }
	void setWeaponDef(int n) { weaponDef = n; }
	std::string getName() { return this->status.name; }
	int getWeaponStr() { return weaponStr; }
	int getWeaponDef() { return weaponDef; }
	void setArmorStr(int n) { armorStr = n; }
	void setArmorDef(int n) { armorDef = n; }
	int getArmorStr() { return armorStr; }
	int getArmorDef() { return armorDef; }
	void equipItem(int n, Player *p);
	void setBelongingsNum(int n) { belongingsNum = n; }
	void addBelongings(Item *item);
	void throwItem(int n);
	void passItem(int n,Player *p);

	Magic *getMagic(int i) { return this->magic[i]; }
	void attack(Enemy *e, std::string *n = 0);
	int getLearnMagicNum() { return this->learnMagicNum; }
	void damege(int n) { this->status.hp -= n; }
	void addMp(int n) { this->status.mp += n; }

	void learnMagic();
};

extern Player *player[PLAYERNUM];

#endif
