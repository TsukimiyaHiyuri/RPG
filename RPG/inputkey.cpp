#include "DxLib.h"
#include "inputkey.h"

InputMouse Mouse;
int Key[256];

int updatekey() {

	int tmpMouse;
	char tmpKey[256];

	GetHitKeyStateAll(tmpKey);
	tmpMouse = GetMouseInput();

	//　キーボードの押されているキーのフレーム数をカウントする
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}

	//　マウスの左右のボタンが押されているフレーム数をカウントする
	if (tmpMouse & MOUSE_INPUT_LEFT) {
		Mouse.left++;
	}
	else {
		Mouse.left = 0;
	}

	if (tmpMouse & MOUSE_INPUT_RIGHT) {
		Mouse.right++;
	}
	else {
		Mouse.right = 0;
	}

	//　現在のマウスの座標を得る
	GetMousePoint(&Mouse.x, &Mouse.y);

	return 0;
}

void Mouse_n(int n)
{
	Mouse.left = n;
	Mouse.right = n;
}