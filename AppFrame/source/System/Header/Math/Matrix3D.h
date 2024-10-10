//----------------------------------------------------------------------
// @filename Matrix3D.h
// @author: Fukuma Kyohei
// @explanation
// 行列計算を行うクラス
//----------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include <math.h>
//3Dにおける行列関連のクラス
class Matrix3D
{
public:
	Matrix3D();
	~Matrix3D();
	Matrix3D Ident();
	//オペレータオーバーロード
	Matrix3D  operator+=(const Matrix3D& right);
	Matrix3D  operator*=(const Matrix3D& right);
	bool      operator==(const Matrix3D& right);
	bool      operator!=(const Matrix3D& right);
	//DXライブラリのMATRIXを使えるように
	Matrix3D& operator= (const MATRIX& right);
	MATRIX  dxl();
	//X軸
	static Matrix3D  MGetRotX(float d);
	//y軸
	static Matrix3D  MGetRotY(float d);
	//z軸
	static Matrix3D  MGetRotZ(float d);
	//matrix計算処理
	//スケーリング
	Matrix3D  MScale(Matrix3D m, float d);
	//ベクトルによる拡大縮小
	Matrix3D  MGetScale(class Vector3D& vec);
	//ベクトルによる平行移動
	Matrix3D  MGetTranslate(class Vector3D& vec);
	
public:
	float _m[4][4];
};
//クラス外オペレータオーバーロード
//加算
const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right);
//乗算
const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right);
//回転行列