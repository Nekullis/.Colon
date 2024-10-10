//----------------------------------------------------------------------
// @filename Afterglow.h
// @author: Saito Ko
// @explanation
// �w�肵���t���[���̍��W��p���Ďc���𔭐�������N���X
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include "dxlib.h"
class Afterglow
{
public : 
	Afterglow(int model,int frameNum,float length,int handle,int animCountMax);
	~Afterglow();
	void Process();
	void Render();
	void SetUpdate(bool update) { IsUpdate = update; _oldPos = MV1GetFramePosition(_model, _frameNum);}// ���_���X�V���邩�ǂ�����ݒ肵���̈ʒu���擾
protected:
	void SetVertex();// ���_��ݒ肷��֐�

	int _handle; // �摜�n���h��
	int _model; // �t���[���̈ʒu���擾���邽�߂̃��f��
	int _frameNum; // �擾�������ʒu�̃t���[���ԍ�
	int _animCountMax; // �A�j���[�V�����̑��t���[����
	int _animCount; // �A�j���[�V�����̃J�E���g
	float _length; // ����
	VECTOR _oldPos; // �O��̈ʒu
	bool IsUpdate; // ���_���X�V���邩�ǂ���
	std::vector<unsigned short> _vertexIndex;// ���_�̃C���f�b�N�X�R���e�i
	std::vector<VERTEX3D> _vertex; // ���_�̃R���e�i
	int _subColor;

	bool IsStop;
};

