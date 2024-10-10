//----------------------------------------------------------------------
// @filename Matrix3D.h
// @author: Fukuma Kyohei
// @explanation
// �s��v�Z���s���N���X
//----------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include <math.h>
//3D�ɂ�����s��֘A�̃N���X
class Matrix3D
{
public:
	Matrix3D();
	~Matrix3D();
	Matrix3D Ident();
	//�I�y���[�^�I�[�o�[���[�h
	Matrix3D  operator+=(const Matrix3D& right);
	Matrix3D  operator*=(const Matrix3D& right);
	bool      operator==(const Matrix3D& right);
	bool      operator!=(const Matrix3D& right);
	//DX���C�u������MATRIX���g����悤��
	Matrix3D& operator= (const MATRIX& right);
	MATRIX  dxl();
	//X��
	static Matrix3D  MGetRotX(float d);
	//y��
	static Matrix3D  MGetRotY(float d);
	//z��
	static Matrix3D  MGetRotZ(float d);
	//matrix�v�Z����
	//�X�P�[�����O
	Matrix3D  MScale(Matrix3D m, float d);
	//�x�N�g���ɂ��g��k��
	Matrix3D  MGetScale(class Vector3D& vec);
	//�x�N�g���ɂ�镽�s�ړ�
	Matrix3D  MGetTranslate(class Vector3D& vec);
	
public:
	float _m[4][4];
};
//�N���X�O�I�y���[�^�I�[�o�[���[�h
//���Z
const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right);
//��Z
const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right);
//��]�s��