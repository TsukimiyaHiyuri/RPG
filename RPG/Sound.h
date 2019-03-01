#pragma once
#ifndef _Sound_
#define _Sound_

#define SENUM 6
#define BGMNUM 3

enum SEType {
	DecideSE = 0,
	CancelSE = 1,
	AttackSE = 2,
	DamageSE = 3,
	EscapedSE = 4,
	LevelUpSE = 5
};

enum BGMType {
	BattleBGM = 0,
	BossBattleBGM = 1,
	FieldBGM = 2
};

class Sound {
	int se[SENUM];
	int bgm[BGMNUM];
public:
	Sound();
	void loadSound();
	void playSE(SEType type);
	void playBGM(BGMType type);
	bool checkSE(SEType);
	bool checkBGM(BGMType);
};

#endif