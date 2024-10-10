//----------------------------------------------------------------------
// @filename 3DCollision.h
// @author: Saito Ko Fukuma Kyohei Kawai Daisuke
// @explanation
// 3Dで使用する当たり判定を行うクラス
//----------------------------------------------------------------------
#pragma once
#include "MyStructure.h"
#include "../../Header/Collision/2DCollision.h"
#include"dxlib.h"
class Collision3D
{
public:

	//最短距離は大体点と点を垂直に下した線になる

	//平面上での四角同士のあたり判定
	static bool PlaneCollision(Vector3D pos1, float w1, float d1, Vector3D pos2, float w2, float d2);

	//AABBの当たり判定
	static bool AABBCollision(Vector3D pos1, float w1, float h1, float d1, Vector3D pos2, float w2, float h2, float d2);

	//平面上での円のあたり判定
	static bool CircleCollision(Vector3D pos1, float r1, Vector3D pos2, float r2);

	//円柱の当たり判定
	static bool CylindCollision(Vector3D pos1, float r1,float h1, Vector3D pos2, float r2,float h2);

	//AABBの最短距離
	static float AABBShortLength(Vector3D Box, float wide, float height, float depth, Vector3D Point);

	//OBB同士の当たり判定
	static bool OBBCollision(OBB box_1,OBB box_2);

    //点と直線の最短距離
	static POINT_LINE_SHORT PointLineShortLength(Vector3D line_start, Vector3D line_end, Vector3D point);

	//点と線分の最短距離   私的な作りは始点と終点はワールド座標で入れる
	static POINT_LINE_SHORT PointLineSegShortLength(Vector3D line_start, Vector3D line_end, Vector3D point);

	//2直線の垂直になる場所とベクトル係数
	static TWOLINE_SHORT TwoLineShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end);

	//2線分の垂直になる場所とベクトル係数
	static TWOLINE_SHORT TwoSegmentShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end);

	//球と球の当たり判定
	static bool SphereCol(Vector3D pos1, float r1, Vector3D pos2, float r2);
	static bool SphereCol(const Sphere& sphere1, const Sphere& sphere2);

	//カプセル同士の当たり判定
	static bool TwoCapsuleCol(Vector3D line_1_start, Vector3D line_1_end, float r_1, Vector3D line_2_start, Vector3D line_2_end, float r_2);
	static bool TwoCapsuleCol(const Capsule& capsule1, const Capsule& capsule2);

	// 球とカプセルの当たり判定
	static bool SphereCapsuleCol(Vector3D spherePos, float sphereR, Vector3D capsuleStartPos, Vector3D capsuleEndPos, float capsuleR, Vector3D* shortestPos = nullptr);
	static bool SphereCapsuleCol(const Sphere& sphere, const Capsule& capsule, Vector3D* shortestPos = nullptr);

	//点とＯＢＢの最接近点　OBBと点が一番近いOBBの位置を返します。
	static  Vector3D PointOBB(Vector3D point, OBB obb);
	
	//OBBと球の当たり判定
	static bool OBBSphereCol(OBB obb, Vector3D point, float r, Vector3D* hitPos = nullptr);
	static bool OBBSphereCol(const OBB& obb, const Sphere& sphere, Vector3D* hitPos = nullptr);

	//OBBとカプセルの当たり判定
	static bool OBBCapsuleCol(OBB obb, Vector3D line_start, Vector3D line_end, float r, Vector3D* hitPos = nullptr);
	//オーバーロード
	static bool OBBCapsuleCol(OBB obb, Capsule capsule, Vector3D* hitPos = nullptr);

	//線分とOBBの当たり判定
	static bool SegmentOBB(Vector3D line_start, Vector3D line_end, OBB obb);

	//-------------------------------------------------------
	// 河合さん産
	static bool isParallel(VECTOR p1, VECTOR p2);

	static void clamp01(float& v);

	static void clamp1m1(float& v);

	static void clamp(float& v, float min, float max);

	//壁擦りベクトルの作成
	static Vector3D MakeWallLap(MV1_COLL_RESULT_POLY HitNorm, Vector3D MoveV);

	//abs関数を使ってベクトルの絶対値を求める
	static float VectorAbs(Vector3D v);

	//点と円錐の当たり判定
	static bool CheckHitPointCorn(Vector3D top, Vector3D bottom, float r, Vector3D p);

	// 線分と平面の交差判定
	// 点p1aと法線p1nの平面と線分p2a,p2bの交差判定
	// hは交点
	static bool CheckHitSegmentPlane(Vector3D p1a, Vector3D p1n, Vector3D p2a, Vector3D p2b, Vector3D& h);

	// 線分と平面の交差判定
	// 点p1a,p1b,p1cの平面と線分p2a,p2bの交差判定
	// hは交点
	static bool CheckHitTriangleSegment(Vector3D p1a, Vector3D p1b, Vector3D p1c, Vector3D p2a, Vector3D p2b, Vector3D& h, float& t);

	//-------------------------------------------------------
	// 福間君産
	//点と扇形の当たり判定
	//v1:方向ベクトル, v2:差分ベクトル, rad;角度
	static bool CollisionPointAndFan(Vector3D v1, Vector3D v2, float rad);

	//球面座標系からデカルト座標系に変換する
	static class Vector3D ConvertToCartesian(class Vector3D angle, float radius);
};