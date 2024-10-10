//----------------------------------------------------------------------
// @filename Spline.h
// @author: Saito Ko
// @explanation
// �ꎟ~�O���̃x�W�F�Ȑ��E�X�v���C���Ȑ��̌v�Z���s���N���X
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
	// 4�_�Ԃ��w�肵��2�_�Ԃ̕�Ԃ��s��
	static Vector3D CatmullRomSpline(const std::vector<Vector3D>& point, float time);
private:
	static float BSplineBase(int i, int k, float t, const std::vector<float>& knots);
};

