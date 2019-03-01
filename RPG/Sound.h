#pragma once
#ifndef _Sound_
#define _Sound_

#define SENUM 7
#define BGMNUM 3

enum SEType {
	DecideSE = 0,
	CancelSE = 1,
	AttackSE = 2,
	DamageSE = 3,
	EscapedSE = 4,
	LevelUpSE = 5,
	MenuSE = 6
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
	void playSE(SEType type, bool isBack);
	void playBGM(BGMType type);
	bool checkSE(SEType);
	bool checkBGM(BGMType);
	void stopBGM(BGMType type);
};

#endif