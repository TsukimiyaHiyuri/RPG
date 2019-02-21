#include "DxLib.h"
#include "inputkey.h"

InputMouse Mouse;
int Key[256];

int updatekey() {

	int tmpMouse;
	char tmpKey[256];

	GetHitKeyStateAll(tmpKey);
	tmpMouse = GetMouseInput();

	//�@�L�[�{�[�h�̉�����Ă���L�[�̃t���[�������J�E���g����
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}

	//�@�}�E�X�̍��E�̃{�^����������Ă���t���[�������J�E���g����
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

	//�@���݂̃}�E�X�̍��W�𓾂�
	GetMousePoint(&Mouse.x, &Mouse.y);

	return 0;
}

void Mouse_n(int n)
{
	Mouse.left = n;
	Mouse.right = n;
}