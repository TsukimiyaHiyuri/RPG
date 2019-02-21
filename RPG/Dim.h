#pragma once
#ifndef Dim__
#define Dim__

enum direct {
	UPR = 0,
	UP = 1,
	UPL = 2,
	RIGHTR = 3,
	RIGHT = 4,
	RIGHTL = 5,
	DOWNR = 6,
	DOWN = 7,
	DOWNL = 8,
	LEFTR = 9,
	LEFT = 10,
	LEFTL = 11
};

struct Dim2 {
	int x;
	int y;
};

#endif