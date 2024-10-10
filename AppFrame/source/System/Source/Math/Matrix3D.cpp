//----------------------------------------------------------------------
// @filename Matrix3D.cpp
// @author: Fukuma Kyohei
// @explanation
// 3D��Ԃł̃}�g���b�N�X�������N���X
//----------------------------------------------------------------------
#include "../../Header/Math/Matrix3D.h"
#include "../../Header/Math/Vector3D.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
Matrix3D::Matrix3D()
{
	//�v�f��S��0�ɂ���
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_m[i][j] = 0;
		}
	}
}
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Matrix3D::~Matrix3D()
{
}
//----------------------------------------------------------------------
// @brief �s��̏�����
// @return ����
//----------------------------------------------------------------------
Matrix3D Matrix3D::Ident()
{
	Matrix3D temp;
	//�s��̏������A[0][0],[1][1],[2][2],[3][3]��1�ɂ��Ă���
	for (int i = 0; i < 4; i++)
	{
		temp._m[i][i] = 1;
	}
	return temp;
}
//----------------------------------------------------------------------
// @brief ���Z
// @param right:���Z����}�g���b�N�X
// @return ���Z����
//----------------------------------------------------------------------
Matrix3D Matrix3D::operator+=(const Matrix3D& right)
{
	//�ꎞ�I�ȍs��̍쐬
	Matrix3D temp;
	//�e�s�A�e��ŉ��Z���s��
	//0�s
	temp._m[0][0] = _m[0][0] + right._m[0][0];
	temp._m[0][1] = _m[0][1] + right._m[0][1];
	temp._m[0][2] = _m[0][2] + right._m[0][2];
	temp._m[0][3] = _m[0][3] + right._m[0][3];
	//1�s
	temp._m[1][0] = _m[1][0] + right._m[1][0];
	temp._m[1][1] = _m[1][1] + right._m[1][1];
	temp._m[1][2] = _m[1][2] + right._m[1][2];
	temp._m[1][3] = _m[1][3] + right._m[1][3];
	//2�s
	temp._m[2][0] = _m[2][0] + right._m[2][0];
	temp._m[2][1] = _m[2][1] + right._m[2][1];
	temp._m[2][2] = _m[2][2] + right._m[2][2];
	temp._m[2][3] = _m[2][3] + right._m[2][3];
	//3�s
	temp._m[3][0] = _m[3][0] + right._m[3][0];
	temp._m[3][1] = _m[3][1] + right._m[3][1];
	temp._m[3][2] = _m[3][2] + right._m[3][2];
	temp._m[3][3] = _m[3][3] + right._m[3][3];
	return temp;
}
//----------------------------------------------------------------------
// @brief ���Z
// @param right:���Z����}�g���b�N�X
// @return ���Z����
//----------------------------------------------------------------------
Matrix3D Matrix3D::operator*=(const Matrix3D& right)
{
	Matrix3D temp;
	temp._m[0][0] = _m[0][0] * right._m[0][0] + _m[0][1] * right._m[1][0] + _m[0][2] * right._m[2][0] + _m[0][3] * right._m[3][0];
	temp._m[0][1] = _m[0][0] * right._m[0][1] + _m[0][1] * right._m[1][1] + _m[0][2] * right._m[2][1] + _m[0][3] * right._m[3][1];
	temp._m[0][2] = _m[0][0] * right._m[0][2] + _m[0][1] * right._m[1][2] + _m[0][2] * right._m[2][2] + _m[0][3] * right._m[3][2];
	temp._m[0][3] = _m[0][0] * right._m[0][3] + _m[0][1] * right._m[1][3] + _m[0][2] * right._m[2][3] + _m[0][3] * right._m[3][3];

	temp._m[1][0] = _m[1][0] * right._m[0][0] + _m[1][1] * right._m[1][0] + _m[1][2] * right._m[2][0] + _m[1][3] * right._m[3][0];
	temp._m[1][1] = _m[1][0] * right._m[0][1] + _m[1][1] * right._m[1][1] + _m[1][2] * right._m[2][1] + _m[1][3] * right._m[3][1];
	temp._m[1][2] = _m[1][0] * right._m[0][2] + _m[1][1] * right._m[1][2] + _m[1][2] * right._m[2][2] + _m[1][3] * right._m[3][2];
	temp._m[1][3] = _m[1][0] * right._m[0][3] + _m[1][1] * right._m[1][3] + _m[1][2] * right._m[2][3] + _m[1][3] * right._m[3][3];

	temp._m[2][0] = _m[2][0] * right._m[0][0] + _m[2][1] * right._m[1][0] + _m[2][2] * right._m[2][0] + _m[2][3] * right._m[3][0];
	temp._m[2][1] = _m[2][0] * right._m[0][1] + _m[2][1] * right._m[1][1] + _m[2][2] * right._m[2][1] + _m[2][3] * right._m[3][1];
	temp._m[2][2] = _m[2][0] * right._m[0][2] + _m[2][1] * right._m[1][2] + _m[2][2] * right._m[2][2] + _m[2][3] * right._m[3][2];
	temp._m[2][3] = _m[2][0] * right._m[0][3] + _m[2][1] * right._m[1][3] + _m[2][2] * right._m[2][3] + _m[2][3] * right._m[3][3];

	temp._m[3][0] = _m[3][0] * right._m[0][0] + _m[3][1] * right._m[1][0] + _m[3][2] * right._m[2][0] + _m[3][3] * right._m[3][0];
	temp._m[3][1] = _m[3][0] * right._m[0][1] + _m[3][1] * right._m[1][1] + _m[3][2] * right._m[2][1] + _m[3][3] * right._m[3][1];
	temp._m[3][2] = _m[3][0] * right._m[0][2] + _m[3][1] * right._m[1][2] + _m[3][2] * right._m[2][2] + _m[3][3] * right._m[3][2];
	temp._m[3][3] = _m[3][0] * right._m[0][3] + _m[3][1] * right._m[1][3] + _m[3][2] * right._m[2][3] + _m[3][3] * right._m[3][3];
	return temp;
}
//----------------------------------------------------------------------
// @brief �����I�y���[�^
// @param right:��r����}�g���b�N�X
// @return ��r����
//----------------------------------------------------------------------
bool Matrix3D::operator==(const Matrix3D& right)
{
	if (_m[0][0] == right._m[0][0] && _m[0][1] == right._m[0][1] && _m[0][2] == right._m[0][2] && _m[0][3] == right._m[0][3]
		&& _m[1][0] == right._m[1][0] && _m[1][1] == right._m[1][1] && _m[1][2] == right._m[1][2] && _m[0][3] == right._m[1][3]
		&& _m[2][0] == right._m[2][0] && _m[2][1] == right._m[2][1] && _m[2][2] == right._m[2][2] && _m[0][3] == right._m[2][3]
		&& _m[3][0] == right._m[3][0] && _m[3][1] == right._m[3][1] && _m[3][2] == right._m[3][2] && _m[0][3] == right._m[3][3])
	{
		return true;
	}
	return false;
}

