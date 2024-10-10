//----------------------------------------------------------------------
// @filename Timer.cpp
// @author: Saito Ko
// @explanation
// �������Z�Ŏg�p���鏈���ɂ����������Ԃ��v������N���X
//----------------------------------------------------------------------
#include "../../Header/Function/Timer.h"
Timer* Timer::_instance= nullptr;

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
Timer::Timer() {
	_instance = this;
	_lastTime = 0;
	_elapsedTime = 0.0f;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Timer::~Timer() {
	_instance = nullptr;
}

//----------------------------------------------------------------------
// @brief �^�C�}�[���X�^�[�g
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Timer::Start() {
	_lastTime = GetNowHiPerformanceCount();
	return true;
}

//----------------------------------------------------------------------
// @brief �O�̃t���[������̌o�ߎ��Ԃ��v�Z
// @return �o�ߎ���
//----------------------------------------------------------------------
double Timer::TimeElapsed() {
	LONGLONG _nowTime = GetNowHiPerformanceCount();
	int _interval = (int)(_nowTime - _lastTime);
	_elapsedTime = (double)_interval / 1000000;
	_lastTime = _nowTime;
	return _elapsedTime;//�O�t���[������̌o�ߎ��Ԃ�Ԃ�
}