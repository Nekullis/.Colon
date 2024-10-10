//----------------------------------------------------------------------
// @filename mymath.cpp
// @author: Saito Ko
// @explanation
// �v�Z���ȗ������邽�߂̊֐����܂Ƃ߂��N���X
//----------------------------------------------------------------------
#include "../../Header/Math/mymath.h"

//----------------------------------------------------------------------
// @brief �p�x��degree����radian�ɕϊ�
// @param deg: degree
// @return radian
//----------------------------------------------------------------------
float Math::DegToRad(float deg) {
	return deg * PI / 180.0f;		// �p�x��degree����radian�ɕϊ�
}

//----------------------------------------------------------------------
// @brief �p�x��radian����degree�ɕϊ�
// @param rad: radian
// @return degree
//----------------------------------------------------------------------
float Math::RadToDeg(float rad) {
	return rad * 180.0f / PI;		// �p�x��radian����degree�ɕϊ�
}

//----------------------------------------------------------------------
// @brief 2�̒l�̂����傫������Ԃ�
// @param left: ����
// @param right: �E��
// @return �傫�����̒l
//----------------------------------------------------------------------
float Math::Max(float left, float right) {
	return left > right ? left : right;
};

//----------------------------------------------------------------------
// @brief 2�̒l�̂�������������Ԃ�
// @param left: ����
// @param right: �E��
// @return ���������̒l
//----------------------------------------------------------------------
float Math::Min(float left, float right) {
	return left < right ? left : right;
};

//----------------------------------------------------------------------
// @brief n��min_n��max_n�̊ԂɎ��߂�
// @param min_n: �ŏ��l
// @param max_n: �ő�l
// @param n: �l
// @return min_n <= n <= max_n
float Math::Clamp(float min_n, float max_n, float n) {
	if (n <= min_n) { return min_n; }
	if (n >= max_n) { return max_n; }
	return n;
}

//
//���[�v���Ŏg���₷��
//----------------------------------------------------------------------
// @brief �}�g���b�N�X�����x�N�g���𐳋K������]������
// @param norm: ��]������x�N�g��
// @param rotation: ��]�p�x
// @param type: 0:x 1:y 2:z
// @return ��]��̃x�N�g��
//----------------------------------------------------------------------
Vector3D  Math::NormRotMatrix(Vector3D norm, float rotation, int type) {
	MATRIX conv_matrix = MGetIdent();
	Vector3D re_vec;
	switch (type) {
	case 0://x
		conv_matrix = MGetRotX(rotation);
		break;
	case 1://y
		conv_matrix = MGetRotY(rotation);
		break;
	case 2://z
		conv_matrix = MGetRotZ(rotation);
		break;
	default:
		return VGet(-1,0,0);
	}
	re_vec = VTransform(norm.toVECTOR(), conv_matrix);

	return re_vec.Normalize();
}

//----------------------------------------------------------------------
// @brief �s�񂩂�x�N�g�������o��
// @param matrix: �s��
// @param index: 0:x 1:y 2:z
// @return �x�N�g��
//----------------------------------------------------------------------
Vector3D Math::MatrixToVector(MATRIX matrix,int index) {
	return VGet(matrix.m[index][0], matrix.m[index][1], matrix.m[index][2]);
}

//----------------------------------------------------------------------
// @brief �������ɓ��e���ꂽ���������瓊�e���������Z�o
// @param Sep: ������
// @param e1: ������1
// @param e2: ������2
// @param e3: ������3
// @return ���e������
//----------------------------------------------------------------------
float  Math::LenSegOnSeparateAxis(Vector3D Sep, Vector3D e1, Vector3D e2, Vector3D e3 ) {

	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabsf(Sep.Dot(e1));
	float r2 = fabsf(Sep.Dot(e2));
	float r3 = 0.0f;
	if (e3.x != 0 || e3.y != 0 || e3.z != 0) {
		r3 = fabsf(Sep.Dot(e3));
	}
	return r1 + r2 + r3;
}

//----------------------------------------------------------------------
// @brief XYZ����]�s����쐬
// @param dir_x: X����]�p�x
// @param dir_y: Y����]�p�x
// @param dir_z: Z����]�p�x
// @return XYZ����]�s��
//----------------------------------------------------------------------
MATRIX Math::MMultXYZ(float dir_x, float dir_y, float dir_z) {
	MATRIX matrix;
	matrix = MGetRotX(dir_x);
	matrix = MMult(matrix, MGetRotY(dir_y));
	matrix = MMult(matrix, MGetRotZ(dir_z));

	return matrix;
};

