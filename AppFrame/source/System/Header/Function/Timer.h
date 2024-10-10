//----------------------------------------------------------------------
// @filename Timer.h
// @author: Saito Ko
// @explanation
// 物理演算で使用する処理にかかった時間を計測するクラス
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
class Timer
{
public:
	Timer();
	~Timer();
	bool Start();//このクラスを呼び出したときに宣言する
	double TimeElapsed();//前のフレームからの経過時間を計算
	static Timer* GetInstance() { return _instance; }
	//--仮
	LONGLONG GetLastTime() const { return _lastTime; }
	double GetElapsedTime() const { return _elapsedTime; }
private:
	static Timer* _instance;
	LONGLONG _lastTime;//前のフレームの最後の時間
	double _elapsedTime;//前のフレームからの経過時間
};

