#pragma once
#ifndef _BackGround_
#define _BackGround_

#include <vector>

class BackGround {
	std::vector<int> graphics;
	int titleGraphic;
public:
	BackGround();
	void drawGraph(int n);
	void setTitleGraphic();
	void drawTitleGraph();
};

#endif