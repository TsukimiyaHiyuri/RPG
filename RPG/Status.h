#pragma once
#ifndef _STATUS_
#define _STATUS_

#include <string>

struct Status {
	std::string name;
	int lv;
	int maxHp;
	int hp;
	int maxMp;
	int mp;
	int str;
	int def;
	long exp;
	long gold;
};

#endif