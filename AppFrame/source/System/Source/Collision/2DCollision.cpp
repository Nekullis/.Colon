//----------------------------------------------------------------------
// @filename 2DCollision.cpp
// @author: Saito Ko
// @explanation
// 2Dで使用する当たり判定を行うクラス
//----------------------------------------------------------------------
#include "../../Header/Collision/2DCollision.h"
#include "dxlib.h"

//--------------------------------------------------------
// ＠breif 2つのboxが当たったかを判定
// @param x1, y1, w1, h1		// ひとつめのbox 左上(x,y), 大きさw,h
// @param x2, y2, w2, h2		// ふたつめのbox 左上(x,y), 大きさw,h
// @return 当たっていたらtrue, 当たっていなかったらfalseを返す
//--------------------------------------------------------
bool Collision2D::IsHitBox(
	float x1, float y1, float w1, float h1,		// ひとつめのbox 左上(x,y), 大きさw,h
	float x2, float y2, float w2, float h2		// ふたつめのbox 左上(x,y), 大きさw,h
) {
	if (x1 < x2 + w2 && x2 < x1 + w1		// x方向の判定
		&& y1 < y2 + h2 && y2 < y1 + h1		// y方向の判定
		)
	{
		// 2つのboxは当たっている
		return true;
	}

	// 2つのboxは当たっていない
	return false;
}

//--------------------------------------------------------
// ＠breif 2つのboxが当たったかを判定
// @param rect1		// ひとつめのbox 左上(x,y), 大きさw,h
// @param rect2		// ふたつめのbox 左上(x,y), 大きさw,h
// @return 当たっていたらtrue, 当たっていなかったらfalseを返す
//--------------------------------------------------------
bool Collision2D::IsHitBox(MYRECT rect1, MYRECT rect2) {
	return IsHitBox(rect1.x, rect1.y, rect1.w, rect1.h, rect2.x, rect2.y, rect2.w, rect2.h);
};

//--------------------------------------------------------
// @breif 2つの円が当たったかを判定
// @param x1, y1, r1		// ひとつめのcircle 中心(x,y), 半径r
// @param x2, y2, r2		// ふたつめのcircle 中心(x,y), 半径r
// @return 当たっていたらtrue, 当たっていなかったらfalseを返す
// --------------------------------------------------------
bool Collision2D::IsHitCircle(
	float x1, float y1, float r1,		// ひとつめのcircle 中心(x,y), 半径r
	float x2, float y2, float r2		// ふたつめのcircle 中心(x,y), 半径r
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
// @breif 円と矩形が当たったかを判定
// @param box_x, box_y, box_w, box_h		// box 左上(x,y), 大きさw,h
// @param circle_x, circle_y, circle_r		    // circle 中心(x,y), 半径r
// @return 当たっていたらtrue, 当たっていなかったらfalseを返す
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

		if (circle_x < box_x) { //左
			if (circle_y < box_y) {  //左上
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}
			}

			if (box_y + box_h < circle_y) {  //左上
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}
			}
		}

		if (circle_x > box_x) { //右
			if (box_y > circle_y) {  //右上
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}

			}
			if (box_y + box_h < circle_y) {  //右上
				if (PythagoreanLeft > PythagoreanRight) {
					hitfrag = false;
				}

			}

		}
	}
	return hitfrag;
}