//----------------------------------------------------------------------
// @filename TimeLimit.cpp
// @author: Saito Ko
// @explanation
// �������Ԃ̊Ǘ����s���N���X
//----------------------------------------------------------------------
#include "../../Header/Function/TimeLimit.h"
#include "../AppFrame/source/Application/UtilMacro.h"
TimeLimit* TimeLimit::_instance = nullptr;
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
TimeLimit::TimeLimit() {
	// �C���X�^���X��ۑ�
	if (_instance != nullptr) {
		DebugErrar();
		return;
	}
	_instance = this;
	// ������
	_timeLimit = 0.0f;
	_startTime = 0.0f;
	_remainingTime = 0.0f;
	_setTime = 0;
	_IsStop = false;
	_stopTime = 0;
	_timeLimitSecond = 0;
	_elapsedTime = 0;
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
TimeLimit::~TimeLimit() {
	_instance = nullptr;
};
//----------------------------------------------------------------------
// @brief �������Ԃ�ݒ�
// @return ����
//----------------------------------------------------------------------
void TimeLimit::SetTimeLimit(const int minutes, const int second) {
	// ���Ԃ��~���b�ɕϊ�
	_timeLimit = static_cast<float>((minutes * 60 + second) * 1000);
	// �ݒ莞�Ԃ�ۑ�
	_setTime = _timeLimit;
	// �J�n���Ԃ��擾
	_startTime = static_cast<float>(GetNowCount());
	// �c�莞�Ԃ��v�Z
	_remainingTime = static_cast<float>(_timeLimit) - (GetNowCount() - _startTime); 
	// �~���b��b�ɕϊ�
	_remainingTime /= 1000;
	// �X�g�b�v���Ԃ�������
	_stopTime = GetNowCount();
	// �X�g�b�v��Ԃɂ���
	_IsStop = true;
	_timeLimitSecond = SecondsToTime();
	_elapsedTime = GetElapsedSecond();
};
//----------------------------------------------------------------------
// @brief �������Ԃ��v�Z���鏈�����~�߂�
// @return ����
//----------------------------------------------------------------------
void TimeLimit::Stop() {
	// �X�g�b�v���Ă��Ȃ��ꍇ
	if (!_IsStop) {
		_IsStop = true;
		_stopTime = GetNowCount();
	}
	// �X�g�b�v���Ă���ꍇ
	else {
		// �X�g�b�v���Ԃ��X�V
		_startTime += GetNowCount() - _stopTime;
		_stopTime = GetNowCount();
	}
};
//----------------------------------------------------------------------
// @brief �������Ԃ��v�Z���鏈�����ĊJ����
// @return ����
//----------------------------------------------------------------------
void TimeLimit::Restart() {
	// �~�܂��Ă������Ԃ��J�n���Ԃɑ���
	_startTime += GetNowCount() - _stopTime;
	_stopTime = 0;
	_IsStop = false;
};
//----------------------------------------------------------------------
// @brief �������Ԃ��v�Z����
// @return ����
//----------------------------------------------------------------------
float TimeLimit::Update() {
	// �X�g�b�v���Ă���ꍇ�A�~�܂�O�̍Ō�̎��Ԃ�Ԃ�
	if (_IsStop) {
		return _remainingTime;
	}

	// �c�莞�Ԃ��v�Z
	_remainingTime = static_cast<float>(_timeLimit) - (GetNowCount() - _startTime); 
	// �~���b��b�ɕϊ�
	_remainingTime /= 1000;

	_timeLimitSecond = SecondsToTime();
	_elapsedTime = GetElapsedSecond();

	return _remainingTime;
};
//----------------------------------------------------------------------
// @brief �������Ԃ��擾
// @return ����
//----------------------------------------------------------------------
int TimeLimit::SecondsToTime() {
	// �c�莞�Ԃ𕪂ƕb�ɕϊ�
	float time = _remainingTime / 60;
	int min = static_cast<int>(time);
	int sec = static_cast<int>((time - min) * 60);

	return static_cast<int>(min * powf(10.0f, 2.0f) + sec);
};
//----------------------------------------------------------------------
// @brief �o�ߎ��Ԃ��擾
// @return ����
//----------------------------------------------------------------------
int TimeLimit::GetElapsedSecond(){
	// �o�ߎ��Ԃ��擾
	float time = (GetNowCount() - _startTime) / (60 * 1000);
	
	int min = static_cast<int>(time);
	int sec = static_cast<int>((time - min) * 60);

	return static_cast<int>(min * powf(10.0f, 2.0f) + sec);
};

int TimeLimit::GetDigits(){
	int digits = 0;
	int timeLimit = static_cast<int>(GetRemainingTime());
	do
	{
		timeLimit /= 10;
		digits++;
	} while (timeLimit != 0);

	return digits;
};