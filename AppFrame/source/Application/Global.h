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
//�֐�
	Global();
	~Global();
	bool Init();
	bool ResourceLoad();
	bool SoundLoad();
	void SetExit() { _isExit = true; }
	bool GetExit() const { return _isExit; }

//�ϐ��E�N���X
	SoundServer* _soundServer;
	bool _isExit; // �I���t���O
};
extern Global global;
extern void DebugErrar(const std::source_location location = std::source_location::current());
