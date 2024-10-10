//----------------------------------------------------------------------
// @filename Vector2D.cpp
// @author: Osaki Nagomi
// @explanation
// 2次元ベクトルクラス
//----------------------------------------------------------------------
#include "../../Header/Math/Vector2D.h"
#include <math.h>

//----------------------------------------------------------------------
// @brief 加算
// @param right: 加算するベクトル
// @return 加算結果
//----------------------------------------------------------------------
Vector2D Vector2D::operator+=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x + right.x;
	result.y = y + right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief 減算
// @param right: 減算するベクトル
// @return 減算結果
//----------------------------------------------------------------------
Vector2D Vector2D::operator-=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x - right.x;
	result.y = y - right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief 乗算 
// @param right: 乗算するベクトル
// @return 乗算結果
//----------------------------------------------------------------------
Vector2D Vector2D::operator*=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x * right.x;
	result.y = y * right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief 乗算 スカラー倍
// @param right: 乗算する実数
// @return 乗算結果
//----------------------------------------------------------------------
Vector2D Vector2D::operator*=(const float& right)
{
	Vector2D result = Vector2D();
	result.x = x * right;
	result.y = y * right;
	return result;
}

//----------------------------------------------------------------------
// @brief 除算
// @param right: 除算するベクトル
// @return 除算結果
//----------------------------------------------------------------------
Vector2D Vector2D::operator/=(const Vector2D& right)
{
	Vector2D result = Vector2D();
	result.x = x / right.x;
	result.y = y / right.y;
	return result;
}

//----------------------------------------------------------------------
// @brief 除算
// @param right: 除算する実数
// @return 除算結果
//----------------------------------------------------------------------
Vector2D Vector2D::operator/=(const float& right)
{
	Vector2D result = Vector2D();
	result.x = x / right;
	result.y = y / right;
	return result;
}

//----------------------------------------------------------------------
// @brief 内積
// @param v: 内積を求めるベクトル
// @return 内積の値
//----------------------------------------------------------------------
float Vector2D::Dot(const Vector2D& v) const {
	return Dot((*this), v);
};

//----------------------------------------------------------------------
// @brief 外積
// @param v: 外積を求めるベクトル
// @return 外積の値
//----------------------------------------------------------------------
float Vector2D::Cross(const Vector2D& v) const {
	return Cross((*this), v);
};

//----------------------------------------------------------------------
// @brief 長さ
// @return 長さ
//----------------------------------------------------------------------
float Vector2D::Len() const {
	return sqrtf(x * x + y * y);
};

//----------------------------------------------------------------------
// @brief 内積
// @param left: ベクトル1
// @param right: ベクトル2
// @return 内積の値
//----------------------------------------------------------------------
float Vector2D::Dot(const Vector2D& left, const Vector2D& right){
	return left.x * right.x + left.y * right.y;
};

//----------------------------------------------------------------------
// @brief 外積
// @param left: ベクトル1
// @param right: ベクトル2
// @return 外積の値
//----------------------------------------------------------------------
float Vector2D::Cross(const Vector2D& left, const Vector2D& right) {
		return left.x * right.y - left.y * right.x;
};

//----------------------------------------------------------------------
// @brief 加算
// @param left: ベクトル1
// @param right: ベクトル2
// @return 加算結果
//----------------------------------------------------------------------
const Vector2D operator+(const Vector2D& left, const Vector2D& right) { return Vector2D(left) += right; }

//----------------------------------------------------------------------
// @brief 減算
// @param left: ベクトル1
// @param right: ベクトル2
// @return 減算結果
//----------------------------------------------------------------------
const Vector2D operator-(const Vector2D& left, const Vector2D& right) { return Vector2D(left) -= right; }

//----------------------------------------------------------------------
// @brief 乗算
// @param left: ベクトル1
// @param right: ベクトル2
// @return 乗算結果
//----------------------------------------------------------------------
const Vector2D operator*(const Vector2D& left, const Vector2D& right) { return Vector2D(left) *= right; }