//----------------------------------------------------------------------
// @filename XInput.cpp
// @author: Saito Ko
// @explanation
// XInput��Ԃ̃R���g���[���[�̓��͂��Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Input/XInput.h"
#include "../../Header/Math/mymath.h"

int XInput::_connectNum = 0;
XInput* XInput::_instatnce = nullptr;

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
XInput::XInput() :
	_isConnect(true) 
{
	if(_instatnce == nullptr){
		_instatnce = this;
	}
	_connectNum++;
	_padNum = _connectNum;
	for (int i = 0; i < DXINPUT_BUTTON_MAX; i++) {
		_trg[i] = 0;
		_rel[i] = 0;
		_input.Buttons[i] = 0;
	}
};

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param number �p�b�h�ԍ�
// @return ����
//----------------------------------------------------------------------
XInput::XInput(int number):
	_isConnect(false) 
{
	_padNum = number;
	for (int i = 0; i < DXINPUT_BUTTON_MAX; i++) {
		_trg[i] = 0;
		_rel[i] = 0;
		_input.Buttons[i] = 0;
	}

	ReSet();

};

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
XInput::~XInput() {
	if (_isConnect) {
		_connectNum--;
	}
	ReSet();
}

//----------------------------------------------------------------------
// @brief �p�b�h�̓��͏����X�V
// @return �����������ǂ���
//----------------------------------------------------------------------
bool XInput::Input() {
	// �L�[�̓��́A�g���K���́A�����[�X���͂𓾂�
	unsigned char keyold[PAD_BUTTON_MAX]{};

	//UpdateJoyPad();

	for (int i = 0; i < DXINPUT_BUTTON_MAX; i++) {
		keyold[i] = _input.Buttons[i];
	}
	for (int i = 0; i < 4; i++) {
		keyold[DXINPUT_BUTTON_MAX + i] = _stickInput[i];
	}

	// ���͏�Ԃ��擾
	GetJoypadXInputState(_padNum, &_input);

	for (int i = 0; i < DXINPUT_BUTTON_MAX; i++) {
		// �g���K���͂̎擾
		_trg[i] = (_input.Buttons[i] ^ keyold[i]) & _input.Buttons[i];
		// �����[�X���͂̎擾
		_rel[i] = (_input.Buttons[i] ^ keyold[i]) & ~_input.Buttons[i];
	}

	// LT�{�^��
	unsigned char triggerButton = _input.LeftTrigger == 0 ? 0 : 1;
	// �g���K���͂̎擾
	_trg[XINPUT_BUTTON_LT] = (triggerButton ^ keyold[XINPUT_BUTTON_LT]) & triggerButton;
	// �����[�X���͂̎擾
	_rel[XINPUT_BUTTON_LT] = (triggerButton ^ keyold[XINPUT_BUTTON_LT]) & ~triggerButton;

	// RT�{�^��
	triggerButton = _input.RightTrigger == 0 ? 0 : 1;
	// �g���K���͂̎擾
	_trg[XINPUT_BUTTON_RT] = (triggerButton ^ keyold[XINPUT_BUTTON_RT]) & triggerButton;
	// �����[�X���͂̎擾
	_rel[XINPUT_BUTTON_RT] = (triggerButton ^ keyold[XINPUT_BUTTON_RT]) & ~triggerButton;

	float deadZone = 0.05f;
	// �X�e�B�b�N���͒l��50%�ȉ��Ȃ���͂��J�b�g����i�f�b�h�]�[���ݒ�j
	_input.ThumbLX = abs(_input.ThumbLX) > SHRT_MAX * deadZone ? _input.ThumbLX : 0;
	_input.ThumbLY = abs(_input.ThumbLY) > SHRT_MAX * deadZone ? _input.ThumbLY : 0;
	_input.ThumbRX = abs(_input.ThumbRX) > SHRT_MAX * deadZone ? _input.ThumbRX : 0;
	_input.ThumbRY = abs(_input.ThumbRY) > SHRT_MAX * deadZone ? _input.ThumbRY : 0;

	_adjustedLStick.x = (float)_input.ThumbLX / (float)SHRT_MAX;
	_adjustedLStick.y = (float)_input.ThumbLY / (float)SHRT_MAX;
	_adjustedRStick.x = (float)_input.ThumbRX / (float)SHRT_MAX;
	_adjustedRStick.y = (float)_input.ThumbRY / (float)SHRT_MAX;

	// �덷�ɂ���Ĕ͈͂𒴂����ꍇ�ɃN�����v������
	_adjustedLStick.x = Math::Clamp(-1.0f, 1.0f, _adjustedLStick.x);
	_adjustedLStick.y = Math::Clamp(-1.0f, 1.0f, _adjustedLStick.y);
	_adjustedRStick.x = Math::Clamp(-1.0f, 1.0f, _adjustedRStick.x);
	_adjustedRStick.y = Math::Clamp(-1.0f, 1.0f, _adjustedRStick.y);


	// �X�e�B�b�N���͂̒l���u-1.0f ~ 1.0f�v�ɕϊ�����
	// �X�e�B�b�N���͂̎擾
	// ��@���@���@�E
	short stickParam[4] = { _input.ThumbLY, _input.ThumbLX,-_input.ThumbLY,  -_input.ThumbLX };
	short ParamToZero[2] = { _input.ThumbLY,_input.ThumbLX };
	for (int i = 0; i < 4; i++) {
		_stickInput[i] = std::signbit(static_cast<float>(stickParam[i])) ? 0 : 1;
		_stickInput[i] = (ParamToZero[i % 2] != 0 ? 1 : 0) & _stickInput[i];
		// �g���K���͂̎擾
		_trg[DXINPUT_BUTTON_MAX + i] = (_stickInput[i] ^ keyold[DXINPUT_BUTTON_MAX + i]) & _stickInput[i];
		// �����[�X���͂̎擾
		_rel[DXINPUT_BUTTON_MAX + i] = (_stickInput[i] ^ keyold[DXINPUT_BUTTON_MAX + i]) & ~_stickInput[i];
	}



	return true;
};

//----------------------------------------------------------------------
// @brief �p�b�h���Ȃ��Ȃ����ꂽ���ɍĐݒ肷��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool XInput::UpdateJoyPad() {
	int connectNum = GetJoypadNum();
	if (_connectNum != connectNum) {
		_connectNum = connectNum;
		ReSet();
	}

	return true;
};

//----------------------------------------------------------------------
// @brief �Z�b�g�A�b�v���s��
// @return �Ȃ�
//----------------------------------------------------------------------
void XInput::ReSet() {
	ReSetupJoypad();
	ReSetupInputSystem();
};

//----------------------------------------------------------------------
// @brief ���X�e�B�b�N����������Ă��邩
// @return ��������Ă��邩�ǂ���
//----------------------------------------------------------------------
bool XInput::IsInputStickLeft() const{
	//���A�i���O�X�e�B�b�N����������Ă���Ȃ�true
	if (_input.ThumbLX != 0 || _input.ThumbLY != 0) { return true; }
	return false;
};

//----------------------------------------------------------------------
// @brief �E�X�e�B�b�N����������Ă��邩
// @return ��������Ă��邩�ǂ���
//----------------------------------------------------------------------
bool XInput::IsInputStickRight() const{
	//�E�A�i���O�X�e�B�b�N����������Ă���Ȃ�true
	if (_input.ThumbRX != 0 || _input.ThumbRY != 0) { return true; }
	return false;
};