//----------------------------------------------------------------------
// @filename DrawGauge.h
// @author: Saito Ko 
// @explanation
// 2D�|���S����p���Ď��v�E�����v���ɃQ�[�W�𑝌������`�悷��N���X
//----------------------------------------------------------------------
#pragma once
#include"dxlib.h"
#include "../Math/mymath.h"
#include "../../../Application/Global.h"
#include "../Math/Vector3D.h"
#include "math.h"
class DrawGauge
{
public:
	DrawGauge(int image, int start_pos, float size, bool flag);
	DrawGauge(const char* name, int start_pos, float size, bool flag);
	~DrawGauge();
	bool Process(const Vector3D& pos, float parcent, float parcent_max);//���̒l�ƍő�̒l
	bool Process(const Vector3D& pos, float parcent, float parcent_max,float size);//�T�C�X�w���
	bool Draw() const;
	bool Draw(const int handle) const;

	static  const unsigned short _rightTraianglList[];//�E��]����n�߂��邽�߂̕`��̎��Ɏg���e���_�̃��X�g
	static  const unsigned short _leftTraianglList[];//����]����n�߂��邽�߂̕`��̎��Ɏg���e���_�̃��X�g
private:
	VERTEX2D vertex[10];//�`��̍ۂɎg���e���_
	int handle;//�Q�[�W�Ƃ��Ďg���摜�@�ǂݍ��݂̏ꍇ�̓��\�[�X�T�[�o�[���g�p
	int _startPosition;//�n�܂�ʒu�@�n�܂�ʒu�͂s�x�o�d
	int _transFlag;//���]�����邩
	float _size;//�\������摜�̔��a

	//�J�n�n�_���
	enum TYPE : int {
		right = 0,
		down,
		left,
		up
	};
};

