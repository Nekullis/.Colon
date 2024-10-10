//----------------------------------------------------------------------
// @filename Spline.h
// @author: Saito Ko
// @explanation
// 一次~三次のベジェ曲線・スプライン曲線の計算を行うクラス
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include "Vector3D.h"
class Spline
{
public:
	static Vector3D LinearSpline(const std::vector<Vector3D>& point , float time);
	static Vector3D QuadraticSpline(const std::vector<Vector3D>& point, float time);
	static Vector3D CubicSpline(const std::vector<Vector3D>& point, float time);
	static Vector3D BSpline(const std::vector<Vector3D>& point, int k, float time);
	// 4点間を指定して2点間の補間を行う
	static Vector3D CatmullRomSpline(const std::vector<Vector3D>& point, float time);
private:
	static float BSplineBase(int i, int k, float t, const std::vector<float>& knots);
};

