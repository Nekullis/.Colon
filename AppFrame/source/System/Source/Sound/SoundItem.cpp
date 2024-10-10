//----------------------------------------------------------------------
// @filename SoundItemBase.cpp
// @author: Saito Ko
// @explanation
// SE��BGM�Ȃǂ̃T�E���h�A�C�e���̃N���X�W
//----------------------------------------------------------------------
#include "../../Header/Sound/SoundItem.h"
#include "../../Header/Sound/SoundServer.h"

const char SoundItemBase::FADE_IN = 1;
const char SoundItemBase::FADE_OUT = 2;

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param filename: �t�@�C����
// @return �Ȃ�
//----------------------------------------------------------------------
SoundItemBase::SoundItemBase(std::string filename) {
	_filename = filename;
	_snd = -1;
	_volume = 0;
	_pan = 0;
	_frequency = 0;		// �t�@�C���ɂ���ĕW�����Ⴄ�̂�
	_sndServer = NULL;
	_currentTime = 0;
	_fadeTime = 0;
	IsFade = 0;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
SoundItemBase::~SoundItemBase() {
	Unload();
}

//----------------------------------------------------------------------
// @brief �폜
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBase::Unload() {
	if (_snd != -1) {
		DeleteSoundMem(_snd);
		_snd = -1;
	}
}

//----------------------------------------------------------------------
// @brief ���[�h����Ă��邩�ǂ���
// @return true: ���[�h����Ă���
//----------------------------------------------------------------------
bool	SoundItemBase::IsLoad() {
	// �񓯊����[�h���I����Ă��邩�H
	if (_snd != -1 && CheckHandleASyncLoad(_snd) == FALSE) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
// @brief �Đ�����Ă��邩�ǂ���
// @return �Ȃ�
//----------------------------------------------------------------------
bool	SoundItemBase::IsPlay() {
	if (_snd != -1 && CheckSoundMem(_snd) == 1) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
// @brief �T�E���h�̒�~
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBase::Stop() {
	if (_snd != -1) {
		StopSoundMem(_snd);
	}
}

//----------------------------------------------------------------------
// @brief �{�����[���̒l���擾
// @return �Ȃ�
//----------------------------------------------------------------------
int	 SoundItemBase::GetVolume() const { 
	return _volume; 
}

//----------------------------------------------------------------------
// @brief �p���̒l���擾
// @return �Ȃ�
//----------------------------------------------------------------------
int	 SoundItemBase::GetPan() const { 
	return _pan; 
}

//----------------------------------------------------------------------
// @brief �p���̒l��ݒ�
// @param pan: �p���̒l
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBase::SetPan(int pan) {
	_pan = pan;
	if (_snd != -1) {
		ChangePanSoundMem(_pan, _snd);
	}
}

//----------------------------------------------------------------------
// @brief �t���[�N�G���V�[�̒l���擾
// @return �Ȃ�
//----------------------------------------------------------------------
int	 SoundItemBase::GetFrequency() const { 
	return _frequency; 
}

//----------------------------------------------------------------------
// @brief �t���[�N�G���V�[�̒l��ݒ�
// @param frequency: �t���[�N�G���V�[�̒l
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBase::SetFrequency(int frequency) {
	_frequency = frequency;
	if (_snd != -1 && _frequency != 0) {
		SetFrequencySoundMem(_frequency, _snd);
	}
}

//----------------------------------------------------------------------
// @brief �t���[�N�G���V�[�̒l�����Z�b�g
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBase::ResetFrequency() {
	_frequency = 0;
	if (_snd != -1) {
		ResetFrequencySoundMem(_snd);
		_frequency = GetFrequencySoundMem(_snd);
	}
}

//----------------------------------------------------------------------
// @brief �t�F�[�h�̉��ʂ�ݒ�
// @return �Ȃ�
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
// @brief �Đ�
// @param flg: �Đ��t���O
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBase::PlayMem(int flg) {
	// �Đ��O�ɉ��ʓ���ݒ�
	SetVolume();
	SetPan(_pan);
	SetFrequency(_frequency);
	PlaySoundMem(_snd, flg, TRUE);
}

//----------------------------------------------------------------------
// @brief �T�E���h�̉��ʂ�ύX
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemSE::SetVolume() {
	_volume = _sndServer->GetSeVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}

//----------------------------------------------------------------------
// @brief �T�E���h�̉��ʂ�ύX
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBGM::SetVolume() {
	_volume = _sndServer->GetBgmVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}

//----------------------------------------------------------------------
// @brief BGM�̍Đ�
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemBGM::Play() {
	if (_sndServer) {
		_sndServer->StopType(TYPE::BGM);
	}
	StreamLoad();	// �X�g���[���Đ��̂��̂����[�h����
	if (IsPlay() == false) {	// BGM�͍Đ�����Ă��Ȃ��ꍇ�̂�
		PlayMem(DX_PLAYTYPE_LOOP);
	}
}

//----------------------------------------------------------------------
// @brief BGM�̉��ʂ̐ݒ�
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemVOICE::SetVolume() {
	_volume = _sndServer->GetVoiceVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemOneShot::Update() {
	int snd = _snd;
	base::Update();
	if (snd != -1 && _snd == -1) {
		// �Đ�����Ă�����Unload()����Ă���ꍇ�A�������폜
		_sndServer->Del(this);
	}
}

//----------------------------------------------------------------------
// @brief �T�E���h�̉��ʂ�ύX
// @return �Ȃ�
//----------------------------------------------------------------------
void	SoundItemOneShot::SetVolume() {
	_volume = _sndServer->GetSeVolume();
	if (_snd != -1) {
		ChangeVolumeSoundMem(_volume, _snd);
	}
}
