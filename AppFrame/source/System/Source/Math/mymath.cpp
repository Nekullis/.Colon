//----------------------------------------------------------------------
// @filename mymath.cpp
// @author: Saito Ko
// @explanation
// 計算を簡略化するための関数をまとめたクラス
//----------------------------------------------------------------------
#include "../../Header/Math/mymath.h"

//----------------------------------------------------------------------
// @brief 角度をdegreeからradianに変換
// @param deg: degree
// @return radian
//----------------------------------------------------------------------
float Math::DegToRad(float deg) {
	return deg * PI / 180.0f;		// 角度をdegreeからradianに変換
}

//----------------------------------------------------------------------
// @brief 角度をradianからdegreeに変換
// @param rad: radian
// @return degree
//----------------------------------------------------------------------
float Math::RadToDeg(float rad) {
	return rad * 180.0f / PI;		// 角度をradianからdegreeに変換
}

//----------------------------------------------------------------------
// @brief 2つの値のうち大きい方を返す
// @param left: 左辺
// @param right: 右辺
// @return 大きい方の値
//----------------------------------------------------------------------
float Math::Max(float left, float right) {
	return left > right ? left : right;
};

//----------------------------------------------------------------------
// @brief 2つの値のうち小さい方を返す
// @param left: 左辺
// @param right: 右辺
// @return 小さい方の値
//----------------------------------------------------------------------
float Math::Min(float left, float right) {
	return left < right ? left : right;
};

//----------------------------------------------------------------------
// @brief nをmin_nとmax_nの間に収める
// @param min_n: 最小値
// @param max_n: 最大値
// @param n: 値
// @return min_n <= n <= max_n
float Math::Clamp(float min_n, float max_n, float n) {
	if (n <= min_n) { return min_n; }
	if (n >= max_n) { return max_n; }
	return n;
}

//
//ループ文で使いやすい
//----------------------------------------------------------------------
// @brief マトリックスを作りベクトルを正規化し回転させる
// @param norm: 回転させるベクトル
// @param rotation: 回転角度
// @param type: 0:x 1:y 2:z
// @return 回転後のベクトル
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
// @brief 行列からベクトルを取り出す
// @param matrix: 行列
// @param index: 0:x 1:y 2:z
// @return ベクトル
//----------------------------------------------------------------------
Vector3D Math::MatrixToVector(MATRIX matrix,int index) {
	return VGet(matrix.m[index][0], matrix.m[index][1], matrix.m[index][2]);
}

//----------------------------------------------------------------------
// @brief 分離軸に投影された軸成分から投影線分長を算出
// @param Sep: 分離軸
// @param e1: 軸成分1
// @param e2: 軸成分2
// @param e3: 軸成分3
// @return 投影線分長
//----------------------------------------------------------------------
float  Math::LenSegOnSeparateAxis(Vector3D Sep, Vector3D e1, Vector3D e2, Vector3D e3 ) {

	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabsf(Sep.Dot(e1));
	float r2 = fabsf(Sep.Dot(e2));
	float r3 = 0.0f;
	if (e3.x != 0 || e3.y != 0 || e3.z != 0) {
		r3 = fabsf(Sep.Dot(e3));
	}
	return r1 + r2 + r3;
}

//----------------------------------------------------------------------
// @brief XYZ軸回転行列を作成
// @param dir_x: X軸回転角度
// @param dir_y: Y軸回転角度
// @param dir_z: Z軸回転角度
// @return XYZ軸回転行列
//----------------------------------------------------------------------
MATRIX Math::MMultXYZ(float dir_x, float dir_y, float dir_z) {
	MATRIX matrix;
	matrix = MGetRotX(dir_x);
	matrix = MMult(matrix, MGetRotY(dir_y));
	matrix = MMult(matrix, MGetRotZ(dir_z));

	return matrix;
};

//----------------------------------------------------------------------
// @brief XYZ軸回転行列を作成し、カメラビルボード行列を掛ける
// @param dir_x: X軸回転角度
// @param dir_y: Y軸回転角度
// @param dir_z: Z軸回転角度
// @return XYZ軸回転行列
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
// @brief 行列から正規直行ベクトルを作成する
// @param vec_x: X軸ベクトル
// @param vec_y: Y軸ベクトル
// @param vec_z: Z軸ベクトル
// @param matrix: 行列
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Math::SetMatrixToVector(Vector3D& vec_x, Vector3D& vec_y, Vector3D& vec_z, const MATRIX matrix) {
	vec_x = Vector3D(matrix.m[0][0], matrix.m[0][1], matrix.m[0][2]);
	vec_y = Vector3D(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
	vec_z = Vector3D(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
	return true;
}

//----------------------------------------------------------------------
// @brief 鋭角かどうか
// @param p1: ベクトル1
// @param p2: ベクトル2
// @param p3: ベクトル3
// @return 鋭角かどうか
//----------------------------------------------------------------------
bool Math::CheckAcuteAngle(Vector3D p1, Vector3D p2, Vector3D p3) {
	return (p1 - p2).Dot(p3 - p2) >= 0.0f;
}

//----------------------------------------------------------------------
// @brief 平行かどうか
// @param line_1_start: 線分1始点
// @param line_1_end: 線分1終点
// @param line_2_start: 線分2始点
// @param line_2_end: 線分2終点
// @return 平行かどうか
//----------------------------------------------------------------------
bool Math::CheckParallelRelation(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	Vector3D line_1 = line_1_end - line_1_start;
	Vector3D line_2 = line_2_end - line_2_start;
	float value = (line_1.Cross(line_2)).Len();
	float effective_range = 0.001f;
	return -effective_range <= value && value <= effective_range;
}

//----------------------------------------------------------------------
// @brief 垂直かどうか
// @param line_1_start: 線分1始点
// @param line_1_end: 線分1終点
// @param line_2_start: 線分2始点
// @param line_2_end: 線分2終点
// @return 垂直かどうか
//----------------------------------------------------------------------
bool Math::CheckVerticalRelation(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	Vector3D line_1 = line_1_end - line_1_start;
	Vector3D line_2 = line_2_end - line_2_start;
	float dot = line_1.Dot(line_2);
	float effective_range = 0.001f;
	return -effective_range <= dot && dot <= effective_range;
}

//----------------------------------------------------------------------
// @brief 2つのベクトルのなす角を計算する
// @param v1: ベクトル1
// @param v2: ベクトル2
// @return 角度(radian)
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
// @brief 3Dモデルを引数vForwardの方向が正面になるように回転させる
// @param modelHandle: モデルハンドル
// @param vForward: 正面方向
//----------------------------------------------------------------------
void Math::SetModelForward_RotationY(int modelHandle, Vector3D vForwad)
{
	Vector3D vBase = Vector3D(0.0f, 0.0f, -1.0f);
	vForwad.y = 0.0f;
	float angle = CalcVectorAngle(vBase, vForwad);
	angle *= vForwad.x < 0.0f ? 1.0f : -1.0f;
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));
}
