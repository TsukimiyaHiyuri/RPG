#pragma once
#ifndef _Magic_
#define _magic_

#include "Player.h"
#include "Enemy.h"
#include <string>
#define MAXMAGICNUM 8
#define CURE 30

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
	std::string name;	// ���@�̖��O
	std::string discription;	// ���@�̐���
	int learnLv;	// �K�����x��
	MagicType type;	// ���@�̎��
	int useMp;		// ����MP

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
#endif
