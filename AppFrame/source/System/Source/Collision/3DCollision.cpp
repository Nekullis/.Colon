//----------------------------------------------------------------------
// @filename 3DCollision.cpp
// @author: Saito Ko Fukuma Kyohei Kawai Daisuke
// @explanation
// 3Dで使用する当たり判定を行うクラス
//----------------------------------------------------------------------
#include "../../Header/Collision/3DCollision.h"

//----------------------------------------------------------------------
// @brief XZ平面での当たり判定
// @param pos1 位置1
// @param w1 幅1
// @param d1 奥行1
// @param pos2 位置2
// @param w2 幅2
// @param d2 奥行2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::PlaneCollision(Vector3D pos1, float w1,float d1, Vector3D pos2, float w2, float d2)
{
	Vector3D receiv = pos1 - Vector3D(w1 / 2, 0, d1 / 2);
	Vector3D give = pos2 - Vector3D(w2 / 2, 0, d2 / 2);

	return Collision2D::IsHitBox(receiv.x, receiv.z, w1, d1, give.x, give.z, w2, d2);
}

//----------------------------------------------------------------------
// @brief AABBでの当たり判定
// @param pos1 位置1
// @param w1 幅1
// @param h1 高さ1
// @param d1 奥行1
// @param pos2 位置2
// @param w2 幅2
// @param h2 高さ2
// @param d2 奥行2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::AABBCollision(Vector3D pos1, float w1, float h1, float d1, Vector3D pos2, float w2, float h2, float d2)
{
	Vector3D receiv = pos1 - Vector3D(w1 / 2, h1 / 2, d1 / 2);
	Vector3D give = pos2 - Vector3D(w2 / 2, h2 / 2, d2 / 2);

	if(Collision2D::IsHitBox(receiv.x, receiv.z, w1, d1, give.x, give.z, w2, d2)) {
		if(Collision2D::IsHitBox(receiv.x, receiv.y, w1, h1, give.x, give.y, w2, h2)) {
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------
// @brief XZ平面での円の当たり判定
// @param pos1 位置1
// @param r1 半径1
// @param pos2 位置2
// @param r2 半径2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::CircleCollision(Vector3D pos1, float r1, Vector3D pos2, float r2){
	Vector3D col = pos1 - pos2; col.y = 0;
	float r = r1 + r2;
	if (r * r > col.x * col.x + col.z * col.z) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
// @brief 円柱の当たり判定
// @param pos1 位置1
// @param r1 半径1
// @param h1 高さ1
// @param pos2 位置2
// @param r2 半径2
// @param h2 高さ2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::CylindCollision(Vector3D pos1, float r1, float h1, Vector3D pos2, float r2, float h2) {
	Vector3D col = pos1 - pos2;
	float r = r1 + r2;
	if (r * r > col.x * col.x + col.z * col.z) {
		if (pos1.y < pos2.y && pos1.y + h1 > pos2.y ||
			pos1.y < pos2.y + h2 && pos1.y + h1 > pos2.y + h2) {
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
// @brief AABBの最短距離
// @param Box ボックスの位置
// @param wide 幅
// @param height 高さ
// @param depth 奥行
// @param Point 点の位置
// @return 最短距離
//----------------------------------------------------------------------
float Collision3D::AABBShortLength(Vector3D Box, float wide, float height ,float depth , Vector3D Point) {
	float SqLen = 0;   // 長さのべき乗の値を格納
	float point[3] = { Point.x,Point.y,Point.z};
	float box[3] = { Box.x,Box.y,Box.z };
	float length[3] = { wide/2,height/2,depth/2 };

	for (int i = 0; i < 3; i++)
	{
		// 各軸で点が最小値以下もしくは最大値以上ならば、差を考慮
		if (point[i] < box[i] - length[i])  // i=0はX、1はY、2はZの意味です
			SqLen += ((point[i] - (box[i] - length[i])) * (point[i] - (box[i] - length[i])));
		if (point[i] > box[i] + length[i])
			SqLen += ((point[i] - (box[i] + length[i])) * (point[i] - (box[i] + length[i])));
	}
	return sqrtf(SqLen);
}

//----------------------------------------------------------------------
// @brief OBB同士の当たり判定
// @param obb_1 OBBの情報
// @param obb_2 OBBの情報
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::OBBCollision(OBB obb_1, OBB obb_2) {
	// lengthは全体の長さなので使うときは半分にする
	//NAe は 方向ベクトル Ae は 方向ベクトルにその長さをかけたもの　方向ベクトルはマトリクスから持ってきたもので正規化されている

	Vector3D NAe1 = obb_1.dir_vec[0], Ae1 = NAe1 * (obb_1.length[0] / 2);
	Vector3D NAe2 = obb_1.dir_vec[1], Ae2 = NAe2 * (obb_1.length[1] / 2);
	Vector3D NAe3 = obb_1.dir_vec[2], Ae3 = NAe3 * (obb_1.length[2] / 2);
	Vector3D NBe1 = obb_2.dir_vec[0], Be1 = NBe1 * (obb_2.length[0] / 2);
	Vector3D NBe2 = obb_2.dir_vec[1], Be2 = NBe2 * (obb_2.length[1] / 2);
	Vector3D NBe3 = obb_2.dir_vec[2], Be3 = NBe3 * (obb_2.length[2] / 2);
	//Misalignmentでおなかの中心にモデルをずらしている 大体ｙ軸だけで済むと思うがフライト系などの3軸回転を入れるときは
	//VTransformの中の回転行列をy軸だけでなくｘとｚを含めた3軸で回転してください
	Vector3D Interval = obb_1.pos - obb_2.pos;

	//  各軸の方向ベクトルと分離軸との絶対値の内積の和をまとめたものと 中心点間の距離を比較し中心点間距離より短かったら衝突している

	// 分離軸 : Ae1
	float rA = Ae1.Len();
	float rB = Math::LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
	float L = fabsf(Interval.Dot(NAe1));
	if (L > rA + rB)
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = Ae2.Len();
	rB = Math::LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
	L = fabsf(Interval.Dot(NAe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	rA = Ae3.Len();
	rB = Math::LenSegOnSeparateAxis(NAe3, Be1,Be2,Be3);
	L = fabsf(Interval.Dot(NAe3));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = Math::LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
	rB = Be1.Len();
	L = fabsf(Interval.Dot(NBe1));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = Math::LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
	rB = Be2.Len();
	L = fabsf(Interval.Dot(NBe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	rA = Math::LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
	rB = Be3.Len();
	L = fabsf(Interval.Dot(NBe3));
	if (L > rA + rB)
		return false;

	// ↓9割の計算は上の方向ベクトルだけでもできる
	//  OBBが辺同士ひねった関係で近づくと方向ベクトルの分離軸では判定できなくなるそうです

	// 分離軸 : C11   Ae1*Be1に垂直
	Vector3D Cross;
	Cross = NAe1.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C12   Ae1*Be2
	Cross = NAe1.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C13   Ae1*Be3
	Cross = NAe1.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C21   Ae2*Be1
	Cross = NAe2.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C22   Ae2*Be2
	Cross = NAe2.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C23   Ae2*Be3
	Cross = NAe2.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C31   Ae3*Be1
	Cross = NAe3.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C32   Ae3*Be2
	Cross = NAe3.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C33   Ae3*Be3
	Cross = NAe3.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

//----------------------------------------------------------------------
// @brief 点と直線の最短距離
//             最短距離は大体点と点を垂直に下した線になる
// @param line_start 直線の始点
// @param line_end 直線の終点
// @param point 点の位置
// @return 最短距離
//----------------------------------------------------------------------
POINT_LINE_SHORT Collision3D::PointLineShortLength(Vector3D line_start, Vector3D line_end, Vector3D point) {
	POINT_LINE_SHORT Re;
	Vector3D line = line_end - line_start;
	float length = line.Sqlen();

	Re.coefficient = 0.0f;
	if (length > 0.0f) {
		Re.coefficient = line.Dot(point - line_start) / length;
	}

	Re.hit_point = line_start + (line * Re.coefficient);
	Re.length = (Re.hit_point - point).Len();

	return Re;
};

//----------------------------------------------------------------------
// @brief 点と線分の最短距離
//             最短距離は大体点と点を垂直に下した線になる
// @param line_start 線分の始点
// @param line_end 線分の終点
// @param point 点の位置
// @return 最短距離
//----------------------------------------------------------------------
POINT_LINE_SHORT Collision3D::PointLineSegShortLength(Vector3D line_start, Vector3D line_end, Vector3D point) {
	Vector3D end = line_end - line_start;
	POINT_LINE_SHORT Re = Collision3D::PointLineShortLength(line_start, line_end, point);

	if (!Math::CheckAcuteAngle(point, line_start, line_end)) {
		//始点側
		Re.hit_point = line_start;
		Re.length = (line_start - point).Len();
	}
	else if (!Math::CheckAcuteAngle(point, line_start + end, line_start)) {
		//終点側
		Re.hit_point = line_start + end;
		Re.length = (end - point).Len();
	}

	return Re;
}

//----------------------------------------------------------------------
// @brief 2直線の垂直になる場所とベクトル係数
// @param line_1_start 直線1の始点
// @param line_1_end 直線1の終点
// @param line_2_start 直線2の始点
// @param line_2_end 直線2の終点
// @return 2直線の最短距離・直線1の最短距離の点・直線1のベクトル係数・直線2の最短距離の点・直線2のベクトル係数
//----------------------------------------------------------------------
TWOLINE_SHORT Collision3D::TwoLineShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	TWOLINE_SHORT Re;
	Vector3D one_way = line_1_end - line_1_start;
	Vector3D two_way = line_2_end - line_2_start;

	//平行な直線か調べる
	if (Math::CheckParallelRelation(line_1_start, line_1_end, line_2_start, line_2_end)) {
		POINT_LINE_SHORT pls = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.length = pls.length;
		Re.lineOnePoint = line_1_start;
		Re.lineOneCoefficient = 0.0f;
		Re.lineTwoPoint = pls.hit_point;
		Re.lineTwoCoefficient = pls.coefficient;

		return Re;
	}

	float Dot_OwTw = one_way.Dot(two_way);//方向1と方向2の垂直な距離
	float Dot_OsOw = one_way.Sqlen();//線分1と方向1の垂直な距離
	float Dot_TsTw = two_way.Sqlen();//線分2と方向2の垂直な距離
	Vector3D Sub_OsTs = line_1_start - line_2_start;//始点1から始点2の方向

	Re.lineOneCoefficient = (Dot_OwTw * two_way.Dot(Sub_OsTs) - Dot_TsTw * one_way.Dot(Sub_OsTs)) / (Dot_OsOw * Dot_TsTw - Dot_OwTw * Dot_OwTw);
	Re.lineOnePoint = line_1_start + one_way * Re.lineOneCoefficient;
	Re.lineTwoCoefficient = two_way.Dot(Re.lineOnePoint - line_2_start) / Dot_TsTw;
	Re.lineTwoPoint = line_2_start + two_way * Re.lineTwoCoefficient;
	Re.length = (Re.lineTwoPoint - Re.lineOnePoint).Len();

	return Re;
}

//----------------------------------------------------------------------
// @brief 2線分の垂直になる場所とベクトル係数
// @param line_1_start 線分1の始点
// @param line_1_end 線分1の終点
// @param line_2_start 線分2の始点
// @param line_2_end 線分2の終点
// @return 2線分の最短距離・線分1の最短距離の点・線分1のベクトル係数・線分2の最短距離の点・線分2のベクトル係数
//----------------------------------------------------------------------
TWOLINE_SHORT Collision3D::TwoSegmentShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {

	TWOLINE_SHORT Re;

	Vector3D one_way = line_1_end - line_1_start;
	Vector3D two_way = line_2_end - line_2_start;

	float effective_range = 0.001f;

	//縮退　小さすぎて点になっている　点で考える
	//線分1が縮退しているか
	if (one_way.Sqlen() < effective_range) {
		//線分1が縮退していた
		//線分2も縮退しているか
		if (two_way.Sqlen() < effective_range) {
			// 線分2は縮退していた
			Re.lineOnePoint = line_1_start;
			Re.lineTwoPoint = line_2_start;
			Re.lineOneCoefficient = 0.0f;
			Re.lineTwoCoefficient = 0.0f;
			Re.length = (line_2_start- line_1_start).Len();
			return Re;
		}
		else {
			// 線分2は縮退していなかった
			//線分1の始点と直線2の最短距離
			POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_2_start, line_2_end, line_1_start);
			Re.lineOnePoint = line_1_start;
			Re.lineOneCoefficient = 0.0f;
			Re.lineTwoPoint = value.hit_point;
			Re.lineTwoCoefficient = value.coefficient;
			Re.length = value.length;
			Re.lineTwoCoefficient = Math::Clamp(0, 1.0f, Re.lineTwoCoefficient);
			return Re;
		}
	}
	//線分2が縮退しているか
	else if (two_way.Sqlen() < effective_range) {
		// 線分2は縮退していた
		//上で線分1は確認したのでここはしない
		POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.lineOnePoint = value.hit_point;
		Re.lineOneCoefficient = value.coefficient;
		Re.lineTwoPoint = line_2_start;
		Re.lineTwoCoefficient = 0.0f;
		Re.length = value.length;
		Re.lineOneCoefficient = Math::Clamp(0, 1.0f, Re.lineOneCoefficient);
		return Re;
	}

	//縮退がなかったので線分同士で考える
	//線分1と線分2が並行か
	if (Math::CheckParallelRelation(line_1_start, line_1_end, line_2_start, line_2_end)) {
		//平行だったので垂線の端の一つをＰ1とする
		POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.lineOnePoint = line_1_start;
		Re.lineOneCoefficient = 0.0f;
		Re.lineTwoPoint = value.hit_point;
		Re.lineTwoCoefficient = value.coefficient;
		Re.length = value.length;
		if (0.0f <= Re.lineTwoCoefficient && Re.lineTwoCoefficient <= 1.0f) {
			return Re;
		}
	}
	else {
		//平行でなかったので線分二つの最短距離を求める
		Re = Collision3D::TwoLineShortPoint(line_1_start, line_1_end, line_2_start, line_2_end);
		if (0.0f <= Re.lineOneCoefficient && Re.lineOneCoefficient <= 1.0f &&
			0.0f <= Re.lineTwoCoefficient && Re.lineTwoCoefficient <= 1.0f) {
			return Re;
		}
	}

	//垂線の端が線分の外側にあるので
	//線分1側のベクトル係数を0から1の間にクランプして垂線を降ろす

	Re.lineOneCoefficient = Math::Clamp(0, 1, Re.lineOneCoefficient);
	Re.lineOnePoint = line_1_start + one_way * Re.lineOneCoefficient;
	POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_2_start, line_2_end, Re.lineOnePoint);
	Re.lineTwoCoefficient = value.coefficient;
	Re.lineTwoPoint = value.hit_point;
	Re.length = value.length;

	if (0.0f <= Re.lineTwoCoefficient && Re.lineTwoCoefficient <= 1.0f) {
		return Re;
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	Re.lineTwoCoefficient = Math::Clamp(0, 1, Re.lineTwoCoefficient);
	Re.lineTwoPoint = line_2_start + two_way * Re.lineTwoCoefficient;
	value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, Re.lineTwoPoint);

	Re.lineOneCoefficient = value.coefficient;
	Re.lineOnePoint = value.hit_point;
	Re.length = value.length;

	if (0.0f <= Re.lineOneCoefficient && Re.lineOneCoefficient <= 1.0f) {
		return Re;
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	Re.lineOneCoefficient = Math::Clamp(0, 1, Re.lineOneCoefficient);
	Re.lineOnePoint = line_1_start + one_way * Re.lineOneCoefficient;
	Re.length = (Re.lineTwoPoint - Re.lineOnePoint).Len();
	return Re;
}

//----------------------------------------------------------------------
// @brief 球と球の当たり判定
// @param pos1 位置1
// @param r1 半径1
// @param pos2 位置2
// @param r2 半径2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::SphereCol(Vector3D pos1, float r1, Vector3D pos2, float r2) {
	return (pos2 - pos1).Sqlen() <= (r1 + r2) * (r1 + r2);
}

//----------------------------------------------------------------------
// @brief 球と球の当たり判定
// @param sphere1 球1
// @param sphere2 球2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::SphereCol(const Sphere& sphere1, const Sphere& sphere2)
{
	return Collision3D::SphereCol(sphere1.pos, sphere1.r, sphere2.pos, sphere2.r);
}

//----------------------------------------------------------------------
// @brief カプセル同士の当たり判定
// @param line_1_start カプセル1の始点
// @param line_1_end カプセル1の終点
// @param r_1 カプセル1の半径
// @param line_2_start カプセル2の始点
// @param line_2_end カプセル2の終点
// @param r_2 カプセル2の半径
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::TwoCapsuleCol(Vector3D line_1_start, Vector3D line_1_end, float r_1, Vector3D line_2_start, Vector3D line_2_end, float r_2) {
	TWOLINE_SHORT value = Collision3D::TwoSegmentShortPoint(line_1_start, line_1_end, line_2_start, line_2_end);
	return value.length <= r_1 + r_2;
}

//----------------------------------------------------------------------
// @brief カプセル同士の当たり判定
// @param capsule1 カプセル1
// @param capsule2 カプセル2
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::TwoCapsuleCol(const Capsule& capsule1, const Capsule& capsule2)
{
	return Collision3D::TwoCapsuleCol(capsule1.pos, capsule1.up_pos, capsule1.r, capsule2.pos, capsule2.up_pos, capsule2.r);
}

//----------------------------------------------------------------------
// @brief 球とカプセルの当たり判定
// @param spherePos 球の位置
// @param sphereR 球の半径
// @param capsuleStartPos カプセルの始点
// @param capsuleEndPos カプセルの終点
// @param capsuleR カプセルの半径
// @param[out] shortestPos 最短距離の位置
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::SphereCapsuleCol(Vector3D spherePos, float sphereR, Vector3D capsuleStartPos, Vector3D capsuleEndPos, float capsuleR, Vector3D* shortestPos)
{
	POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(capsuleStartPos, capsuleEndPos, spherePos);
	if (shortestPos != nullptr) {
		*shortestPos = value.hit_point;
	}
	return Collision3D::SphereCol(spherePos, sphereR, value.hit_point, capsuleR);
}

//----------------------------------------------------------------------
// @brief 球とカプセルの当たり判定
// @param sphere 球
// @param capsule カプセル
// @param[out] shortestPos 最短距離の位置
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::SphereCapsuleCol(const Sphere& sphere, const Capsule& capsule, Vector3D* shortestPos)
{
	return Collision3D::SphereCapsuleCol(sphere.pos, sphere.r, capsule.pos, capsule.up_pos, capsule.r, shortestPos);
}

//----------------------------------------------------------------------
// @brief 点とOBBの最接近点
// @param point 点の位置
// @param obb OBBの情報
// @return OBBと点が一番近いOBBの位置
//----------------------------------------------------------------------
Vector3D Collision3D::PointOBB(Vector3D point, OBB obb) {
	Vector3D pos = obb.pos;
	Vector3D cp = point - pos;
	Vector3D Re = pos;
	float length = 0.0f;
	for (int i = 0; i < 3; i++) {
		length = cp.Dot(obb.dir_vec[i]);

		if (length > (obb.length[i] / 2)) {
			length = obb.length[i] / 2;
		}
		else if (length < -obb.length[i] / 2) {
			length = -obb.length[i] / 2;
		}
		Re = Re+obb.dir_vec[i]* length;
	}
	return Re;
}

//----------------------------------------------------------------------
// @brief OBBと球の当たり判定
// @param obb OBB
// @param point 球の位置
// @param r 球の半径
// @param[out] hitPos 衝突した位置
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::OBBSphereCol(OBB obb, Vector3D point, float r, Vector3D* hitPos) {
	Vector3D pos = Collision3D::PointOBB(point, obb);

	Vector3D vector = pos - point;

	if (vector.Dot(vector) <= r * r) {
		if (hitPos != nullptr) {
			*hitPos = pos;
		}
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// @brief OBBと球当たり判定
// @param obb OBB
// @param sphere 球
// @param[out] hitPos 衝突した位置
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::OBBSphereCol(const OBB& obb, const Sphere& sphere, Vector3D* hitPos)
{
	return Collision3D::OBBSphereCol(obb, sphere.pos, sphere.r, hitPos);
}

//----------------------------------------------------------------------
// @brief OBBとカプセルの当たり判定
// @param obb OBB
// @param capsuleStartPos カプセルの始点
// @param capsuleEndPos カプセルの終点
// @param capsuleR カプセルの半径
// @param[out] hitPos 衝突した位置
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::OBBCapsuleCol(OBB obb, Vector3D line_start, Vector3D line_end, float r, Vector3D* hitPos) {
	POINT_LINE_SHORT  a = Collision3D::PointLineSegShortLength(line_start, line_end, obb.pos);

	Vector3D pos = Collision3D::PointOBB(a.hit_point, obb);

	Vector3D vector = pos - a.hit_point;

	if (vector.Dot(vector) <= r * r) {
		if (hitPos != nullptr) {
			*hitPos = pos;
		}
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// @brief OBBとカプセルの当たり判定
// @param obb OBB
// @param capsule カプセル
// @param[out] hitPos 衝突した位置
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::OBBCapsuleCol(OBB obb, Capsule capsule, Vector3D* hitPos) {
	return OBBCapsuleCol(obb, capsule.pos, capsule.up_pos, capsule.r, hitPos);
}

//----------------------------------------------------------------------
// @brief 線分とOBBの当たり判定
// @param line_start 線分の始点
// @param line_end 線分の終点
// @param obb OBB
// @return 衝突しているかどうか
//----------------------------------------------------------------------
bool Collision3D::SegmentOBB(Vector3D line_start, Vector3D line_end, OBB obb){
	for(int i = 0; i < 3; i++){
		TWOLINE_SHORT value = Collision3D::TwoSegmentShortPoint(line_start, line_end, obb.pos, obb.pos + obb.dir_vec[i] * obb.length[i]);
		if (value.length > obb.length[i]/2) {
			return false;
		}
	}
	return true;
};

//---------------------------------------------------------------------------------
// 河合さん産
//---------------------------------------------------------------------------------
 
//--------------------------------------------------------
// @brief 0～1の間にクランプ
// @param[out] v クランプする値
// @return なし
//--------------------------------------------------------
void Collision3D::clamp01(float& v) {
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

//--------------------------------------------------------
// @brief -1～1の間にクランプ
// @param[out] v クランプする値
// @return なし
// --------------------------------------------------------
void Collision3D::clamp1m1(float& v) {
	if (v < -1.0f)
		v = -1.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

//--------------------------------------------------------
// @brief min～maxの間にクランプ
// @param[out] v クランプする値
// @param[in] min 最小値
// @param[in] max 最大値
// @return なし
// --------------------------------------------------------
void Collision3D::clamp(float& v, float min, float max) {
	if (v < min)
		v = min;
	else if (v > max)
		v = max;
}

//--------------------------------------------------------
// @brief 平行か調べる
// @param[in] p1 座標1
// @param[in] p2 座標2
// @return 平行ならtrue
bool Collision3D::isParallel(VECTOR p1, VECTOR p2) {

	//外積取る
	VECTOR v = VCross(p1, p2);

	//サイズ見る
	float d = VSize(v);

	// 誤差範囲内なら平行と判定
	if (-0.0001f < d && d < 0.0001f) {

		return true;
	}

	return false;
}

//--------------------------------------------------------
// @brief DXlibを用いた壁擦りベクトルの作成
// @param HitNorm 当たった面の法線
// @param MoveV 移動ベクトル
// @return 壁擦りベクトル
// --------------------------------------------------------
Vector3D Collision3D::MakeWallLap(MV1_COLL_RESULT_POLY HitNorm, Vector3D MoveV) {

	//法線ベクトル(V)を求めるための公式
	// V = F * aN
	// F(移動ベクトル),a(-F * N),N(法線ベクトル（単位化したやつ）)

	// 法線ベクトル
	Vector3D norm = HitNorm.Normal;
	norm = norm.Normalize();

	// 移動ベクトル
	Vector3D FrontV = MoveV;

	// 移動ベクトルに-1かけたやつ（ReverseMove）
	Vector3D RMove = FrontV * -1;

	//壁に対して平行なベクトル(壁擦り)求めるのに使うやつ
	//法線と逆移動ベクトルの内積
	float a = RMove.Dot(norm);

	//壁に対して平行なベクトル(壁擦り)求めるのに使うやつその２
	//移動ベクトルに足すためのベクトル
	norm = norm * a;

	//壁擦りベクトル作成
	//WR = wall rapping = 壁擦り
	Vector3D WR = FrontV + norm;

	return WR;
}

//--------------------------------------------------------
// @brief ベクトルの絶対値を求める
// @param v ベクトル
// @return ベクトルの絶対値
// --------------------------------------------------------
float Collision3D::VectorAbs(Vector3D v)
{
	float v_comp[] = { v.x,v.y,v.z };
	int length = sizeof(v_comp) / sizeof(v_comp[0]);
	for (int i = 0; i < length; ++i)
	{
		v_comp[i] = abs(v_comp[i]);
	}
	Vector3D absV = Vector3D(v_comp[0], v_comp[1], v_comp[2]);
	return  sqrtf(absV.Sqlen());
}

//--------------------------------------------------------
// @brief 点と三角錐の当たり判定
// @param top 三角錐の頂点
// @param bottom 三角錐の底面
// @param r 半径
// @param p 点
// @return 衝突しているかどうか
// --------------------------------------------------------
bool Collision3D::CheckHitPointCorn(Vector3D top, Vector3D bottom, float r, Vector3D p)
{
	float h = VectorAbs(bottom - top);
	Vector3D PnT = p - top;
	Vector3D BnT = bottom - top;
	if (0.0f <= PnT.Dot(BnT) &&
		PnT.Dot(BnT) <= h * h &&
		VectorAbs(PnT.Cross(BnT)) <= VectorAbs(PnT) * r * h / sqrtf(r * r + h * h))
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------
// @brief 線分と平面の当たり判定
// @param p1a 平面の点1
// @param p1n 平面の法線
// @param p2a 線分の始点
// @param p2b 線分の終点
// @param[out] h 交点
// @return 衝突しているかどうか
// --------------------------------------------------------
bool Collision3D::CheckHitSegmentPlane(Vector3D p1a, Vector3D p1n, Vector3D p2a, Vector3D p2b, Vector3D& h)
{
	// 平面の法線ベクトルの成分
	float a = p1n.x, b = p1n.y, c = p1n.z;
	// 平面上の点の座標
	float x0 = p1a.x, y0 = p1a.y, z0 = p1a.z;

	// 線分の端点の座標
	float x1 = p2a.x, y1 = p2a.y, z1 = p2a.z;
	float x2 = p2b.x, y2 = p2b.y, z2 = p2b.z;

	// tの分母部分の計算（平面と線分の方向ベクトルの内積）
	float denominator = a * (x2 - x1) + b * (y2 - y1) + c * (z2 - z1);
	if (denominator == 0) {
		// 分母が0の場合、平面と線分は平行であるため交点なし
		return false;
	}

	// tの分子部分の計算（平面上の点と線分の始点のベクトルの内積）
	float numerator = a * (x0 - x1) + b * (y0 - y1) + c * (z0 - z1);

	// tの計算（線分上のどの位置に交点があるかを示すパラメータ）
	float t = numerator / denominator;
	if (t < 0.0f || t > 1.0f) {
		// tが0から1の範囲外であれば、交点は線分上に存在しない
		return false;
	}

	// 交点の計算（線分上の点のパラメータ表示にtを代入）
	h.x = (1 - t) * x1 + t * x2;
	h.y = (1 - t) * y1 + t * y2;
	h.z = (1 - t) * z1 + t * z2;


	return true;
}

//--------------------------------------------------------
// @brief 線分と三角形の当たり判定
// @param p1a 線分の始点
// @param p1b 線分の終点
// @param p2a 三角形の点1
// @param p2b 三角形の点2
// @param p2c 三角形の点3
// @param[out] h 交点
// @param[out] t 交点のパラメータ
// @return 衝突しているかどうか
// --------------------------------------------------------
bool Collision3D::CheckHitTriangleSegment(Vector3D p1a, Vector3D p1b, Vector3D p2a, Vector3D p2b, Vector3D p2c, Vector3D& h, float& t) {

	// ①平面の方程式を求める
	// 三角形の法線ベクトルの成分
	// 外積n = AB x AC
	// plane normalでpn

	Vector3D pn = (p2b - p2a).Cross(p2c - p2a);

	if (pn.x == 0.0f && pn.y == 0.0f && pn.z == 0.0f) {
		return false;
	}

	// 平面の方程式
	// ax + by + cz + d = 0
	// d = -(pn.x * p2a.x + pn.y * p2a.y + pn.z * p2a.z)
	float d = -(pn.x * p2a.x + pn.y * p2a.y + pn.z * p2a.z);

	// ②線分が平面を横切るかどうかを判定する
	// 線分平面のどちらにあるか
	float a = pn.x * p1a.x + pn.y * p1a.y + pn.z * p1a.z + d;
	float b = pn.x * p1b.x + pn.y * p1b.y + pn.z * p1b.z + d;

	// a,bの符号が異なる場合、線分は平面を横切る
	if (a * b >= 0) {
		return false;
	}

	// ③線分と平面の交点を求める
	// 線分の方向ベクトル
	Vector3D v = p1b - p1a;

	// 線分上のP(t) = p1 + t * v が平面上にあるためのｔを求める
	// pn.x * (p1a.x + t(p1b.x - p1a.x)) + pn.y * (p1a.y + t(p1b.y - p1a.y)) 
	//		+ pn.z * (p1a.z + t(p1b.z - p1a.z)) + d = 0
	// 
	//		-(pn.x * p1a.x + pn.y * p1a.y + pn.z * p1a.z + d) 
	// t = ----------------------------------------------------
	//			 pn.x * v.x + pn.y * v.y + pn.z * v.z

	float denominator = pn.x * v.x + pn.y * v.y + pn.z * v.z;
	if (denominator == 0.0f) {
		return false;
	}

	t = -a / denominator;

	// tが0から1の範囲外であれば、交点は線分上に存在しない
	if (t < 0.0f || t > 1.0f) {
		return false;
	}

	// 交点の計算（線分上の点のパラメータ表示にtを代入）
	h.x = p1a.x + t * v.x;
	h.y = p1a.y + t * v.y;
	h.z = p1a.z + t * v.z;

	return true;
}

//--------------------------------------------------------
// 福間君産
//--------------------------------------------------------

//--------------------------------------------------------
// @brief 点と扇形の当たり判定
// @param v1 方向ベクトル
// @param v2 差分ベクトル
// @param rad 角度
// @return 衝突しているかどうか
//--------------------------------------------------------
bool Collision3D::CollisionPointAndFan(Vector3D v1, Vector3D v2, float rad)
{
	//内積の計算
	v1 = v1.Normalize();
	v2 = v2.Normalize();
	float dot = v1.Dot(v2);
	//内積の計算がバグらないように
	if (dot < 0.0000001 && dot > -0.0000001) { return false; }
	if (dot > Math::DegToRad(rad))
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------
// @brief 球面座標系をデカルト座標系に変換
// @param angle 方向ベクトル
// @param radius 球面の中心点からの半径
// @return 変換結果
//--------------------------------------------------------
Vector3D Collision3D::ConvertToCartesian(Vector3D angle, float radius)
{
	Vector3D temp;
	//球面座標系をデカルト座標系に変換するために必要な要素は半径(radius),垂直角度(angleのx成分),水平角度(angleのy成分)
	temp.x = radius * cosf(angle.x) * sinf(angle.y);
	temp.y = radius * sinf(angle.x);
	temp.z = radius * cosf(angle.x) * cosf(angle.y);
	return temp;
}
