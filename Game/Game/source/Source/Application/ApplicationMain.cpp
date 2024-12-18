#include "../../Header/Application/ApplicationMain.h"
#include "../../Header/Mode/ModeGame.h"

// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	// 音声の読み込み
	global.SoundLoad();
	
	// 前の処理から今の処理の計算時間を得るクラス
	_timer = new Timer();
	_timer->Start();
	// FPSを安定させるためのクラスを初期化
	_fpsController = new Fps();

	// モードの登録
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