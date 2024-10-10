//----------------------------------------------------------------------
// @filename Quaternion.cpp
// @author: Saito Ko
// @explanation
// �N�H�[�^�j�I���̌v�Z���s���N���X
//----------------------------------------------------------------------
#include "../../Header/Math/Quaternion.h"
#include <math.h>
#include "../../../Application/UtilMacro.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Quaternion::Quaternion(){
	identity();
};

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param w ��]�p
// @param x ��]����x����
// @param y ��]����y����
// @param z ��]����z����
// @return �Ȃ�
//----------------------------------------------------------------------
Quaternion::Quaternion(float w, float x, float y, float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
};

//----------------------------------------------------------------------
// @brief X����]�̃N�H�[�^�j�I����ݒ�
// @param theta ��]�p
// @return �Ȃ�
//----------------------------------------------------------------------
void	Quaternion::SetToRotateX(float theta){
	// 	���p�ɕϊ�����
	float thetaOver2 = theta * 0.5f; 

	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
};

//----------------------------------------------------------------------
// @brief Y����]�̃N�H�[�^�j�I����ݒ�
// @param theta ��]�p
// @return �Ȃ�
//----------------------------------------------------------------------
void	Quaternion::SetToRotateY(float theta){
	// 	���p�ɕϊ�����
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
};

//----------------------------------------------------------------------
// @brief Z����]�̃N�H�[�^�j�I����ݒ�
// @param theta ��]�p
// @return �Ȃ�
//----------------------------------------------------------------------
void	Quaternion::SetToRotateZ(float theta){
	// 	���p�ɕϊ�����
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
};

//----------------------------------------------------------------------
// @brief �}�g���b�N�X����N�H�[�^�j�I����ݒ�
// @param matrix �}�g���b�N�X
// @return �Ȃ�
//----------------------------------------------------------------------
void Quaternion::SetToMatrix(MATRIX& matrix){
	float trace = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2];
		float w, x, y, z;

		if (trace > 0) {
			float s = 0.5f / std::sqrtf(trace + 1.0f);
			w = 0.25f / s;
			x = (matrix.m[2][1] - matrix.m[1][2]) * s;
			y = (matrix.m[0][2] - matrix.m[2][0]) * s;
			z = (matrix.m[1][0] - matrix.m[0][1]) * s;
		}
		else {
			if (matrix.m[0][0] > matrix.m[1][1] && matrix.m[0][0] > matrix.m[2][2]) {
				float s = 2.0f * std::sqrtf(1.0f + matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2]);
				w = (matrix.m[2][1] - matrix.m[1][2]) / s;
				x = 0.25f * s;
				y = (matrix.m[0][1] + matrix.m[1][0]) / s;
				z = (matrix.m[0][2] + matrix.m[2][0]) / s;
			}
			else if (matrix.m[1][1] > matrix.m[2][2]) {
				float s = 2.0f * std::sqrtf(1.0f + matrix.m[1][1] - matrix.m[0][0] - matrix.m[2][0]);
				w = (matrix.m[0][2] - matrix.m[2][0]) / s;
				x = (matrix.m[0][1] + matrix.m[1][0]) / s;
				y = 0.25f * s;
				z = (matrix.m[1][2] + matrix.m[2][1]) / s;
			}
			else {
				float s = 2.0f * std::sqrtf(1.0f + matrix.m[2][2] - matrix.m[0][0] - matrix.m[1][1]);
				w = (matrix.m[1][0] - matrix.m[0][1]) / s;
				x = (matrix.m[0][2] + matrix.m[2][0]) / s;
				y = (matrix.m[1][2] + matrix.m[2][1]) / s;
				z = 0.25f * s;
			}
		}

		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
}

//----------------------------------------------------------------------
// @brief X����]�̃N�H�[�^�j�I���𐶐�
// @param theta ��]�p
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Quaternion::CreateRotateX(float theta){
	Quaternion q;
	q.SetToRotateX(theta);
	return q;
};

