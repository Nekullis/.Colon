//----------------------------------------------------------------------
// @filename Spline.cpp
// @author: Saito Ko
// @explanation
// �ꎟ~�O���̃x�W�F�Ȑ��E�X�v���C���Ȑ��̌v�Z���s���N���X
//----------------------------------------------------------------------
#include "../../Header/Math/Spline.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../../Header/Math/mymath.h"

//----------------------------------------------------------------------
// @brief �ꎟ�׃W�F�Ȑ�
// @param point: �_�̍��W
// @param time: ����
// @return �ꎟ�׃W�F�Ȑ��̍��W
//----------------------------------------------------------------------
Vector3D Spline::LinearSpline(const std::vector<Vector3D>& point, float time){
#ifdef _DEBUG
	if (point.size() < 2) {
		// �����ɕK�v�ȓ_������Ȃ�
		DebugErrar();
		return Vector3D();
	}
#endif

	// �ǂ̃Z�O�����g�ɑ����邩������
	float t = Math::Clamp(0.0f, 1.0f, time) * (point.size() - 1);
	int segment = static_cast<int>(t);
	t -= segment;

	Vector3D p0 = point[segment];
	Vector3D p1 = point[segment + 1];

	// ���� : p(t) = (1 - t) * p0 + t * p1
	Vector3D result = (1 - t) * p0 + t * p1;

	return result;
};

//----------------------------------------------------------------------
// @brief �񎟂׃W�F�Ȑ�
// @param point: �_�̍��W
// @param time: ����
// @return �񎟂׃W�F�Ȑ��̍��W
//----------------------------------------------------------------------
Vector3D Spline::QuadraticSpline(const std::vector<Vector3D>& point, float time){
#ifdef _DEBUG
	if (point.size() < 3) {
		// �����ɕK�v�ȓ_������Ȃ�
		DebugErrar();
		return Vector3D();
	}
#endif

	// �ǂ̃Z�O�����g�ɑ����邩������
	float t = Math::Clamp(0.0f, 1.0f, time) * (point.size() - 2);
	int segment = static_cast<int>(t);
	t -= segment;
	

	Vector3D p0 = point[segment];
	Vector3D p1 = point[segment + 1];
	Vector3D p2 = point[segment + 2];

	// ���� : p(t) = (1 - t)^2 * p0 + 2(1 - t)t * p1 + t^2 * p2

	Vector3D result = (1 - t) * (1 - t) * p0 + 2 * (1 - t) * t * p1 + t * t * p2;

	return result;
};

//----------------------------------------------------------------------
// @brief �O���׃W�F�Ȑ�
// @param point: �_�̍��W
// @param time: ����
// @return �O���׃W�F�Ȑ��̍��W
//----------------------------------------------------------------------
Vector3D Spline::CubicSpline(const std::vector<Vector3D>& point, float time){
#ifdef _DEBUG
	if (point.size() < 4) {
		// �����ɕK�v�ȓ_������Ȃ�
		DebugErrar();
		return Vector3D();
	}
#endif

	// �ǂ̃Z�O�����g�ɑ����邩������
	float t = Math::Clamp(0.0f, 1.0f, time) * (point.size() - 3);
	int segment = static_cast<int>(t);
	t -= segment;

	Vector3D p0 = point[segment];
	Vector3D p1 = point[segment + 1];
	Vector3D p2 = point[segment + 2];
	Vector3D p3 = point[segment + 3];

	// ���� : p(t) = (1 - t)^3 * p0 + 3 * (1 - t)^2 * t * p1 + 3 * (1 - t)t^2 * p2 + t^3 * p3
	float t2 = t * t;
	float t3 = t * t * t;

	Vector3D result = (1 - t) * (1 - t) * (1 - t) * p0 + 3 * (1 - t) * (1 - t) * t * p1 + 3 * (1 - t) * t2 * p2 + t3 * p3;

	return result;
};

