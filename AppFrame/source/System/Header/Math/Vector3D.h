//----------------------------------------------------------------------
// @filename Vector2D.h
// @author: Saito Ko
// @explanation
// 3次元ベクトルクラス
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include <math.h>
#include "Matrix3D.h"
class Vector3D
{
public:
	float x, y, z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};

	Vector3D(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	};

	// DxLib の VECTOR 型 から Vector3D 型 へ変換する
	Vector3D(VECTOR vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	};

	void Set(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	void Set(VECTOR vec) {
		Set(vec.x, vec.y, vec.z);
	}

	inline Vector3D operator=(const VECTOR& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return (*this);
	}

	//和
	Vector3D operator+(const Vector3D& vec)const
	{
		Vector3D tmp;
		tmp.x = x + vec.x;
		tmp.y = y + vec.y;
		tmp.z = z + vec.z;
		return tmp;
	}

	//差
	Vector3D operator-(const Vector3D& vec)const
	{
		Vector3D tmp;
		tmp.x = x - vec.x;
		tmp.y = y - vec.y;
		tmp.z = z - vec.z;
		return tmp;
	}

	//内積
	float operator*(const Vector3D& vec)const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3D operator*(const Matrix3D& m){
		Vector3D temp;
		temp.x = this->x * m._m[0][0] + this->y * m._m[1][0] + this->z * m._m[2][0] + m._m[3][0];
		temp.y = this->x * m._m[0][1] + this->y * m._m[1][1] + this->z * m._m[2][1] + m._m[3][1];
		temp.z = this->x * m._m[0][2] + this->y * m._m[1][2] + this->z * m._m[2][2] + m._m[3][2];
		return temp;
	};

	float Dot(const Vector3D& left, const Vector3D right) const 
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	float Dot(const Vector3D& vec) const 
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	//外積
	Vector3D Cross(const Vector3D& left, const Vector3D& right)
	{
		Vector3D tmp;
		tmp.x = left.y * right.z - left.z * right.y;
		tmp.y = left.z * right.x - left.x * right.z;
		tmp.z = left.x * right.y - left.y * right.x;
		return tmp;
	};

	Vector3D Cross(const Vector3D& vec) const
	{
		Vector3D tmp;
		tmp.x = y * vec.z - z * vec.y;
		tmp.y = z * vec.x - x * vec.z;
		tmp.z = x * vec.y - y * vec.x;
		return tmp;
	};


	// +=
	Vector3D operator+=(const Vector3D& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return (*this);
	}

	// -=
	Vector3D operator-=(const Vector3D& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return (*this);
	}

	// *= スカラ－積
	Vector3D operator*=(const int scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return (*this);
	}

	Vector3D operator*=(const float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return (*this);
	}

	// /= スカラ－減算
	Vector3D operator/=(const int scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return (*this);
	}

	Vector3D operator/=(const float scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return (*this);
	}

	//ベクトルの長さ
	float Len() const
	{
		return sqrtf(x * x + y * y + z * z);
	};

	//ベクトルの長さ 2乗
	float Sqlen() const
	{
		return x * x + y * y + z * z;
	}

	// 二つのベクトル（始点と終点）からの長さを得る
	static float Sqlen(const Vector3D& start, const Vector3D& end)
	{
		float len = 0.0f;
		len += (start.x - end.x) * (start.x - end.x);
		len += (start.y - end.y) * (start.y - end.y);
		len += (start.z - end.z) * (start.z - end.z);
		return len;
	}

	//単位ベクトルを返す
	//長さがなかった場合0ベクトルが返る
	Vector3D Normalize() const
	{
		Vector3D tmp;
		float len = this->Len();
		if (len > 0)
		{
			tmp.x = x / len;
			tmp.y = y / len;
			tmp.z = z / len;
		}
		return tmp;
	}

	// ラジアン値を返す
	Vector3D Radian() const
	{
		Vector3D tmp;
		tmp.x = this->x * 3.1415926f /180.0f;
		tmp.y = this->y * 3.1415926f /180.0f;
		tmp.z = this->z * 3.1415926f /180.0f;
		return tmp;
	}

	// 角度値を返す
	Vector3D Degree() const
	{
		Vector3D tmp;
		tmp.x = this->x * 180.0f / 3.1415926f;
		tmp.y = this->y * 180.0f / 3.1415926f;
		tmp.z = this->z * 180.0f / 3.1415926f;
		return tmp;
	}

	// Vector3D → DxLibのVECTOR 形式に変換
	VECTOR toVECTOR() const
	{
		VECTOR tmp = VGet(0.0f,0.0f,0.0f);
		tmp.x = x;
		tmp.y = y;
		tmp.z = z;
		return tmp;
	}

};

inline Vector3D operator*(const float scale, const Vector3D& vec)
{
	Vector3D tmp(vec);
	tmp *= scale;
	return tmp;
}

inline Vector3D operator*(const Vector3D& vec, const float scale)
{
	Vector3D tmp(vec);
	tmp *= scale;
	return tmp;
}

//スカラー減算
inline Vector3D operator/(const Vector3D& vec, const float scale)
{
	Vector3D tmp(vec);
	tmp /= scale;
	return tmp;
}

// 外積
inline Vector3D operator%(const Vector3D& left, const Vector3D& right)
{
	Vector3D tmp;
	tmp.x = left.y * right.z - left.z * right.y;
	tmp.y = left.z * right.x - left.x * right.z;
	tmp.z = left.x * right.y - left.y * right.x;
	return tmp;
};

inline Vector3D Lerp(const Vector3D& start, const Vector3D& end, float t)
{
	Vector3D tmp;
	tmp = start + (end - start) * t;
	return tmp;
}

inline Vector3D WallSlide(const Vector3D& vec, const Vector3D& normal)
{
	Vector3D tmp;
	tmp = vec - (normal * vec.Dot(normal));
	return tmp;
}

inline Vector3D Reflect(const Vector3D& vec, const Vector3D& normal) 
{
	Vector3D tmp;
	tmp = vec - normal * (2.0f * vec.Dot(normal));
	return tmp;
}