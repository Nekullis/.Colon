//----------------------------------------------------------------------
// @filename Mouse.cpp
// @author: Saito Ko
// @explanation
// �}�E�X�̍��W��N���b�N�����Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Input/Mouse.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
Mouse::Mouse(){
	x = 0;
	y = 0;
	oldX = 0;
	oldY = 0;
	for (int i = 0; i < MOUTH_MAX; i++) {
		_key[i] = 0;
		_trg[i] = 0;
		_rel[i] = 0;
	}
};

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Mouse::~Mouse(){

};

//----------------------------------------------------------------------
// @brief �}�E�X�̍��W��N���b�N�����X�V
// @return ����
//----------------------------------------------------------------------
void Mouse::Update(){
	oldX = x; oldY = y;
	GetMousePoint(&x,&y);

	int input[MOUTH_MAX] = { MOUSE_INPUT_LEFT,MOUSE_INPUT_RIGHT,MOUSE_INPUT_MIDDLE };
	int now = GetMouseInput();

	bool oldkey[MOUTH_MAX] = { _key[0],_key[1],_key[2] };

	for (int i = 0; i < MOUTH_MAX; i++) {
		_key[i] = now & input[i];
		_trg[i] = (_key[i] && !oldkey[i]);
		_rel[i] = (!_key[i] && oldkey[i]);
	}
};
