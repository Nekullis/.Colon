//----------------------------------------------------------------------
// @filename Draw3D.h
// @author: Saito Ko 
// @explanation
// 3D空間でのコリジョンや形を描画するためのクラス
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "../Math/Vector3D.h"
#include <math.h>
class Draw3D
{
public:
	static bool PositionDraw3D(const Vector3D& pos);
	static bool RectangleFootDraw3D(const Vector3D& pos, float w, float d);
	static bool BoxCollisionDraw3D(const Vector3D& pos,float w, float h, float d, float direction);
	static bool CollisionToBillBoradDraw(const Vector3D& pos, float wide, float height, float depth,float direction_z);
	static bool CircleFootDraw3D(const Vector3D& pos,float r);
	static bool CircleCollisionDraw(const Vector3D& pos, float r,float h,bool flag);
};

