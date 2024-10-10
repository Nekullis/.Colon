#include "Global.h"


Global global;

Global::Global() {
	_soundServer = new SoundServer();
	_isExit = false;
};

Global::~Global() {
	delete _soundServer;
};

bool Global::Init() {
	return true;
};

bool Global::ResourceLoad() {
	SetUseASyncLoadFlag(true);
	SetUseASyncLoadFlag(false);
	return true;
};

bool Global::SoundLoad() {
	// �񓯊��ǂݍ��ݐݒ�
	SetUseASyncLoadFlag(true);
	//BGM
	_soundServer->Add("BGM_Title", new SoundItemBGM("Sound/BGM/Title.mp3"));
	_soundServer->Add("BGM_Game", new SoundItemBGM("Sound/BGM/Game.mp3"));
	//SE	
	_soundServer->Add("SE_Gun", new SoundItemSE("Sound/SE/se_gun_fire05.mp3"));
	_soundServer->Add("SE_Explosion", new SoundItemSE("Sound/SE/small_explosion2.mp3"));

	SetUseASyncLoadFlag(FALSE);
	return true;
}

void DebugErrar(const std::source_location location) {
	std::string errar = "�t�@�C����:" + std::string(location.file_name()) + "\n" + "�s:" + std::to_string(location.line()) + "�ŃG���[����";
	MessageBox(NULL, errar.c_str(), "", MB_OK);
}