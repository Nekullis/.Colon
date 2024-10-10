#include "../../Header/Application/ApplicationMain.h"
#include "../../Header/Mode/ModeGame.h"

// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	// �����̓ǂݍ���
	global.SoundLoad();
	
	// �O�̏������獡�̏����̌v�Z���Ԃ𓾂�N���X
	_timer = new Timer();
	_timer->Start();
	// FPS�����肳���邽�߂̃N���X��������
	_fpsController = new Fps();

	// ���[�h�̓o�^
	ModeServer::GetInstance()->Add(new ModeGame(), 1, "ModeGame");
	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	delete _timer; _timer = nullptr;
	delete _fpsController; _fpsController = nullptr;
	ResourceServer::DeleteResourceAll();
	return true;
}

bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	_fpsController->WaitFps();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	_fpsController->DrawFps(0,0);
	return true;
}