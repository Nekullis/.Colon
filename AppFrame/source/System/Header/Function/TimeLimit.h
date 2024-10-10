//----------------------------------------------------------------------
// @filename TimeLimit.h
// @author: Saito Ko
// @explanation
// �������Ԃ̊Ǘ����s���N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include <math.h>
#include <string>
class TimeLimit
{
public:
	TimeLimit();
	~TimeLimit();
	void SetTimeLimit(const int minutes,const int second);
	
	float Update();
	int SecondsToTime();
	int GetElapsedSecond();
	void Stop();
	void Restart();
	
	static TimeLimit* GetInstance() { return _instance; }

	float GetRemainingTime() const { return _remainingTime; }
	int GetTimeLimit() const { return _timeLimitSecond > 0 ? _timeLimitSecond : 0; }
	bool GetIsEnd() const { return _remainingTime <= 0; }
	int GetElapsedTime() const { return _elapsedTime; }

	int GetDigits();

	float GetStartTime() const { return _setTime / 1000.0f; }

protected:
	static TimeLimit* _instance;// ���̃N���X�̃C���X�^���X
	float _startTime,_timeLimit;// �J�n���ԂƐ�������
	float _setTime;// �ݒ莞��
	float _remainingTime;// �c�莞��
	int _stopTime;// �X�g�b�v��������
	bool _IsStop;// ���Ԃ��~�߂邩�ǂ���

	int _timeLimitSecond; // ��������
	int _elapsedTime; // �o�ߎ���
};

