//----------------------------------------------------------------------
// @filename FrameData.cpp
// @author: Morozumi Hiroya Saito Ko
// @explanation
// �L�����N�^�[�̃��[�V�������Ԃɂ���ď������s���N���X
// csv�t�@�C������f�[�^��ǂݍ��݁A�������s��
//----------------------------------------------------------------------

#include "../../../Header/Component/Animation/FrameData.h"
#include "../../../../File/CFile/CFile.h"

std::map<std::string, std::map<int, std::multimap<int, CommandParam>>>  FrameData::_kindFrameData;//�L�����N�^�[�̎�ޕʂɎ��f�[�^
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
FrameData::FrameData(){

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
FrameData::~FrameData() {
	_frameData.clear();
	_kindFrameData.clear();
};
//----------------------------------------------------------------------
// @brief �t���[���f�[�^�̓ǂݍ���
// @param kindName �L�����N�^�[�̎��
// @param frameData �ǂݍ��ރt���[���f�[�^�̃��X�g
// @return �����������ǂ���
//----------------------------------------------------------------------
bool FrameData::LoadData(const std::string& kindName,const std::vector<std::pair<int, std::string>>& frameData) {
	auto itr = _kindFrameData.find(kindName);
	if (itr == _kindFrameData.end()) {
		//�p�����[�^��ۑ����Ă������X�g���쐬
		for (auto it = frameData.begin(); it != frameData.end(); ++it) {
			// �t�@�C���p�X�̍쐬
			std::string filePath = "Data/FrameData/" + kindName + "/" + it->second;
			//�t�@�C���ǂݍ���
			CFile csvFile(filePath);
			//�t�@�C�����J�����ꍇ���s
			std::multimap<int, CommandParam> paramList;
			if (csvFile.Success()) {
				int c = 0;
				const char* p = (const char*)csvFile.Data();
				int size = csvFile.Size();
				int key = 0;
				CommandParam param;
				while (c < size) {
					c += GetDecNum(&p[c], &key);//�A�j���[�V�����t���[��������
					c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &param.first);//�R�}���h������
					c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.second);//�p�����[�^������
					c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����
					paramList.insert(std::make_pair(key, param));//���X�g�ɂ��ߍ���
				}
				//�I������̂Ŗ{���X�g�ɑ��
				_kindFrameData[kindName][it->first] = paramList;
			}
		}
	}
	_frameData = _kindFrameData[kindName];
	return true;
}
//----------------------------------------------------------------------
// @brief �t���[���f�[�^�̓ǂݍ���
// @param kindName �L�����N�^�[�̎��
// @param frameData �ǂݍ��ރt���[���f�[�^�̃��X�g
// @return �����������ǂ���
//----------------------------------------------------------------------
bool FrameData::LoadData(const std::string& kindName, const std::vector<MotionNamePair>& motionList)
{
	auto itr = _kindFrameData.find(kindName);
	if (itr == _kindFrameData.end()) {
		int i = 0;
		//�p�����[�^��ۑ����Ă������X�g���쐬
		for (auto it = motionList.begin(); it != motionList.end(); ++it) {
			// �t�@�C���p�X�̍쐬
			std::string filePath = "Data/FrameData/" + kindName + "/FD_" + it->first + ".csv";
			//�t�@�C���ǂݍ���
			CFile csvFile(filePath);
			//�t�@�C�����J�����ꍇ���s
			std::multimap<int, CommandParam> paramList;
			if (csvFile.Success()) {
				int c = 0;
				const char* p = (const char*)csvFile.Data();
				int size = csvFile.Size();
				int key = 0;
				CommandParam param;
				while (c < size) {
					c += GetDecNum(&p[c], &key);//�A�j���[�V�����t���[��������
					c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &param.first);//�R�}���h������
					c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.second);//�p�����[�^������
					c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����
					paramList.insert(std::make_pair(key, param));//���X�g�ɂ��ߍ���
				}
				//�I������̂Ŗ{���X�g�ɑ��
				_kindFrameData[kindName][i] = paramList;
				
			}
			i++;
		}
	}
	_frameData = _kindFrameData[kindName];
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @param state ���
// @param animTime �A�j���[�V��������
// @return ����
//----------------------------------------------------------------------
void FrameData::Process(int state, int animTime) {
	//�R���e�i�̏�����
	if (!_nextCommandList.empty()) {
		_nextCommandList.clear();
	}

	auto itr = _frameData[state].equal_range(animTime);
	for (auto& it = itr.first; it != itr.second ; ++it) {
		//�L�����ŗL�̏���
		_nextCommandList.push_back(it->second);
	}
};

