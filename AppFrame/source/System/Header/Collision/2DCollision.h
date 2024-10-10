//----------------------------------------------------------------------
// @filename 2DCollision.h
// @author: Saito Ko
// @explanation
// 2D�Ŏg�p���铖���蔻����s���N���X
//----------------------------------------------------------------------
#pragma once
#include <math.h>
#include "../../Header/Collision/MyStructure.h"
#include "../Math/mymath.h"
#include "dxlib.h"

class Collision2D
{
public:

	// �����蔻��p�B2��box�������������𔻒�
	// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
	static bool IsHitBox(
		float x1, float y1, float w1, float h1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
		float x2, float y2, float w2, float h2		// �ӂ��߂�box ����(x,y), �傫��w,h
	);

	static bool IsHitBox(
		MYRECT rect1,		// �ЂƂ߂�MYRECT ����(x,y), �傫��w,h
		MYRECT rect2		// �ӂ��߂�MYRECT ����(x,y), �傫��w,h
	);

	// �����蔻��p�B2�̉~�������������𔻒�
	// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
	static bool IsHitCircle(
		float x1, float y1, float r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
		float x2, float y2, float r2		// �ӂ��߂�circle ���S(x,y), ���ar
	);

	static bool IsHitCircleAndBox(float box_x, float  box_y, float  box_w, float  box_h, float circle_x, float circle_y, float circle_r);   //�~�Ǝl�p�̓����蔻��

};