//----------------------------------------------------------------------
// @brief B�X�v���C���Ȑ��̊��֐�
// @param i: �C���f�b�N�X
// @param k: ����
// @param t: ����
// @param knots: �m�b�g�x�N�g��
// @return B�X�v���C���Ȑ��̊��֐�
//----------------------------------------------------------------------
float Spline::BSplineBase(int i, int k, float t, const std::vector<float>& knots){
	if (k == 1) {
		return (knots[i] <= t && t < knots[i + 1]) ? 1.0f : 0.0f;
	}
	else {
		float coef1 = (knots[i + k - 1] == knots[i]) ? 0.0f : (t - knots[i]) / (knots[i + k - 1] - knots[i]);
		float coef2 = (knots[i + k] == knots[i + 1]) ? 0.0f : (knots[i + k] - t) / (knots[i + k] - knots[i + 1]);

		return coef1 * BSplineBase(i, k - 1, t, knots) + coef2 * BSplineBase(i + 1, k - 1, t, knots);
	}
};

//----------------------------------------------------------------------
// @brief B�X�v���C���Ȑ�
// @param point: �_�̍��W
// @param k: ����
// @param time: ����
// @return B�X�v���C���Ȑ��̍��W
//----------------------------------------------------------------------
Vector3D Spline::BSpline(const std::vector<Vector3D>& point, int k, float time){
#ifdef _DEBUG
	if (point.size() < k) {
		// �����ɕK�v�ȓ_������Ȃ�
		DebugErrar();
		return Vector3D();
	}
#endif

	std::vector<float> knots(point.size() + k);
	int n = static_cast<int>(point.size()) - 1;

	for (int i = 0; i <= n + k; ++i) {
		if (i < k) {
			knots[i] = 0.0;
		}
		else if (i <= n) {
			knots[i] = static_cast<float>(i - k + 1) / (n - k + 2);
		}
		else {
			knots[i] = 1.0;
		}
	}

	float t = Math::Max(0.0, Math::Min(1.0, time)) * (n - k + 2);

	Vector3D result;
	for (int i = 0; i <= n; ++i) {
		float b = BSplineBase(i, k, t, knots);
		result += b * point[i];
	}

	return result;
};

//----------------------------------------------------------------------
// @brief Catmull-Rom�X�v���C���Ȑ�
// @param point: �_�̍��W
// @param time: ����
// @return Catmull-Rom�X�v���C���Ȑ��̍��W

Vector3D Spline::CatmullRomSpline(const std::vector<Vector3D>& point, float time){
#ifdef _DEBUG
	if (point.size() < 4) {
		// �����ɕK�v�ȓ_������Ȃ�
		DebugErrar();
		return Vector3D();
	}
#endif

	// �ǂ̃Z�O�����g�ɑ����邩������
	float t = Math::Clamp(0.0f, 1.0f, time) * (point.size() - 3);
	int segment = static_cast<int>(t);
	t -= segment;

	Vector3D p0 = point[segment];
	Vector3D p1 = point[segment + 1];
	Vector3D p2 = point[segment + 2];
	Vector3D p3 = point[segment + 3];

	//f(1) = -0.5t^3 + t^2 - 0.5t        �_P0�̉e������B�n�_�̐ڐ��ɉe����^����
	//f(2) = 1.5t^3 - 2.5t^2 + 1.0     �_P1�̉e������B�n�_�ƏI�_�̐ڐ��ɉe����^���� t=0�̎�P1��ʂ�
	//f(3) = -1.5t^3 + 2.0t^2 + 0.5t  �_P2�̉e������B�I�_�Ǝn�_�̐ڐ��ɉe����^���� t=1�̎�P2��ʂ�
	//f(4) = 0.5t^3 - 0.5t^2              �_P3�̉e������B�I�_�̐ڐ��ɉe����^����

	// ���� : p(t) = 0.5 * ((2 * p1) + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * t^2 + (-p0 + 3 * p1 - 3 * p2 + p3) * t^3)
	float t2 = t * t;
	float t3 = t * t * t;

	Vector3D result = 0.5f * ((2 * p1) + (p0 * -1 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * t2 + (p0 * -1 + 3 * p1 - 3 * p2 + p3) * t3);

	return result;
};