bool Matrix3D::operator!=(const Matrix3D& right)
{
	return !(*this==right);
}
//----------------------------------------------------------------------
// @brief �s�����I�y���[�^
// @param right:��r����}�g���b�N�X
// @return ��r����
//----------------------------------------------------------------------
Matrix3D& Matrix3D::operator=(const MATRIX& right)
{
	
	_m[0][0] = right.m[0][0];
	_m[0][1] = right.m[0][1];
	_m[0][2] = right.m[0][2];
	_m[0][3] = right.m[0][3];

	_m[1][0] = right.m[1][0];
	_m[1][1] = right.m[1][1];
	_m[1][2] = right.m[1][2];
	_m[1][3] = right.m[1][3];

	_m[2][0] = right.m[2][0];
	_m[2][1] = right.m[2][1];
	_m[2][2] = right.m[2][2];
	_m[2][3] = right.m[2][3];

	_m[3][0] = right.m[3][0];
	_m[3][1] = right.m[3][1];
	_m[3][2] = right.m[3][2];
	_m[3][3] = right.m[3][3];
	return (*this);
}
//----------------------------------------------------------------------
// @brief DxLib�p�}�g���b�N�X�ϊ�
// @return �ϊ�����
//----------------------------------------------------------------------
MATRIX Matrix3D::dxl()
{
	MATRIX m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m[i][j]=static_cast<float>(_m[i][j]);
		}
	}
	return m;
}
//----------------------------------------------------------------------
// @brief �}�g���b�N�X�̃X�P�[�����O
// @param m:�X�P�[�����O����}�g���b�N�X
// @param value:�X�P�[���̒l
// @return �X�P�[�����O����
//----------------------------------------------------------------------
Matrix3D Matrix3D::MScale(Matrix3D m, float value)
{
	Matrix3D temp;
	temp._m[0][0] = m._m[0][0] * value;
	temp._m[0][1] = m._m[0][1] * value;
	temp._m[0][2] = m._m[0][2] * value;
	temp._m[0][3] = m._m[0][3] * value;

	temp._m[1][0] = m._m[1][0] * value;
	temp._m[1][1] = m._m[1][1] * value;
	temp._m[1][2] = m._m[1][2] * value;
	temp._m[1][3] = m._m[1][3] * value;

	temp._m[2][0] = m._m[2][0] * value;
	temp._m[2][1] = m._m[2][1] * value;
	temp._m[2][2] = m._m[2][2] * value;
	temp._m[2][3] = m._m[2][3] * value;

	temp._m[3][0] = m._m[3][0] * value;
	temp._m[3][1] = m._m[3][1] * value;
	temp._m[3][2] = m._m[3][2] * value;
	temp._m[3][3] = m._m[3][3] * value;
	return temp;
}
//----------------------------------------------------------------------
// @brief �X�P�[�����O�����}�g���b�N�X�擾
// @param vec:�}�g���b�N�X�̃X�P�[�����O�l
// @return �X�P�[�����O�����}�g���b�N�X
//----------------------------------------------------------------------
Matrix3D Matrix3D::MGetScale(class Vector3D& vec)
{
	Matrix3D temp;
	temp._m[0][0] = vec.x;
	temp._m[1][1] = vec.y;
	temp._m[2][2] = vec.z;
	temp._m[3][3] = 1.0f;
	return temp;
}
//----------------------------------------------------------------------
// @brief ���s�ړ��}�g���b�N�X�擾
// @param vec:�}�g���b�N�X�̕��s�ړ��l
// @return ���s�ړ������}�g���b�N�X�擾
//----------------------------------------------------------------------
Matrix3D Matrix3D::MGetTranslate(class Vector3D& vec)
{
	Matrix3D temp;
	temp._m[3][0] = vec.x;
	temp._m[3][1] = vec.y;
	temp._m[3][2] = vec.z;
	temp._m[3][3] = 1.0f;
	return temp;
}
//----------------------------------------------------------------------
// @brief ���Z
// @param left: �}�g���b�N�X1
// @param right: �}�g���b�N�X2
// @return ���Z����
//----------------------------------------------------------------------
const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(left) += right;
}
//----------------------------------------------------------------------
// @brief ��Z
// @param left: �}�g���b�N�X1
// @param right: �}�g���b�N�X2
// @return ��Z����
//----------------------------------------------------------------------
const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(left) *= right;
}
//----------------------------------------------------------------------
// @brief �w��l�ł�X���̉�]�s��擾
// @param value:��]�l(rad)
// @return ��]�s��擾
//----------------------------------------------------------------------
Matrix3D Matrix3D::MGetRotX(float value)
{
	float _sin, _cos;
	_sin = sinf(value);
	_cos = cosf(value);
	Matrix3D temp;
	temp._m[1][1] = _cos;
	temp._m[1][2] = _sin;
	temp._m[2][1] = -_sin;
	temp._m[2][2] = _cos;
	return temp;
}
//----------------------------------------------------------------------
// @brief �w��l�ł�Y���̉�]�s��擾
// @param value:��]�l(rad)
// @return ��]�s��擾
//----------------------------------------------------------------------
Matrix3D Matrix3D::MGetRotY(float value)
{
	float _sin, _cos;
	_sin = sinf(value);
	_cos = cosf(value);
	Matrix3D temp;
	temp._m[0][0] = _cos;
	temp._m[0][2] = -_sin;
	temp._m[2][0] = _sin;
	temp._m[2][2] = _cos;
	return temp;
}
//----------------------------------------------------------------------
// @brief �w��l�ł�Z���̉�]�s��擾
// @param value:��]�l(rad)
// @return ��]�s��擾
//----------------------------------------------------------------------
Matrix3D Matrix3D::MGetRotZ(float value)
{
	float _sin, _cos;
	_sin = sinf(value);
	_cos = cosf(value);
	Matrix3D temp;
	temp._m[0][0] = _cos;
	temp._m[0][1] = _sin;
	temp._m[1][0] = -_sin;
	temp._m[1][1] = _cos;
	return temp;
}

