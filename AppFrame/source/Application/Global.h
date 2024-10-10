#pragma once
#include "../System/Header/Resource/ResourceServer.h"
#include "../System/Header/Function/Timer.h"
#include "../System/Header/Sound/SoundItem.h"
#include "../System/Header/Sound/SoundServer.h"
#include <string>
#include <source_location>

//#define FULLSCREEN

class Global
{
public:
//関数
	Global();
	~Global();
	bool Init();
	bool ResourceLoad();
	bool SoundLoad();
	void SetExit() { _isExit = true; }
	bool GetExit() const { return _isExit; }

//変数・クラス
	SoundServer* _soundServer;
	bool _isExit; // 終了フラグ
};
extern Global global;
extern void DebugErrar(const std::source_location location = std::source_location::current());
