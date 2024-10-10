
#include "dxlib.h"
#include "../System/Header/Input/XInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"

// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"
#include "../AppFrame/source/Application/Global.h"

//#define FULLSCREEN

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual bool BeforeDXLib_Init() { return true; }	// DXLib_Init() ���s�O�ɍs����������������΃I�[�o�[���C�h

#if !defined(_DEBUG) || defined(FULLSCREEN)
	virtual int DispSizeW() { return 1920; }
	virtual int DispSizeH() { return 1080; }
#else
	virtual int DispSizeW() { return 1280; }
	virtual int DispSizeH() { return 720; }
#endif

	static	ApplicationBase	*GetInstance() { return _lpInstance; }

protected:
	static	ApplicationBase	*_lpInstance;

	ModeServer* _serverMode;
};
