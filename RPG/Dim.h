#pragma once
#ifndef Dim__
#define Dim__

enum direct {
	UPR = 9,
	UP = 10,
	UPL = 11,
	RIGHTR = 6,
	RIGHT = 7,
	RIGHTL = 8,
	DOWNR = 0,
	DOWN = 1,
	DOWNL = 2,
	LEFTR = 3,
	LEFT = 4,
	LEFTL = 5
};

struct Dim2 {
	int x;
	int y;
};

#endif