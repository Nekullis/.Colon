//----------------------------------------------------------------------
// @filename AfterImage.h
// @author: Morozumi Hiroya
// @explanation
// �L�����N�^�[�̎c���\�����s���N���X
// �������ɂ������f���𕡐��̕\�����邱�ƂŎc����\������
//----------------------------------------------------------------------
#pragma once
#include <string>
#include <vector>
#include "DxLib.h"

class AfterImage
{
public:
	AfterImage();
	~AfterImage();

	// ����������
	// @param parentModelHandle: �e���f���̃n���h��
	// @param keyName: �L�[���iResourceServer�ł̃��f���f�[�^�̊Ǘ��Ɏg�p����j
	// @param modelName: ���f���̃p�X
	// @param afterImageNum: �����ɕ\������c���̍ő吔
	// @param remainTime: �c���̎�������
	void Init(int parentModelHandle, std::string keyName, std::string modelName, int afterImageNum = 10, int remainTime = 10);

	// �c����ǉ�����
	// @param animIndex: �A�j���[�V�����̃C���f�b�N�X�imv1�t�@�C�����ł̃C���f�b�N�X�ԍ��j�i-1�̏ꍇ�̓A�j���[�V������K�����Ȃ��j
	// @param playTime: �A�j���[�V�����̍Đ�����
	void AddAfterImage(int animIndex = -1, float playTime = 0);

	// �X�V����
	void Process();
	
	// �`�揈��
	void Render();

private:	
	// �c�����f���̏��
	struct ModelInfo
	{
		// �g�p�t���O
		bool use;
		// �c��̎�������
		int remainTime;

		// ----------------------------------------
		// ���f�����
		
		// ���f���n���h��
		int modelHandle;

		// �f�B�t���[�Y�J���[�̃X�P�[���l
		// �}�e���A���̃f�B�t���[�Y�J���[�Ɋ|�����킹��l
		// RGBA(0.0f ~ 1.0f)
		COLOR_F difColorScale;

		// �A�j���[�V�����̃A�^�b�`�C���f�b�N�X�ԍ�
		int attachIndex;
		// ----------------------------------------
	};
	std::vector<ModelInfo*> _modelInfo;

	// �e���f���̃n���h��
	int _parentModelHandle;

	// �����ɕ\������c���̍ő吔
	int _afterImageNum;
	// �c���̎�������
	int _remainTimeMax;
};