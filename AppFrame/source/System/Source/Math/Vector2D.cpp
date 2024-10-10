//----------------------------------------------------------------------
// @filename Vector2D.cpp
// @author: Osaki Nagomi
// @explanation
// 2�����x�N�g���N���X
//----------------------------------------------------------------------
#include "../../Header/Math/Vector2D.h"
#include <math.h>

//----------------------------------------------------------------------
// @brief ���Z
// @param right: ���Z����x�N�g��
// @return ���Z����
//----------------------------------------------------------------------
Vector2D Vector2D::operator+=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x + right.x;
	result.y = y + right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief ���Z
// @param right: ���Z����x�N�g��
// @return ���Z����
//----------------------------------------------------------------------
Vector2D Vector2D::operator-=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x - right.x;
	result.y = y - right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief ��Z 
// @param right: ��Z����x�N�g��
// @return ��Z����
//----------------------------------------------------------------------
Vector2D Vector2D::operator*=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x * right.x;
	result.y = y * right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief ��Z �X�J���[�{
// @param right: ��Z�������
// @return ��Z����
//----------------------------------------------------------------------
Vector2D Vector2D::operator*=(const float& right)
{
	Vector2D result = Vector2D();
	result.x = x * right;
	result.y = y * right;
	return result;
}

//----------------------------------------------------------------------
// @brief ���Z
// @param right: ���Z����x�N�g��
// @return ���Z����
//----------------------------------------------------------------------
Vector2D Vector2D::operator/=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x / right.x;
	result.y = y / right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief ���Z
// @param right: ���Z�������
// @return ���Z����
//----------------------------------------------------------------------
Vector2D Vector2D::operator/=(const float& right)
{
	Vector2D result = Vector2D();
	result.x = x / right;
	result.y = y / right;
	return result;
}

//----------------------------------------------------------------------
// @brief ����
// @param v: ���ς����߂�x�N�g��
// @return ���ς̒l
//----------------------------------------------------------------------
float Vector2D::Dot(const Vector2D& v) const {
	return Dot((*this), v);
};

//----------------------------------------------------------------------
// @brief �O��
// @param v: �O�ς����߂�x�N�g��
// @return �O�ς̒l
//----------------------------------------------------------------------
float Vector2D::Cross(const Vector2D& v) const {
	return Cross((*this), v);
};

//----------------------------------------------------------------------
// @brief ����
// @return ����
//----------------------------------------------------------------------
float Vector2D::Len() const {
	return sqrtf(x * x + y * y);
};

//----------------------------------------------------------------------
// @brief ����
// @param left: �x�N�g��1
// @param right: �x�N�g��2
// @return ���ς̒l
//----------------------------------------------------------------------
float Vector2D::Dot(const Vector2D& left, const Vector2D& right){
	return left.x * right.x + left.y * right.y;
};

//----------------------------------------------------------------------
// @brief �O��
// @param left: �x�N�g��1
// @param right: �x�N�g��2
// @return �O�ς̒l
//----------------------------------------------------------------------
float Vector2D::Cross(const Vector2D& left, const Vector2D& right) {
		return left.x * right.y - left.y * right.x;
};

//----------------------------------------------------------------------
// @brief ���Z
// @param left: �x�N�g��1
// @param right: �x�N�g��2
// @return ���Z����
//----------------------------------------------------------------------
const Vector2D operator+(const Vector2D& left, const Vector2D& right) { return Vector2D(left) += right; }

//----------------------------------------------------------------------
// @brief ���Z
// @param left: �x�N�g��1
// @param right: �x�N�g��2
// @return ���Z����
//----------------------------------------------------------------------
const Vector2D operator-(const Vector2D& left, const Vector2D& right) { return Vector2D(left) -= right; }

//----------------------------------------------------------------------
// @brief ��Z
// @param left: �x�N�g��1
// @param right: �x�N�g��2
// @return ��Z����
//----------------------------------------------------------------------
const Vector2D operator*(const Vector2D& left, const Vector2D& right) { return Vector2D(left) *= right; }