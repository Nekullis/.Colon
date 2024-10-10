//----------------------------------------------------------------------
// @filename XInput.h
// @author: Saito Ko
// @explanation
// XInput��Ԃ̃R���g���[���[�̓��͂��Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "../Math/mymath.h"
#include <cmath>

//XInput�̃{�^���z�u

//#define XINPUT_BUTTON_DPAD_UP		               (0)	// �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_DOWN		       (1)	// �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_LEFT		           (2)	// �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_RIGHT	           (3)	// �f�W�^�������{�^���E
//#define XINPUT_BUTTON_START		                   (4)	// START�{�^��
//#define XINPUT_BUTTON_BACK		                   (5)	// BACK�{�^��
//#define XINPUT_BUTTON_LEFT_THUMB	           (6)	// ���X�e�B�b�N��������
//#define XINPUT_BUTTON_RIGHT_THUMB	       (7)	// �E�X�e�B�b�N��������
//#define XINPUT_BUTTON_LEFT_SHOULDER	   (8)	// LB�{�^��
//#define XINPUT_BUTTON_RIGHT_SHOULDER   (9)	// RB�{�^��
#define XINPUT_BUTTON_LT (10)                          // ���g���K
#define XINPUT_BUTTON_RT (11)                         // �E�g���K 
//#define XINPUT_BUTTON_A		                         (12)   // A�{�^��
//#define XINPUT_BUTTON_B		                         (13)   // B�{�^��
//#define XINPUT_BUTTON_X		                         (14)   // X�{�^��
//#define XINPUT_BUTTON_Y		                         (15)   // Y�{�^��
#define XINPUT_BUTTON_STICK_UP (16)             //��X�e�B�b�N
#define XINPUT_BUTTON_STICK_LEFT (17)         //���X�e�B�b�N
#define XINPUT_BUTTON_STICK_DOWN (18)      //���X�e�B�b�N
#define XINPUT_BUTTON_STICK_RIGHT (19)      //�E�X�e�B�b�N

#define DXINPUT_BUTTON_MAX		16
#define PAD_BUTTON_MAX		20
const int PLAYER_MAX = 4;
const int PLAYER_1 = 1;
const int PLAYER_2 = 2;
const int PLAYER_3 = 3;
const int PLAYER_4 = 4;

class XInput
{
public:
	// �X�e�B�b�N���͒l���u-1 ~ 1�v�ɕϊ����ĕێ�����
	struct STICK {
		float x, y;
	};

	XInput();
	XInput(int number);
	~XInput();
	virtual bool Input();
	static bool UpdateJoyPad();
	static void ReSet();

	//�Q�b�^�[
	//-------------------------------------------------

	virtual unsigned char GetKey(int index) const { return _input.Buttons[index]; }
	virtual unsigned char GetTrg(int index) const { return _trg[index]; }
	virtual unsigned char GetRel(int index) const { return _rel[index]; }

	short GetRx()const  { return _input.ThumbRX; }
	short GetRy()const  { return _input.ThumbRY; }
	short GetLx() const { return _input.ThumbLX; }
	short GetLy() const { return _input.ThumbLY; }
	unsigned char GetLTrg() const { return _input.LeftTrigger; }
	unsigned char GetRTrg() const { return _input.RightTrigger; }

	STICK GetAdjustedStick_L() const { return _adjustedLStick; }
	STICK GetAdjustedStick_R() const { return _adjustedRStick; }

	bool IsInputStickLeft() const;
	bool IsInputStickRight() const;

	static int GetConnectNum() { return _connectNum; }
	static int SetConnectNum(int num) { return _connectNum = num; }

	static XInput* GetInstance() { return _instatnce; }

	//-----------------------------------------------------

private:
	XINPUT_STATE _input;

	static XInput* _instatnce;

	unsigned char Buttons[PAD_BUTTON_MAX];


	STICK _adjustedLStick;
	STICK _adjustedRStick;

// xbox�R���g���[���[�̃{�^���z�u
// �ő吔

	unsigned char	 _trg[PAD_BUTTON_MAX], _rel[PAD_BUTTON_MAX];

	int _padNum;

	unsigned char _stickInput[4];
	static  int _connectNum;
	bool _isConnect;
};