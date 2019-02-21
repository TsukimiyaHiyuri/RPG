#pragma once
#ifndef _key_
#define _key_

struct InputMouse {
	int right;
	int left;
	int x;
	int y;
};

extern InputMouse Mouse;
extern int Key[256];

int updatekey();
void Mouse_n(int n);

#endif