//----------------------------------------------------------------------
// @filename Vector2D.h
// @author: Osaki Nagomi
// @explanation
// 2�����x�N�g���N���X
//----------------------------------------------------------------------
#pragma once

class Vector2D
{
public:
	Vector2D() { x = 0.0f; y = 0.0f; }
	Vector2D(float x, float y) { this->x = x; this->y = y; }
	~Vector2D() = default;

	float Dot(const Vector2D& v) const;	// ����
	float Cross(const Vector2D& v) const;	// �O��
	float Len() const;	// ����

	static float Dot(const Vector2D& left, const Vector2D& right);	// ����
	static float Cross(const Vector2D& left, const Vector2D& right);	// �O��

	// �l�����Z
	Vector2D operator+=(const Vector2D& right);	// ���Z
	Vector2D operator-=(const Vector2D& right);	// ���Z
	Vector2D operator*=(const Vector2D& right);	// ��Z�@�x�N�g�� �~ �x�N�g��
	Vector2D operator*=(const float& right);		// ��Z�@�x�N�g�� �~ �萔
	Vector2D operator/=(const Vector2D& right);	// ���Z�@�x�N�g�� �� �x�N�g��
	Vector2D operator/=(const float& right);		// ���Z�@�x�N�g�� �� �萔

public:
	float x, y;
};

const Vector2D operator+(const Vector2D& left, const Vector2D& right);		// ���Z	
const Vector2D operator-(const Vector2D& left, const Vector2D& right);		// ���Z	
const Vector2D operator*(const Vector2D& left, const Vector2D& right);		// ��Z�@


