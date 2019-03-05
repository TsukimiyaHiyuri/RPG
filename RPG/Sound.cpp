#include "Sound.h"
#include "DxLib.h"

Sound::Sound() {
	this->loadSound();
}

void Sound::loadSound() {
	// SE�̓ǂݍ���
	se[DecideSE] = LoadSoundMem("Sound/se_decide.mp3");
	se[CancelSE] = LoadSoundMem("Sound/se_cancel.mp3");
	se[AttackSE] = LoadSoundMem("Sound/se_attack.mp3");
	se[DamageSE] = LoadSoundMem("Sound/se_damage.mp3");
	se[EscapedSE] = LoadSoundMem("Sound/se_escape.mp3");
	se[LevelUpSE] = LoadSoundMem("Sound/se_levelup.mp3");
	se[MenuSE] = LoadSoundMem("Sound/se_menu.mp3");
	se[CursorSE] = LoadSoundMem("Sound/se_cursor.mp3");
	se[EquipSE] = LoadSoundMem("Sound/se_equip.mp3");

	// BGM�̓ǂݍ���
	bgm[BattleBGM] = LoadSoundMem("Sound/bgm_battle.mp3");
	bgm[BossBattleBGM] = LoadSoundMem("Sound/bgm_bossbattle.mp3");
	bgm[FieldBGM] = LoadSoundMem("Sound/bgm_field.mp3");
	bgm[TitleBGM] = LoadSoundMem("Sound/bgm_title.mp3");
}

void Sound::playSE(SEType type, bool isBack) {
	if (isBack) {
		PlaySoundMem(se[type], DX_PLAYTYPE_BACK);
	}
	else {
		PlaySoundMem(se[type], DX_PLAYTYPE_NORMAL);
	}
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

void Sound::stopBGM(BGMType type) {
	StopSoundMem(bgm[type]);
}