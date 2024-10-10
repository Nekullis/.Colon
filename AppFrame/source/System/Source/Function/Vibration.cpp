//----------------------------------------------------------------------
// @filename Vibration.h
// @author: Saito Ko
// @explanation
// コントローラーの振動を行うクラス
//----------------------------------------------------------------------
#include "../../Header/Function/Vibration.h"
#include "../../Header/Math/mymath.h"
#include "DxLib.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param padID パッドのID
// @return 無し
//----------------------------------------------------------------------
Vibration::Vibration(int padID)
{
	int checkID = -1;
	if (DX_INPUT_PAD1 <= padID && padID <= DX_INPUT_PAD4) checkID = padID;
	_padID = checkID;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Vibration::~Vibration()
{
}

//----------------------------------------------------------------------
// @brief コントローラーを振動させる
// @param frame 振動させるフレーム数
// @param power 振動の強さ
// @return 無し
//----------------------------------------------------------------------
void Vibration::SetVibrationController(float frame, int power)
{
	float remainingFrame = frame * 1000.0f / 60.0f; // フレームをミリ秒に変換 60fps
	StartJoypadVibration(_padID, power, static_cast<int>(remainingFrame), -1);
}