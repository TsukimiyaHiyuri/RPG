#pragma once
#ifndef _Magic_
#define _magic_

#include "Player.h"
#include "Enemy.h"
#include <string>
#define MAXMAGICNUM 8
#define CURE 30
#define MEGCURE 120
#define FIRE 20
#define MEGFIRE 70
#define THUNDER 15
#define MEGTHUNDER 50

class Player;
class Enemy;

enum MagicType {
	AttackAll = 0,
	AttackSolo = 1,
	CureAll = 2,
	CureSolo = 3
};

class Magic {
protected:
	std::string name;	// 魔法の名前
	std::string discription;	// 魔法の説明
	int learnLv;	// 習得レベル
	MagicType type;	// 魔法の種類
	int useMp;		// 消費MP

public:
	Magic();
	virtual bool use(Player *p, std::string *n = 0) { return true; }
	virtual bool use(Player *p, Enemy *e, std::string *n = 0) { return true; }
	virtual bool use(Player *p, Enemy *e[], std::string *n = 0) { return true; }
	MagicType getType() { return this->type; }
	std::string getName() { return this->name; }
	void setDiscription();
	void setStr(std::string *n, int damage, Enemy *e, Player *p);
};

class Fire : public Magic {
public:
	Fire();
	virtual bool use(Player *p, Enemy *e, std::string *n = 0);
};

class Thunder : public Magic {
public:
	Thunder();
	virtual bool use(Player *p, Enemy *e[], std::string *n = 0);
};

class Cure : public Magic {
public:
	Cure();
	virtual bool use(Player *p, std::string *n = 0);
};

class MegFire : public Magic {
public:
	MegFire();
	virtual bool use(Player *p, Enemy *e, std::string *n = 0);
};

class MegThunder : public Magic {
public:
	MegThunder();
	virtual bool use(Player *p, Enemy *e[], std::string *n = 0);
};

class MegCure : public Magic {
public:
	MegCure();
	virtual bool use(Player *p, std::string *n = 0);
};
#endif
