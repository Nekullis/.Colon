//----------------------------------------------------------------------
// @filename ScreenVibration.h
// @author: Saito Ko
// @explanation
// ��ʏ�ł̃J���������Ă���f���̒��S���W�����炷�����s���N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include <math.h>
#include <string>
class ScreenVibration
{
public:
	ScreenVibration();
	~ScreenVibration();
	void SetVibration(float x, float y, float time);//��ʐU��
	void SetVibrationX(float x, float time);
	void SetVibrationY(float y, float time);
	void UpdateScreenVibration();
	
	static ScreenVibration* _instance;
	static ScreenVibration* GetInstance() { return _instance; }

#ifdef _DEBUG
	virtual float DispSizeW() { return 1280.0f; }
	virtual float DispSizeH() { return 720.0f; }
#else
	virtual float DispSizeW() { return 1920.0f; }
	virtual float DispSizeH() { return 1080.0f; }
#endif

protected:
	//�U���p�̕ϐ�
	float vibration_x,vibration_y;//�U����
	float max_x, max_y;//�U���̍ő�l
	float time;//�U������
	bool use_flag;//�U�������ǂ���
};