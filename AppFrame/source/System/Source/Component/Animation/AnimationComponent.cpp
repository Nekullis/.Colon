//----------------------------------------------------------------------
// @filename AnimationManager.cpp
// @author: Morozumi Hiroya Saito Ko
// @explanation
// �L�����N�^�[�̃A�j���[�V�������Ǘ�����N���X
// AnimationItem��ǉ��E�폜���A�A�j���[�V�����̊Ǘ����s��
//----------------------------------------------------------------------
#include "../../../Header/Component/Animation/AnimationComponent.h"
#include "../../../Header/Component/Object/ObjectBase.h"
#include "../../../../File/CFile/CFile.h"
#include "../../../../Application/UtilMacro.h"
#include "dxlib.h"

std::map<CHARA_NAME, ANIM_MAP> AnimationComponent::_allCharaAnimMap;

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
AnimationComponent::AnimationComponent(const std::string& charaName, int modelHandle, int* stateNum ,const std::string& filePath, ObjectBase* owner, int updateowder) 
: Component(owner, updateowder),
_stateNum(stateNum),
_modelHandle(modelHandle),
_playingAnimStateNum(-1),
_playTime(0.0f),
_targetAnimMap(nullptr),
_latestAnimItem(nullptr)
{
	InitMap(charaName, modelHandle, filePath);
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	for (auto itr = _animContainer.begin(); itr != _animContainer.end(); ++itr)
	{
		delete (*itr);
		(*itr) = nullptr;
	}
	_animContainer.clear();
	_targetAnimMap = nullptr;
}
//----------------------------------------------------------------------
// @brief �A�j���[�V�������p�}�b�v�R���e�i�̏����ݒ���s��
//             ���ɓ����L�����N�^�[�����o�^����Ă���ꍇ�́A����̃}�b�v���g�p����
// @param charaName �L�����N�^�[��
// @param modelHandle ���f���n���h��
// @param fileName ���[�V�������X�g�t�@�C����
// @return �Ȃ�
//----------------------------------------------------------------------
void AnimationComponent::InitMap(const std::string& charaName, int modelHandle,const std::string& fileName)
{
	auto itr = _allCharaAnimMap.find(charaName);
	if (itr == _allCharaAnimMap.end()) {
		std::string filePath = "Data/MotionList/" + fileName;

		// csv�t�@�C����ǂݍ���
		CFile file(filePath);
		// �t�@�C�����J�����ꍇ
		if (file.Success()) {
			const char* data = (const char*)file.Data();
			int c = 0;
			int size = file.Size();
			int stateNo = 0;
			while (c < size) {
				std::string motionName;
				int loopTimes = 0;
				// ���[�V���������擾
				c += GetString(&data[c], &motionName);
				// �J���}�̈ʒu��������
				c += FindString(&data[c], ',', &data[size]); c++;
				// ���[�v�񐔂��擾
				c += GetDecNum(&data[c], &loopTimes);
				// ���s�ȂǃX�L�b�v
				c += SkipSpace(&data[c], &data[size]);

				ANIMATION_INFO info{};
				info.animIndex = MV1LoadModel(motionName.c_str());
				info.loopTimes = loopTimes;
				_allCharaAnimMap[charaName][stateNo] = info;
				stateNo++;
#ifdef _DEBUG
				if (info.animIndex == -1) {
					std::string message = "[" + motionName + "] �A�j���[�V������������܂���ł���";
					MessageBox(NULL, message.c_str(), "�G���[", MB_OK);
				}
#endif // _DEBUG
			}
		}
#ifdef _DEBUG
		else {
			// �t�@�C�����J���Ȃ������ꍇ
			MessageBox(NULL, "�t�@�C�����J���܂���ł���", "�G���[", MB_OK);
		}
#endif // _DEBUG
	}
	_targetAnimMap = &_allCharaAnimMap[charaName];
	_modelHandle = modelHandle;
}
//----------------------------------------------------------------------
// @brief �A�j���[�V�������p�}�b�v�R���e�i�̏����ݒ���s��
//             ���ɓ����L�����N�^�[�����o�^����Ă���ꍇ�́A����̃}�b�v���g�p����
// @param charaName �L�����N�^�[��
// @param modelHandle ���f���n���h��
// @param motionList ���[�V�������̔z��
// @return �Ȃ�
//----------------------------------------------------------------------
void AnimationComponent::InitMap(CHARA_NAME charaName, int modelHandle, const std::vector<MotionNamePair>& motionList)
{
	auto itr = _allCharaAnimMap.find(charaName);
	// ���ɓ����L�����N�^�[�����o�^����Ă���ꍇ�́A����̃}�b�v���g�p����
	if (itr == _allCharaAnimMap.end()) {
		for (auto it = motionList.begin(); it != motionList.end(); ++it) {
			ANIMATION_INFO info{};
			info.animIndex = MV1GetAnimIndex(modelHandle, it->first.c_str());
			info.loopTimes = it->second;
			_allCharaAnimMap[charaName][static_cast<int>(it - motionList.begin())] = info;
#ifdef _DEBUG
			if (info.animIndex == -1) {
				std::string message = "[" + it->first + "] �A�j���[�V������������܂���ł���";

				MessageBox(NULL, message.c_str(), "�G���[", MB_OK);
			}
#endif // _DEBUG
		}
	}
	_targetAnimMap = &_allCharaAnimMap[charaName];
	_modelHandle = modelHandle;
}
//----------------------------------------------------------------------
// @brief �A�j���[�V�����A�C�e����ǉ�����
// @param statusNo ���[�V�����̏��
// @return �Ȃ�
//----------------------------------------------------------------------
void AnimationComponent::AddAnimationItem()
{
	// ����statusNo�ɑΉ�����A�j���[�V������񂪑��݂��邩���ׂ�
	auto itr = (*_targetAnimMap).find((*_stateNum));
	// �A�j���[�V������񂪑��݂���ꍇ
	if (itr != (*_targetAnimMap).end())
	{
		AnimationItem* anim = new AnimationItem();

		ANIMATION_INFO info = itr->second;
		int attachIndex = MV1AttachAnim(_modelHandle, 0, info.animIndex, FALSE);
		float totalTime = MV1GetAttachAnimTotalTime(_modelHandle, attachIndex);
		int loopTimes = info.loopTimes;

		anim->Setup((*_stateNum), attachIndex, totalTime, loopTimes);
		_animContainer.push_back(anim);
		_latestAnimItem = anim;
	}
}
//----------------------------------------------------------------------
// @brief �A�j���[�V�����̍Đ�����
// @param statusNo ���[�V�����̏��
// @return �Ȃ�
//----------------------------------------------------------------------
void AnimationComponent::Process()
{
	// �Đ�����A�j���[�V�������ς�����ꍇ
	if (_playingAnimStateNum != (*_stateNum)) {
		// �A�^�b�`����Ă���A�j���[�V�����ɕ����Ԃ�ݒ肷��i���[�V�����u�����h�p�j
		for (auto itrItem = _animContainer.begin(); itrItem != _animContainer.end();)
		{
			// ���[�V������3�ȏ�u�����h���Ȃ����߂ɁA�Â��A�j���[�V�������폜����
			if ((*itrItem)->_stateNo != _playingAnimStateNum) {
				// �A�j���[�V�������f�^�b�`����
				MV1DetachAnim(_modelHandle, (*itrItem)->_attachIndex);
				// ���̃A�j���[�V�����A�C�e�����폜
				delete (*itrItem);
				itrItem = _animContainer.erase(itrItem);
				continue;
			}

			if ((*itrItem)->_closeTime == 0.0f) {
				// �����Ԃ�ݒ肷��
				(*itrItem)->_closeTotalTime = 6.0f;
				(*itrItem)->_closeTime = (*itrItem)->_closeTotalTime;
			}
			++itrItem;
		}

		// �A�j���[�V�����ԍ����X�V����
		_playingAnimStateNum = (*_stateNum);
		// �A�j���[�V�����A�C�e����ǉ�����
		AddAnimationItem();
	}

	// �Ō�ɒǉ����ꂽ�i�ŐV�́j�A�j���[�V�����A�C�e���̍Đ����Ԃ��擾����
	_playTime = _latestAnimItem->_playTime;

	// �A�j���[�V�����̍Đ����Ԃ�i�߂�
	for (auto itrItem = _animContainer.begin(); itrItem != _animContainer.end(); )
	{
		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(_modelHandle, (*itrItem)->_attachIndex, (*itrItem)->_playTime);

		/* �Đ����Ԃ̍X�V���� */
		// �����Ԃ��ݒ肳��Ă��Ȃ��ꍇ
		if ((*itrItem)->_closeTime == 0.0f) {
			// �Đ����Ԃ�i�߂�
			(*itrItem)->_playTime += 1.0f;

			// �A�j���[�V�����Đ��J�n���̃��[�V�����u�����h
			if((*itrItem)->_openTime < (*itrItem)->_openTotalTime){
				(*itrItem)->_openTime += 1.0f;
				// �u�����h����ύX����
				MV1SetAttachAnimBlendRate(_modelHandle, (*itrItem)->_attachIndex, (*itrItem)->_openTime / (*itrItem)->_openTotalTime);
			}
			
			// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
			if ((*itrItem)->_playTime > (*itrItem)->_totalTime) {
				// ���[�v�Đ�������ꍇ
				if ((*itrItem)->_loopCnt > 1 || (*itrItem)->_loopCnt == 0) {
					if ((*itrItem)->_loopCnt > 1) {
						(*itrItem)->_loopCnt--;
					}
					// �Đ����Ԃ�0�ɖ߂�
					(*itrItem)->_playTime = 0.0f;
				}
				// ���[�v�Đ������Ȃ��ꍇ
				else {
					(*itrItem)->_playTime = (*itrItem)->_totalTime;
				}
			}
		}
		else {
			// �A�j���[�V�����I�����̃��[�V�����u�����h

			// �����Ԃ����炷
			(*itrItem)->_closeTime -= 1.f;

			// �����Ԃ��I��������H
			if ((*itrItem)->_closeTime <= 0.f) {
				// �A�j���[�V�������f�^�b�`����
				MV1DetachAnim(_modelHandle, (*itrItem)->_attachIndex);
				// ���̃A�j���[�V�����A�C�e�����폜
				delete (*itrItem);
				itrItem = _animContainer.erase(itrItem);
				continue;
			}
			// �u�����h����ύX����
			MV1SetAttachAnimBlendRate(_modelHandle, (*itrItem)->_attachIndex, (*itrItem)->_closeTime / (*itrItem)->_closeTotalTime);
		}
		// ���̃A�j���[�V�����A�C�e����
		++itrItem;
	}
}
//----------------------------------------------------------------------
// @brief �f�o�b�O���̕`��
// @return �Ȃ�
//----------------------------------------------------------------------
void AnimationComponent::DrawDebugInfo()
{
	int y = 100;
	int line = 0;

	DrawBox(0, y, 300, y + 16 * 3, GetColor(128, 128, 128), TRUE);
	DrawFormatString(0, y + line * 16, COLOR_BLUE, "PlayTime : %3.2f", _playTime); line++;

	for (auto itr = _animContainer.begin(); itr != _animContainer.end(); ++itr)
	{
		DrawFormatString(0, y + line * 16, COLOR_BLUE, "�A�j���[�V�����ԍ� : %d", (*itr)->_stateNo);
		line++;
	}
}
