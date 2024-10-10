//----------------------------------------------------------------------
// @filename MotionList.cpp
// @author: Morozumi Hiroya Saito Ko
// @explanation
// �e�L�����N�^�[�̃��[�V�������X�g���Ǘ�����N���X
// AnimationManager�N���X�y��FrameData�N���X�̏����������ŕK�v�ȏ����Ǘ�����
// "Data/MotionList/MotionList_�Z�Z.csv" ����A�e�L�����N�^�[�̃��[�V�����ꗗ��ǂݍ��ށi�����̕����ɂ̓L�����N�^�[��������j
//----------------------------------------------------------------------
#include "../../../Header/Component/Animation/MotionList.h"
#include "../../../../File/CFile/CFile.h"

std::map<CHARA_NAME, std::vector<MotionNamePair>> MotionList::_allCharaMotionList;

//--------------------------------------------------------
// @breif ���[�V�������X�g�̓ǂݍ���
// @param charaName: �L�����N�^�[��
// @param fileName: ���[�V�������X�g�̃t�@�C����
// @return  ����
//--------------------------------------------------------
void MotionList::Load(CHARA_NAME charaName, std::string fileName)
{
	 //���łɊY������L�����N�^�[�̃��[�V�������X�g�����݂���ꍇ�͓ǂݍ��܂Ȃ�
	auto itr = _allCharaMotionList.find(charaName);
	if (itr == _allCharaMotionList.end()) {
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

				MotionNamePair m = { motionName, loopTimes };
				_allCharaMotionList[charaName].push_back(m);
			}
		}
	}
}

//--------------------------------------------------------
// @breif ���[�V�������X�g�����ׂč폜����
// @return  ����
//--------------------------------------------------------
void MotionList::DeleteAll()
{
	_allCharaMotionList.clear();
}

//--------------------------------------------------------
// ��breif�w�肵���L�����N�^�[�̃��[�V�������X�g���擾����
// @param charaName: �L�����N�^�[��
// @return  ���[�V�������X�g
//--------------------------------------------------------
std::vector<MotionNamePair>* MotionList::GetMotionList(CHARA_NAME charaName)
{
	// �w�肵���L�����N�^�[�̃��[�V�������X�g�����݂���ꍇ
	auto itr = _allCharaMotionList.find(charaName);
	if (itr != _allCharaMotionList.end()) {
		return &itr->second;
	}
	// ���݂��Ȃ��ꍇ
	return nullptr;
}
