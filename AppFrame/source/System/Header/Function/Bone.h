//----------------------------------------------------------------------
// @filename Bone.h
// @author: Saito Ko
// @explanation
// �L�����N�^�[�̔��̖т⃊�{���Ȃǂ�bone�𕨗����Z�œ��������߂̃N���X
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include "dxlib.h"
#include "../Math/Vector3D.h"
#include "../../../File/JsonFile/JsonFile.h"

#define EULER 0
//#define RUNGE_KUTTA 1

class Bone
{
public:
	Bone(int* Model, std::vector<int> list, int size, std::string jsonFileName);
	~Bone();
	void SetMain(Vector3D* pos_list);//bone�̈ʒu���Z�b�g����
	void SetBoneDir(Vector3D world_dir_vec, Vector3D boon_pos, int target_frame, int parent_frame, MATRIX trans_mat, Vector3D dir_parent);;
	void SetDebugDraw() { _isTrans = 1 - _isTrans; };//;���߂��邩�ǂ���
	void DebugProcess(int transNum);//���߃t���O�������Ă�����bone�̃t���[���𓧉߁@���߂������t���[���ƘA�g���Ă��Ȃ������ꍇ�����Ŏw��
	void DebugRender();//���߂���Ă����ꍇ�f�o�b�O�\��

	static const Vector3D _orign;

	Vector3D* _orignPos;

	Vector3D GetOrignPos(int index) const { return _orignPos[index]; }//�����n�_�̍��W�𓾂�
private:
	int* _model;
	int _listSize;
	Vector3D* _vecDirList;//�������_�ł̃{�[�����猩��e�̕���
	MATRIX* _transMatrixList;//���W�ϊ��s��̃��X�g
	std::vector<int> _frameList;//�t���[���̔ԍ����X�g

	//�f�o�b�O�\��
	bool _isTrans;//�\�����邩���Ȃ���
	bool _oldIsTrans;

	// �� �������牺�͕������Z�Ŏg���ϐ���֐�
public:
	void SetGravity(std::string end, std::string start);
	void UpdatePosAndAccelByEuler(float _elapsedTime);
	void UpdatePosAndAccelByRungeKutta(float _elapsedTime);
	Vector3D ForceWorksToMassPoint(int i, Vector3D* posList, Vector3D* accelList); //���_�ɓ����͂��v�Z F=ma
	bool Process();

	void PositionReset();

	Vector3D* _massPosList; // ���_�̍��W���X�g
	Vector3D* _massAccelList; // ���_�̑��x���X�g

private:

	//����͔��̖т����Ȃ̂Œ萔�錾���Ă��邪�ق��̂Ɏg���Ƃ���
	//�ϐ��Ƃ��Đ錾���d�͂Ȃǂ̒l���N���X�����Ƃ��̈����Ƃ��ē��͂���Ƃł���
	//�����������̂ŕʃN���X�ō�����ق����ǂ����������H
	float* _massWeight;//���_�̏d��
	float* _viscousResistance;//�S����R
	float* _gravity; //�d��
	float* _spring; //�΂˒萔
	static const float _processInterval; //�����̍ו����̊Ԋu

	float* _naturalCorrectionFactor; //���̖т̎��R�̂̒������o���Ƃ��Ɏg�p����␳�W��
	Vector3D _gravityDir;//�d�͂̕��� 

	int _massPointSize; //���_��
	std::vector<float> _springList; // �΂˒萔�̃��X�g
	std::vector<float> _naturalList; // �΂˂̒����̃��X�g
};

