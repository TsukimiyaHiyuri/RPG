#pragma once
#ifndef _BackGround_
#define _BackGround_

#include <vector>

class BackGround {
	std::vector<int> graphics;
public:
	BackGround();
	void drawGraph(int n);
};

#endif