//----------------------------------------------------------------------
// @filename Timer.h
// @author: Saito Ko
// @explanation
// �������Z�Ŏg�p���鏈���ɂ����������Ԃ��v������N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
class Timer
{
public:
	Timer();
	~Timer();
	bool Start();//���̃N���X���Ăяo�����Ƃ��ɐ錾����
	double TimeElapsed();//�O�̃t���[������̌o�ߎ��Ԃ��v�Z
	static Timer* GetInstance() { return _instance; }
	//--��
	LONGLONG GetLastTime() const { return _lastTime; }
	double GetElapsedTime() const { return _elapsedTime; }
private:
	static Timer* _instance;
	LONGLONG _lastTime;//�O�̃t���[���̍Ō�̎���
	double _elapsedTime;//�O�̃t���[������̌o�ߎ���
};

