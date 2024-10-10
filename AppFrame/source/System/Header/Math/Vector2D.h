//----------------------------------------------------------------------
// @filename Vector2D.h
// @author: Osaki Nagomi
// @explanation
// 2次元ベクトルクラス
//----------------------------------------------------------------------
#pragma once

class Vector2D
{
public:
	Vector2D() { x = 0.0f; y = 0.0f; }
	Vector2D(float x, float y) { this->x = x; this->y = y; }
	~Vector2D() = default;

	float Dot(const Vector2D& v) const;	// 内積
	float Cross(const Vector2D& v) const;	// 外積
	float Len() const;	// 長さ

	static float Dot(const Vector2D& left, const Vector2D& right);	// 内積
	static float Cross(const Vector2D& left, const Vector2D& right);	// 外積

	// 四則演算
	Vector2D operator+=(const Vector2D& right);	// 加算
	Vector2D operator-=(const Vector2D& right);	// 減算
	Vector2D operator*=(const Vector2D& right);	// 乗算　ベクトル × ベクトル
	Vector2D operator*=(const float& right);		// 乗算　ベクトル × 定数
	Vector2D operator/=(const Vector2D& right);	// 除算　ベクトル ÷ ベクトル
	Vector2D operator/=(const float& right);		// 除算　ベクトル ÷ 定数

public:
	float x, y;
};

const Vector2D operator+(const Vector2D& left, const Vector2D& right);		// 加算	
const Vector2D operator-(const Vector2D& left, const Vector2D& right);		// 減算	
const Vector2D operator*(const Vector2D& left, const Vector2D& right);		// 乗算　


