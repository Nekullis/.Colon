//----------------------------------------------------------------------
// @filename SoundItemBase.cpp
// @author: Saito Ko
// @explanation
// SEやBGMなどのサウンドアイテムのクラス集
//----------------------------------------------------------------------
#include "../../Header/Sound/SoundItem.h"
#include "../../Header/Sound/SoundServer.h"

const char SoundItemBase::FADE_IN = 1;
const char SoundItemBase::FADE_OUT = 2;

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param filename: ファイル名
// @return なし
//----------------------------------------------------------------------
SoundItemBase::SoundItemBase(std::string filename) {
	_filename = filename;
	_snd = -1;
	_volume = 0;
	_pan = 0;
	_frequency = 0;		// ファイルによって標準が違うので
	_sndServer = NULL;
	_currentTime = 0;
	_fadeTime = 0;
	IsFade = 0;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
SoundItemBase::~SoundItemBase() {
	Unload();
}

//----------------------------------------------------------------------
// @brief 削除
// @return なし
//----------------------------------------------------------------------
void	SoundItemBase::Unload() {
	if (_snd != -1) {
		DeleteSoundMem(_snd);
		_snd = -1;
	}
}

//----------------------------------------------------------------------
// @brief ロードされているかどうか
// @return true: ロードされている
//----------------------------------------------------------------------
bool	SoundItemBase::IsLoad() {
	// 非同期ロードが終わっているか？
	if (_snd != -1 && CheckHandleASyncLoad(_snd) == FALSE) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
// @brief 再生されているかどうか
// @return なし
//----------------------------------------------------------------------
bool	SoundItemBase::IsPlay() {
	if (_snd != -1 && CheckSoundMem(_snd) == 1) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
// @brief サウンドの停止
// @return なし
//----------------------------------------------------------------------
void	SoundItemBase::Stop() {
	if (_snd != -1) {
		StopSoundMem(_snd);
	}
}

//----------------------------------------------------------------------
// @brief ボリュームの値を取得
// @return なし
//----------------------------------------------------------------------
int	 SoundItemBase::GetVolume() const { 
	return _volume; 
}

//----------------------------------------------------------------------
// @brief パンの値を取得
// @return なし
//----------------------------------------------------------------------
int	 SoundItemBase::GetPan() const { 
	return _pan; 
}

//----------------------------------------------------------------------
// @brief パンの値を設定
// @param pan: パンの値
// @return なし
//----------------------------------------------------------------------
void	SoundItemBase::SetPan(int pan) {
	_pan = pan;
	if (_snd != -1) {
		ChangePanSoundMem(_pan, _snd);
	}
}

//----------------------------------------------------------------------
// @brief フリークエンシーの値を取得
// @return なし
//----------------------------------------------------------------------
int	 SoundItemBase::GetFrequency() const { 
	return _frequency; 
}

//----------------------------------------------------------------------
// @brief フリークエンシーの値を設定
// @param frequency: フリークエンシーの値
// @return なし
//----------------------------------------------------------------------
void	SoundItemBase::SetFrequency(int frequency) {
	_frequency = frequency;
	if (_snd != -1 && _frequency != 0) {
		SetFrequencySoundMem(_frequency, _snd);
	}
}

//----------------------------------------------------------------------
// @brief フリークエンシーの値をリセット
// @return なし
//----------------------------------------------------------------------
void	SoundItemBase::ResetFrequency() {
	_frequency = 0;
	if (_snd != -1) {
		ResetFrequencySoundMem(_snd);
		_frequency = GetFrequencySoundMem(_snd);
	}
}

//----------------------------------------------------------------------
// @brief フェードの音量を設定
// @return なし
//----------------------------------------------------------------------
void SoundItemBase::SetFadeVolume() {
	if (IsFade == 1) {
	// FadeIn
		int nowTime = GetNowCount() - _currentTime;
		_volume = static_cast<int>(Easing::Linear(static_cast<float>(nowTime), 0.0f, static_cast<float>(_sndServer->GetBgmVolume()), static_cast<float>(_fadeTime)));
		if (nowTime >= _fadeTime) {
			IsFade = 0;
		}
	}
	else if (IsFade == 2) {
	// FadeOut
		int nowTime = GetNowCount() - _currentTime;
		_volume = static_cast<int>(Easing::Linear(static_cast<float>(nowTime), static_cast<float>(_sndServer->GetBgmVolume()), 0.0f, static_cast<float>(_fadeTime)));
		if (nowTime >= _fadeTime) {
			IsFade = 0;
		}
	}
	
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
};

//----------------------------------------------------------------------
// @brief 再生
// @param flg: 再生フラグ
// @return なし
//----------------------------------------------------------------------
void	SoundItemBase::PlayMem(int flg) {
	// 再生前に音量等を設定
	SetVolume();
	SetPan(_pan);
	SetFrequency(_frequency);
	PlaySoundMem(_snd, flg, TRUE);
}

//----------------------------------------------------------------------
// @brief サウンドの音量を変更
// @return なし
//----------------------------------------------------------------------
void	SoundItemSE::SetVolume() {
	_volume = _sndServer->GetSeVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}

//----------------------------------------------------------------------
// @brief サウンドの音量を変更
// @return なし
//----------------------------------------------------------------------
void	SoundItemBGM::SetVolume() {
	_volume = _sndServer->GetBgmVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}

//----------------------------------------------------------------------
// @brief BGMの再生
// @return なし
//----------------------------------------------------------------------
void	SoundItemBGM::Play() {
	if (_sndServer) {
		_sndServer->StopType(TYPE::BGM);
	}
	StreamLoad();	// ストリーム再生のものをロードする
	if (IsPlay() == false) {	// BGMは再生されていない場合のみ
		PlayMem(DX_PLAYTYPE_LOOP);
	}
}

//----------------------------------------------------------------------
// @brief BGMの音量の設定
// @return なし
//----------------------------------------------------------------------
void	SoundItemVOICE::SetVolume() {
	_volume = _sndServer->GetVoiceVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void	SoundItemOneShot::Update() {
	int snd = _snd;
	base::Update();
	if (snd != -1 && _snd == -1) {
		// 再生されていたがUnload()されている場合、自分を削除
		_sndServer->Del(this);
	}
}

//----------------------------------------------------------------------
// @brief サウンドの音量を変更
// @return なし
//----------------------------------------------------------------------
void	SoundItemOneShot::SetVolume() {
	_volume = _sndServer->GetSeVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}
