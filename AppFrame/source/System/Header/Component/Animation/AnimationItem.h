//----------------------------------------------------------------------
// @filename AnimationItem.h
// @author: Morozumi Hiroya Saito Ko
// @explanation
// �L�����N�^�[�̃A�j���[�V��������ێ�����N���X
// AnimationManager�N���X�ŁA���̃N���X�̃C���X�^���X��ǉ��E�폜���A�A�j���[�V�����̊Ǘ����s��
//----------------------------------------------------------------------
#pragma once

// �A�j���[�V�������
struct ANIMATION_INFO {
	// �A�j���[�V�����̃C���f�b�N�X�ԍ��imv1�t�@�C���Őݒ肳��Ă���ԍ��j
	int animIndex;
	// ���[�v�񐔁i0�Ȃ疳�����[�v�j
	int loopTimes;
};

class AnimationItem
{
private:
	friend class AnimationComponent;
	AnimationItem();
	~AnimationItem();

	// �A�j���[�V�����A�C�e���̏����ݒ�
	void Setup(int animIndex, int attachIndex, float totalTime, int loopTimes);

	// �e�L�����N�^�[���Ƃɐݒ肳��Ă���A�j���[�V�����̃X�e�[�^�X�ԍ��ienum�^����int�^�ɃL���X�g�������́j
	int _stateNo;

	// �A�j���[�V�����̃A�^�b�`�C���f�b�N�X
	int _attachIndex;
	// �A�j���[�V�����̑��Đ�����
	float _totalTime;
	// �A�j���[�V�����̍Đ�����
	float _playTime;

	// --------------------------------------------------------------------------------------------
	// ���[�V�����u�����h�֘A

	// �A�j���[�V�����J�n��
	float _openTotalTime;
	float _openTime;
	// �A�j���[�V�����I����
	float _closeTotalTime;
	float _closeTime;
	// --------------------------------------------------------------------------------------------

	// �c�胋�[�v��
	// 0�Ȃ疳�����[�v
	int _loopCnt;
};