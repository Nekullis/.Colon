//----------------------------------------------------------------------
// @filename MotionList.h
// @author: Morozumi Hiroya Saito Ko
// @explanation
// �e�L�����N�^�[�̃��[�V�������X�g���Ǘ�����N���X
// AnimationManager�N���X�y��FrameData�N���X�̏����������ŕK�v�ȏ����Ǘ�����
// "Data/MotionList/MotionList_�Z�Z.csv" ����A�e�L�����N�^�[�̃��[�V�����ꗗ��ǂݍ��ށi�����̕����ɂ̓L�����N�^�[��������j
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include <map>

// ���[�V�������ƃ��[�v�񐔂̃y�A
typedef std::pair<std::string, int> MotionNamePair;
typedef std::string CHARA_NAME;

class MotionList
{
public:
	// ���[�V�������X�g�̓ǂݍ���
	// @param charaName: �L�����N�^�[��
	// @param fileName: ���[�V�������X�g�̃t�@�C����
	static void Load(CHARA_NAME charaName, std::string fileName);
	// ���[�V�������X�g�����ׂč폜����
	static void DeleteAll();
	// �w�肵���L�����N�^�[�̃��[�V�������X�g���擾����
	// @param charaName: �L�����N�^�[��
	static std::vector<MotionNamePair>* GetMotionList(CHARA_NAME charaName);
private:
	// �S�L�����N�^�[�̃��[�V�������X�g
	// @key: �L�����N�^�[��
	// @value: ���[�V�������X�g
	static std::map<CHARA_NAME, std::vector<MotionNamePair>> _allCharaMotionList;
};