//----------------------------------------------------------------------
// @filename 2DCollision.cpp
// @author: Saito Ko
// @explanation
// 2D�Ŏg�p���铖���蔻����s���N���X
//----------------------------------------------------------------------
#include "../../Header/Collision/2DCollision.h"
#include "dxlib.h"

//--------------------------------------------------------
// ��breif 2��box�������������𔻒�
// @param x1, y1, w1, h1		// �ЂƂ߂�box ����(x,y), �傫��w,h
// @param x2, y2, w2, h2		// �ӂ��߂�box ����(x,y), �傫��w,h
// @return �������Ă�����true, �������Ă��Ȃ�������false��Ԃ�
//--------------------------------------------------------
bool Collision2D::IsHitBox(
	float x1, float y1, float w1, float h1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
	float x2, float y2, float w2, float h2		// �ӂ��߂�box ����(x,y), �傫��w,h
) {
	if (x1 < x2 + w2 && x2 < x1 + w1		// x�����̔���
		&& y1 < y2 + h2 && y2 < y1 + h1		// y�����̔���
		)
	{
		// 2��box�͓������Ă���
		return true;
	}

	// 2��box�͓������Ă��Ȃ�
	return false;
}

//--------------------------------------------------------
// ��breif 2��box�������������𔻒�
// @param rect1		// �ЂƂ߂�box ����(x,y), �傫��w,h
// @param rect2		// �ӂ��߂�box ����(x,y), �傫��w,h
// @return �������Ă�����true, �������Ă��Ȃ�������false��Ԃ�
//--------------------------------------------------------
bool Collision2D::IsHitBox(MYRECT rect1, MYRECT rect2) {
	return IsHitBox(rect1.x, rect1.y, rect1.w, rect1.h, rect2.x, rect2.y, rect2.w, rect2.h);
};

//--------------------------------------------------------
// @breif 2�̉~�������������𔻒�
// @param x1, y1, r1		// �ЂƂ߂�circle ���S(x,y), ���ar
// @param x2, y2, r2		// �ӂ��߂�circle ���S(x,y), ���ar
// @return �������Ă�����true, �������Ă��Ȃ�������false��Ԃ�
// --------------------------------------------------------
bool Collision2D::IsHitCircle(
	float x1, float y1, float r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
	float x2, float y2, float r2		// �ӂ��߂�circle ���S(x,y), ���ar
) {
	float w, h, r;
	w = x1 - x2;
	h = y1 - y2;
	r = r1 + r2;
	if (r * r > w * w + h * h) {
		return true;
	}
	return false;
}

//--------------------------------------------------------
// @breif �~�Ƌ�`�������������𔻒�
// @param box_x, box_y, box_w, box_h		// box ����(x,y), �傫��w,h
// @param circle_x, circle_y, circle_r		    // circle ���S(x,y), ���ar
// @return �������Ă�����true, �������Ă��Ȃ�������false��Ԃ�
// --------------------------------------------------------
bool Collision2D::IsHitCircleAndBox(float box_x, float  box_y, float  box_w, float  box_h, float circle_x, float circle_y, float circle_r) {
	int hitfrag = false;

	if ((circle_x > box_x - circle_r)
		&& (circle_y > box_y - circle_r)
		&& (circle_x < box_x + box_w + circle_r)
		&& (circle_y < box_y + box_h + circle_r)) {

		hitfrag = true;
		float PythagoreanRight = circle_r * circle_r;
		float PythagoreanLeft = ((box_x - circle_x) * (box_x - circle_x)) + ((box_y - circle_y) * (box_y - circle_y));

		if (circle_x < box_x) { //��
			if (circle_y < box_y) {  //����
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}
			}

			if (box_y + box_h < circle_y) {  //����
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}
			}
		}

		if (circle_x > box_x) { //�E
			if (box_y > circle_y) {  //�E��
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}

			}
			if (box_y + box_h < circle_y) {  //�E��
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}

			}

		}
	}
	return hitfrag;
}