//----------------------------------------------------------------------
// @brief Y����]�̃N�H�[�^�j�I���𐶐�
// @param theta ��]�p
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Quaternion::CreateRotateY(float theta){
	Quaternion q;
	q.SetToRotateY(theta);
	return q;
};

//----------------------------------------------------------------------
// @brief Z����]�̃N�H�[�^�j�I���𐶐�
// @param theta ��]�p
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Quaternion::CreateRotateZ(float theta){
	Quaternion q;
	q.SetToRotateZ(theta);
	return q;
};

//----------------------------------------------------------------------
// @brief ����]�̃N�H�[�^�j�I����ݒ�
// @param axis ��]��
// @param theta ��]�p
// @return �Ȃ�
//----------------------------------------------------------------------
void	Quaternion::SetToRotateAxis(const Vector3D& axis, float theta){
	// ��]�������K������Ă��Ȃ�������G���[
	if(fabs(axis.Len() - 1.0f) < 0.01f) {
		MessageBox(NULL, "���K������Ă��Ȃ��ł�", "", MB_OK);
		return ;
	};

	// 	���p�ɕϊ�����
	float	thetaOver2 = theta * .5f;
	// 	sin�l���Z�o
	float	sinThetaOver2 = sin(thetaOver2);

	w = cos(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;
};

void	Quaternion::Normalize(){
	// �������Z�o
	float len = sqrt(w * w + x * x + y * y + z * z);

	// ������-��������G���[
	if (len < 0.0f) {
		MessageBox(NULL, "�������|�ł�", "", MB_OK);
		return ;
	};


	float	tmp = 1.0f / len;
	w *= tmp;
	x *= tmp;
	y *= tmp;
	z *= tmp;

};

//----------------------------------------------------------------------
// @brief ��]�p���擾
// @return ��]�p
//----------------------------------------------------------------------
float	Quaternion::GetToRotationAngle() const {
	// w = cos(�� / 2)�Ȃ̂ŁB
	return std::acos(w) * 2.0f;
};

//----------------------------------------------------------------------
// @brief ��]�����擾
// @return ��]��
//----------------------------------------------------------------------
Vector3D	Quaternion::GetToRotationAxis() const {
	// sin(�� / 2) / |v| = sin(�� / 2)
	// sin^2(x) + cos^2(x) = 1���
	float sinThetaOver2 = sqrt(1.0f - w * w);
	float tmp = 1.0f / sinThetaOver2;
	return Vector3D(x * tmp, y * tmp, z * tmp);
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̓��ς��擾
// @param q �N�H�[�^�j�I��
// @return ����
//----------------------------------------------------------------------
float Quaternion::Dot(const Quaternion& q){
	float result = ::Dot(*this, q);
	return result;
};

//----------------------------------------------------------------------
// @brief �I�u�W�F�N�g��Ԃ��犵����Ԃɕϊ�
// @param orientation �I�C���[�p
// @return �Ȃ�
//----------------------------------------------------------------------
void	Quaternion::SetRotateObjectToInertial(const Vector3D& orientation){
	auto SinCos = [](float* s, float* c, float theta) {
		*s = sin(theta);
		*c = cos(theta);
	};

	// �I�u�W�F�N�g��Ԃ��犵����Ԃɕϊ�
	// ���p�̃T�C���ƃR�T�C�����v�Z
	//�������@�w�f�B���O�E�s�b�`�E�o���N
	float	sp, sb, sh;
	float	cp, cb, ch;
	SinCos(&sp, &cp, orientation.x * 0.5f);
	SinCos(&sh, &ch, orientation.y * 0.5f);
	SinCos(&sb, &cb, orientation.z * 0.5f);

	w = ch * cp * cb + sh * sp * sb;
	x = ch * sp * cb + sh * cp * sb;
	y = -ch * sp * sb + sh * cp * cb;
	z = -sh * sp * cb + ch * cp * sb;
};

//----------------------------------------------------------------------
// @brief ������Ԃ���I�u�W�F�N�g��Ԃɕϊ�
// @param orientation �I�C���[�p
// @return �Ȃ�
//----------------------------------------------------------------------
void	Quaternion::SetRotateInertialToObject(const Vector3D& orientation){
	auto SinCos = [](float* s, float* c, float theta) {
		*s = sin(theta);
		*c = cos(theta);
	};

	// ������Ԃ���I�u�W�F�N�g��Ԃɕϊ�
	// ���p�̃T�C���ƃR�T�C�����v�Z

	float	sp, sb, sh;
	float	cp, cb, ch;
	SinCos(&sp, &cp, orientation.x * 0.5f);
	SinCos(&sh, &ch, orientation.y * 0.5f);
	SinCos(&sb, &cb, orientation.z * 0.5f);

	w = ch * cp * cb + sh * sp * sb;
	x = -ch * sp * cb - sh * cp * sb;
	y = ch * sp * sb - sh * cb * cp;
	z = sh * sp * cb - ch * cp * sb;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̊|���Z
// @param q �N�H�[�^�j�I��
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Quaternion::operator *(const Quaternion& q)  const {
	Quaternion tmp;

	tmp.w = w * q.w - x * q.x - y * q.y - z * q.z;
	tmp.x =  w * q.x + x * q.w + y * q.z - z * q.y;
	tmp.y =  w * q.y + y * q.w + z * q.x - x * q.z;
	tmp.z =  w * q.z + z * q.w + x * q.y - y * q.x;

	return tmp;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̊|���Z
// @param q �N�H�[�^�j�I��
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion& Quaternion::operator *=(const Quaternion& q){
	*this = *this * q;
	return *this;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I����z-y-x�n�I�C���[�p�ɕϊ�
// @return �I�C���[�p
//----------------------------------------------------------------------
Vector3D Quaternion::byEuler() {
	// �N�H�[�^�j�I����z-y-x�n�I�C���[�p�ɕϊ�
	float roll, pitch, yaw;
	float sin, cos;

	// roll X����]
	sin = 2 * (w * x + y * z);//32
	cos = 1 - 2 * (x * x + y * y);//33
	roll = atan2(sin, cos);

	// pitch Y����]
	sin = sqrt(1 + 2 * (w * y - x * z));//31
	cos = sqrt(1 - 2 * (w * y - x * z));//31
	pitch = 2 * atan2(sin, cos) - PI / 2;

	// yaw Z����]
	sin = 2 * (w * z + x * y);//21
	cos = 1 - 2 * (y * y + z * z);//11
	yaw = atan2(sin, cos);

	return Vector3D(roll, pitch, yaw);
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I����Dxlib�̃}�g���b�N�X�ɕϊ�
// @return �}�g���b�N�X
//----------------------------------------------------------------------
MATRIX Quaternion::byDxlibMatrix(){
	MATRIX m;
	m.m[0][0] = 1 - 2 * (y * y) - 2 * (z * z);
	m.m[0][1] = (2 * x * y) - (2 * z * w);
	m.m[0][2] = (2 * x * z) + (2 * y * w);
	m.m[0][3] = 0;

	m.m[1][0] = (2 * x * y) + (2 * z * w);
	m.m[1][1] = 1 - 2 * (x * x) - 2 * (z * z);
	m.m[1][2] = (2 * y * z) - (2 * x * w);
	m.m[1][3] = 0;

	m.m[2][0] = (2 * x * z) - (2 * y * w);
	m.m[2][1] = (2 * y * z) + (2 * x * w);
	m.m[2][2] = 1 - 2 * (x * x) - 2 * (y * y);
	m.m[2][3] = 0;

	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;

	return m;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̓��ς��擾
// @param left �N�H�[�^�j�I��
// @param right �N�H�[�^�j�I��
// @return ����
//----------------------------------------------------------------------
float Dot(const Quaternion& left, const Quaternion& right){
	return left.w * right.w + left.x * right.x + left.y * right.y + left.z * right.z;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̋������擾
// @param q �N�H�[�^�j�I��
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Conjugate(const Quaternion& q){
	Quaternion result;

	result.w = q.w;

	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̎w�����擾
// @param q �N�H�[�^�j�I��
// @param exponent �w��
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Pow(const Quaternion& q, float exponent){

	// �P���l�������`�F�b�N
	if (fabs(q.w) > 0.9999f) {
		return q;
	}

	// alpha = theta/2
	float	alpha = acos(q.w);

	// ���Ɏw�����|����
	float	newAlpha = alpha * exponent;

	Quaternion result;
	result.w = cos(newAlpha);
	float	mult = sin(newAlpha) / sin(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;

	return result;
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I����p���ăx�N�g������]
// @param v �x�N�g��
// @param q �N�H�[�^�j�I��
// @return ��]��̃x�N�g��
//----------------------------------------------------------------------
Vector3D RotateVectorByQuaternion(const Vector3D& v, const Quaternion& q) {
	// �N�H�[�^�j�I���ƃx�N�g���̐ρ@q*v*q^-1 ���
	Quaternion conjQuat = Conjugate(q);
	Quaternion vecQuat = Quaternion(0,v.x,v.y,v.z);
	Quaternion result = q * vecQuat * conjQuat;
	return Vector3D(result.x, result.y, result.z);
};

//----------------------------------------------------------------------
// @brief �N�H�[�^�j�I���̋��ʐ��`���
// @param p �N�H�[�^�j�I��
// @param q �N�H�[�^�j�I��
// @param t ����
// @return �N�H�[�^�j�I��
//----------------------------------------------------------------------
Quaternion Slerp(const Quaternion& p, const Quaternion& q, float t) {
	
	// ���Ԃ��������炻��ɍ��킹���[�_��Ԃ�
	if (t <= 0.0f) return p;
	if (t >= 1.0f) return q;

	// �����Ȃ�p����cos���v�Z

	float cosOmega = Dot(p, q);

	//���̓��ς̏ꍇ�Aq�𔽓]������
	// q �� -q �͓�����]��\�����A�قȂ鋅�ʐ��`��Ԃ𐶐�����ꍇ������
	//���m�Ȋp�x��p��t��]���邽�߂ɂ�q��-q�̂ǂ��炩��I������

	float qw = p.w;
	float qx = p.x;
	float qy = p.y;
	float qz = p.z;
	if (cosOmega < 0.0f) {
		qw *= -1;
		qx *= -1;
		qy *= -1;
		qz *= -1;
		cosOmega *= -1;
	}

	// �P�ʎl�����Ȃ̂œ��ς� <= 1.0f �ɂȂ�
	if(cosOmega < 1.1f){
		MessageBox(NULL, "���ς�1.0f�ȏ�ł�", "", MB_OK);
		return Quaternion();
	}

	// ��ԗp�̒[�����v�Z
	// �l�������قƂ�Ǔ��������ׂ�
	float k0, k1;
	if (cosOmega > 0.9999f) {

		//���ɋ߂��ꍇ�͐��`��Ԃ��s��
		k0 = 1.0f - t;
		k1 = t;
	}
	else {

		//�O�p�֐��̉��@�藝��p����sin���v�Z
		// sin^2(x) + cos^2(x) = 1
		float sinOmega = sqrt(1.0f - cosOmega * cosOmega);

		// sin��cos����p�x���v�Z
		float omega = atan2(sinOmega, cosOmega);

		//���Z��1��ōςނ悤�ɕ���̋t�����v�Z
		float oneOverSinOmega = 1.0f / sinOmega;

		// ��ԃp�����[�^���v�Z
		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t * omega) * oneOverSinOmega;
	}

	Quaternion result;
	result.x = k0 * p.x + k1 * qx;
	result.y = k0 * p.y + k1 * qy;
	result.z = k0 * p.z + k1 * qz;
	result.w = k0 * p.w + k1 * qw;

	return result;
};