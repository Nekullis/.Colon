//----------------------------------------------------------------------
// @filename AnimationManager.h
// @author: Morozumi Hiroya Saito Ko
// @explanation
// �L�����N�^�[�̃A�j���[�V�������Ǘ�����N���X
// AnimationItem��ǉ��E�폜���A�A�j���[�V�����̊Ǘ����s��
//----------------------------------------------------------------------
#pragma once
#include "AnimationItem.h"
#include "MotionList.h"
#include "../Component.h"
#include <map>
#include <vector>

// �A�j���[�V�������
// int : �e�L�����N�^�[�̃A�j���[�V�����X�e�[�^�X�ԍ��ienum�^����int�^�ɃL���X�g�������́j
// ANIMATION_INFO : �A�j���[�V�������iAnimationItem.h�Œ�`�j
typedef std::map<int, ANIMATION_INFO> ANIM_MAP;

typedef std::string CHARA_NAME;

class AnimationComponent : public Component
{
public:	

	AnimationComponent(const std::string& charaName, int modelHandle, int* stateNum ,const std::string& filePath, class ObjectBase* owner , int updateOwder);
	~AnimationComponent();

	// --------------------------------------------------------------------------------------------
	// �A�j���[�V�������p�}�b�v�R���e�i�̏����ݒ���s��
	// ���ɓ����L�����N�^�[�����o�^����Ă���ꍇ�́A����̃}�b�v���g�p����

	// @param charaName �L�����N�^�[��
	// @param modelHandle ���f���n���h��
	// @param fileName ���[�V�������X�g�t�@�C����
	void InitMap(const std::string& charaName , int modelHandle, const std::string& fileName);

	// @param charaName �L�����N�^�[��
	// @param modelHandle ���f���n���h��
	// @param motionList ���[�V�������̔z��
	void InitMap(CHARA_NAME charaName, int modelHandle, const std::vector<MotionNamePair>& motionList);
	// --------------------------------------------------------------------------------------------

	// �A�j���[�V�����̍X�V����
	void Process();

	// �Ō�ɒǉ����ꂽ�i�ŐV�́j�A�j���[�V�����̍Đ����Ԃ��擾����
	float GetPlayTime() const { return _playTime; }

	// �f�o�b�O���̕`��
	void DrawDebugInfo();

private:
	// �A�j���[�V�����A�C�e����ǉ�����
	void AddAnimationItem();

	// �S�L�����N�^�[�̃A�j���[�V�������p�}�b�v�R���e�i
	// ����̃L�����N�^�[�̃A�j���[�V�����������L���邽�߁A�L�����N�^�[�����L�[�ɂ��ă}�b�v��ێ�����
	static std::map<CHARA_NAME, ANIM_MAP> _allCharaAnimMap;

	// �A�j���[�V�������p�}�b�v�R���e�i
	// _allCharaAnimMap����w�肵���L�����N�^�[�̃A�j���[�V���������擾���邽�߂̃}�b�v
	// �L�[ : int�^ �L�����N�^�[�̃X�e�[�^�X�ԍ�
	// �o�����[ : ANIMATION_INFO�^ �A�j���[�V�������
	ANIM_MAP* _targetAnimMap;

	// ���f���n���h��
	int _modelHandle;

	// �A�j���[�V�����̔ԍ�
	int* _stateNum;
	// �Đ����A�j���[�V�����̃X�e�[�^�X�ԍ�
	int _playingAnimStateNum;

	// �A�j���[�V�����A�C�e��
	std::vector<AnimationItem*> _animContainer;

	// �Ō�ɒǉ����ꂽ�i�ŐV�́j�A�j���[�V�����A�C�e��
	AnimationItem* _latestAnimItem;
	// �Ō�ɒǉ����ꂽ�i�ŐV�́j�A�j���[�V�����̍Đ�����
	float _playTime;
};