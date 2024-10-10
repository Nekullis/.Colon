//----------------------------------------------------------------------
// @filename Vibration.h
// @author: Saito Ko
// @explanation
// �R���g���[���[�̐U�����s���N���X
//----------------------------------------------------------------------
#include "../../Header/Function/Vibration.h"
#include "../../Header/Math/mymath.h"
#include "DxLib.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param padID �p�b�h��ID
// @return ����
//----------------------------------------------------------------------
Vibration::Vibration(int padID)
{
	int checkID = -1;
	if (DX_INPUT_PAD1 <= padID && padID <= DX_INPUT_PAD4) checkID = padID;
	_padID = checkID;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Vibration::~Vibration()
{
}

//----------------------------------------------------------------------
// @brief �R���g���[���[��U��������
// @param frame �U��������t���[����
// @param power �U���̋���
// @return ����
//----------------------------------------------------------------------
void Vibration::SetVibrationController(float frame, int power)
{
	float remainingFrame = frame * 1000.0f / 60.0f; // �t���[�����~���b�ɕϊ� 60fps
	StartJoypadVibration(_padID, power, static_cast<int>(remainingFrame), -1);
}