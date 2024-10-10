//----------------------------------------------------------------------
// @filename ScreenVibration.cpp
// @author: Saito Ko
// @explanation
// ��ʏ�ł̃J���������Ă���f���̒��S���W�����炷�����s���N���X
//----------------------------------------------------------------------
#include "../../Header/Effect/ScreenVibration.h"

ScreenVibration* ScreenVibration::_instance = nullptr;
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
ScreenVibration::ScreenVibration() {
	_instance = this;
	vibration_x = 0.0f;
	vibration_y = 0.0f;
	max_x = 0.0f;
	max_y = 0.0f;
	time = 0.0f;
	use_flag = false;
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
ScreenVibration::~ScreenVibration() {
	_instance = nullptr;
};
//----------------------------------------------------------------------
// @brief �h���ő�̈ړ��l�Ǝ��Ԃ�ݒ�
// @param x x���̍ő�ړ��l
// @param y y���̍ő�ړ��l
// @param time �h��鎞��
// @return ����
//----------------------------------------------------------------------
void ScreenVibration::SetVibration(float x, float y, float time) {
		vibration_x = x;
		vibration_y = y;
		max_x = x;
		max_y = y;
		this->time = time;
		use_flag = true;
};
//----------------------------------------------------------------------
// @brief x���̍ő�ړ��l�Ǝ��Ԃ�ݒ�
// @param x x���̍ő�ړ��l
// @param time �h��鎞��
// @return ����
//----------------------------------------------------------------------
void ScreenVibration::SetVibrationX(float x, float time){
	vibration_x = x;
	max_x = x;
	this->time = time;
	use_flag = true;
};
//----------------------------------------------------------------------
// @brief y���̍ő�ړ��l�Ǝ��Ԃ�ݒ�
// @param y y���̍ő�ړ��l
// @param time �h��鎞��
// @return ����
//----------------------------------------------------------------------
void ScreenVibration::SetVibrationY(float y, float time){
	vibration_y = y;
	max_y = y;
	this->time = time;
	use_flag = true;
};
//----------------------------------------------------------------------
// @brief ��ʂ�h�炷����
// @return ����
//----------------------------------------------------------------------
void ScreenVibration::UpdateScreenVibration() {
	if (use_flag) {
		//z���ɑ΂���
		if (max_y <= 0) {
			if (max_x <= 0) {
				vibration_x = 0;
				vibration_y = 0;
				use_flag = false;
			}
		}

		{
			if (max_x != 0) {
				max_x -= max_x / time;
				vibration_x = rand() % (int)ceilf(max_x) - ceilf(max_x / 2.0f);
			}
			if (max_y != 0) {
				max_y -= max_y / time;
				vibration_y = rand() % (int)ceilf(max_y) - ceilf(max_y / 2);
			}
		}
		SetCameraScreenCenter((ScreenVibration::DispSizeW() / 2) + vibration_x, (ScreenVibration::DispSizeH() / 2) + vibration_y);
	}
};