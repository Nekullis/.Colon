//----------------------------------------------------------------------
// @filename Matrix3D.cpp
// @author: Fukuma Kyohei
// @explanation
// 3D空間でのマトリックスを扱うクラス
//----------------------------------------------------------------------
#include "../../Header/Math/Matrix3D.h"
#include "../../Header/Math/Vector3D.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
Matrix3D::Matrix3D()
{
	//要素を全て0にする
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_m[i][j] = 0;
		}
	}
}
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Matrix3D::~Matrix3D()
{
}
//----------------------------------------------------------------------
// @brief 行列の初期化
// @return 無し
//----------------------------------------------------------------------
Matrix3D Matrix3D::Ident()
{
	Matrix3D temp;
	//行列の初期化、[0][0],[1][1],[2][2],[3][3]を1にしておく
	for (int i = 0; i < 4; i++)
	{
		temp._m[i][i] = 1;
	}
	return temp;
}
//----------------------------------------------------------------------
// @brief 加算
// @param right:加算するマトリックス
// @return 加算結果
//----------------------------------------------------------------------
Matrix3D Matrix3D::operator+=(const Matrix3D& right)
{
	//一時的な行列の作成
	Matrix3D temp;
	//各行、各列で加算を行う
	//0行
	temp._m[0][0] = _m[0][0] + right._m[0][0];
	temp._m[0][1] = _m[0][1] + right._m[0][1];
	temp._m[0][2] = _m[0][2] + right._m[0][2];
	temp._m[0][3] = _m[0][3] + right._m[0][3];
	//1行
	temp._m[1][0] = _m[1][0] + right._m[1][0];
	temp._m[1][1] = _m[1][1] + right._m[1][1];
	temp._m[1][2] = _m[1][2] + right._m[1][2];
	temp._m[1][3] = _m[1][3] + right._m[1][3];
	//2行
	temp._m[2][0] = _m[2][0] + right._m[2][0];
	temp._m[2][1] = _m[2][1] + right._m[2][1];
	temp._m[2][2] = _m[2][2] + right._m[2][2];
	temp._m[2][3] = _m[2][3] + right._m[2][3];
	//3行
	temp._m[3][0] = _m[3][0] + right._m[3][0];
	temp._m[3][1] = _m[3][1] + right._m[3][1];
	temp._m[3][2] = _m[3][2] + right._m[3][2];
	temp._m[3][3] = _m[3][3] + right._m[3][3];
	return temp;
}
//----------------------------------------------------------------------
// @brief 減算
// @param right:減算するマトリックス
// @return 減算結果
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
// @brief 等号オペレータ
// @param right:比較するマトリックス
// @return 比較結果
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
// @brief 不等号オペレータ
// @param right:比較するマトリックス
// @return 比較結果
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
// @brief DxLib用マトリックス変換
// @return 変換結果
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
// @brief マトリックスのスケーリング
// @param m:スケーリングするマトリックス
// @param value:スケールの値
// @return スケーリング結果
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
// @brief スケーリングしたマトリックス取得
// @param vec:マトリックスのスケーリング値
// @return スケーリングしたマトリックス
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
// @brief 平行移動マトリックス取得
// @param vec:マトリックスの平行移動値
// @return 平行移動したマトリックス取得
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
// @brief 加算
// @param left: マトリックス1
// @param right: マトリックス2
// @return 加算結果
//----------------------------------------------------------------------
const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(left) += right;
}
//----------------------------------------------------------------------
// @brief 乗算
// @param left: マトリックス1
// @param right: マトリックス2
// @return 乗算結果
//----------------------------------------------------------------------
const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(left) *= right;
}
//----------------------------------------------------------------------
// @brief 指定値でのX軸の回転行列取得
// @param value:回転値(rad)
// @return 回転行列取得
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
// @brief 指定値でのY軸の回転行列取得
// @param value:回転値(rad)
// @return 回転行列取得
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
// @brief 指定値でのZ軸の回転行列取得
// @param value:回転値(rad)
// @return 回転行列取得
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

