#include "Sound.h"
#include "DxLib.h"

Sound::Sound() {
	this->loadSound();
}

void Sound::loadSound() {
	// SEÇÃì«Ç›çûÇ›
	se[DecideSE] = LoadSoundMem("Sound/se_decide.mp3");
	se[CancelSE] = LoadSoundMem("Sound/se_cancel.mp3");
	se[AttackSE] = LoadSoundMem("Sound/se_attack.mp3");
	se[DamageSE] = LoadSoundMem("Sound/se_damage.mp3");
	se[EscapedSE] = LoadSoundMem("Sound/se_escape.mp3");
	se[LevelUpSE] = LoadSoundMem("Sound/se_levelup.mp3");

	// BGMÇÃì«Ç›çûÇ›
	bgm[BattleBGM] = LoadSoundMem("Sound/bgm_battle.mp3");
	bgm[BossBattleBGM] = LoadSoundMem("Sound/bgm_bossbattle.mp3");
	bgm[FieldBGM] = LoadSoundMem("Sound/bgm_field.mp3");
}

void Sound::playSE(SEType type) {
	PlaySoundMem(se[type], DX_PLAYTYPE_NORMAL);
}

void Sound::playBGM(BGMType type) {
	PlaySoundMem(bgm[type], DX_PLAYTYPE_LOOP);
}

bool Sound::checkSE(SEType type) {
	if (CheckSoundMem(se[type]) == 1) {
		return true;
	}
	return false;
}

bool Sound::checkBGM(BGMType type) {
	if (CheckSoundMem(bgm[type]) == 1) {
		return true;
	}
	return false;
}