//----------------------------------------------------------------------
// @brief XYZ����]�s����쐬���A�J�����r���{�[�h�s����|����
// @param dir_x: X����]�p�x
// @param dir_y: Y����]�p�x
// @param dir_z: Z����]�p�x
// @return XYZ����]�s��
//----------------------------------------------------------------------
MATRIX Math::MMultXYZToBillboard(float dir_x, float dir_y, float dir_z) {
	MATRIX matrix;
	matrix = MGetRotX(dir_x);
	matrix = MMult(matrix, MGetRotY(dir_y));
	matrix = MMult(matrix, MGetRotZ(dir_z));
	matrix = MMult(matrix, GetCameraBillboardMatrix());

	return matrix;
};

//----------------------------------------------------------------------
// @brief �s�񂩂琳�K���s�x�N�g�����쐬����
// @param vec_x: X���x�N�g��
// @param vec_y: Y���x�N�g��
// @param vec_z: Z���x�N�g��
// @param matrix: �s��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Math::SetMatrixToVector(Vector3D& vec_x, Vector3D& vec_y, Vector3D& vec_z, const MATRIX matrix) {
	vec_x = Vector3D(matrix.m[0][0], matrix.m[0][1], matrix.m[0][2]);
	vec_y = Vector3D(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
	vec_z = Vector3D(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
	return true;
}

//----------------------------------------------------------------------
// @brief �s�p���ǂ���
// @param p1: �x�N�g��1
// @param p2: �x�N�g��2
// @param p3: �x�N�g��3
// @return �s�p���ǂ���
//----------------------------------------------------------------------
bool Math::CheckAcuteAngle(Vector3D p1, Vector3D p2, Vector3D p3) {
	return (p1 - p2).Dot(p3 - p2) >= 0.0f;
}

//----------------------------------------------------------------------
// @brief ���s���ǂ���
// @param line_1_start: ����1�n�_
// @param line_1_end: ����1�I�_
// @param line_2_start: ����2�n�_
// @param line_2_end: ����2�I�_
// @return ���s���ǂ���
//----------------------------------------------------------------------
bool Math::CheckParallelRelation(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	Vector3D line_1 = line_1_end - line_1_start;
	Vector3D line_2 = line_2_end - line_2_start;
	float value = (line_1.Cross(line_2)).Len();
	float effective_range = 0.001f;
	return -effective_range <= value && value <= effective_range;
}

//----------------------------------------------------------------------
// @brief �������ǂ���
// @param line_1_start: ����1�n�_
// @param line_1_end: ����1�I�_
// @param line_2_start: ����2�n�_
// @param line_2_end: ����2�I�_
// @return �������ǂ���
//----------------------------------------------------------------------
bool Math::CheckVerticalRelation(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	Vector3D line_1 = line_1_end - line_1_start;
	Vector3D line_2 = line_2_end - line_2_start;
	float dot = line_1.Dot(line_2);
	float effective_range = 0.001f;
	return -effective_range <= dot && dot <= effective_range;
}

//----------------------------------------------------------------------
// @brief 2�̃x�N�g���̂Ȃ��p���v�Z����
// @param v1: �x�N�g��1
// @param v2: �x�N�g��2
// @return �p�x(radian)
//----------------------------------------------------------------------
float Math::CalcVectorAngle(Vector3D v1, Vector3D v2)
{
	float v1SquareSize = v1.Sqlen();
	float v2SquareSize = v2.Sqlen();
	if (v1SquareSize > 0.000000f && v2SquareSize > 0.000000f) {
		float cos = v1.Dot(v2) / (sqrtf(v1SquareSize) * sqrtf(v2SquareSize));
		return acosf(cos);
	}
	return 0.0f;
}

//----------------------------------------------------------------------
// @brief 3D���f��������vForward�̕��������ʂɂȂ�悤�ɉ�]������
// @param modelHandle: ���f���n���h��
// @param vForward: ���ʕ���
//----------------------------------------------------------------------
void Math::SetModelForward_RotationY(int modelHandle, Vector3D vForwad)
{
	Vector3D vBase = Vector3D(0.0f, 0.0f, -1.0f);
	vForwad.y = 0.0f;
	float angle = CalcVectorAngle(vBase, vForwad);
	angle *= vForwad.x < 0.0f ? 1.0f : -1.0f;
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));
}
