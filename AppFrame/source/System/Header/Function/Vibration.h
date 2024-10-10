//----------------------------------------------------------------------
// @filename Vibration.h
// @author: Saito Ko
// @explanation
// コントローラーの振動を行うクラス
//----------------------------------------------------------------------
#pragma once

class Vibration
{
public:
	Vibration(int padID);
	~Vibration();
	void SetVibrationController(float frame, int power);

private:
	int _padID;
};