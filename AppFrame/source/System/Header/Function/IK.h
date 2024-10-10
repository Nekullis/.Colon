//----------------------------------------------------------------------
// @filename IK.h
// @author: Kawai Daisuke
// @explanation
// 逆運動学を用いたIKの計算を行うクラス
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/System/Header/Math/Vector3D.h"
class IK
{
public :
	 // 1ボーンIK
	static void OneBoneIK(Vector3D targetPos, Vector3D& bonePos, Vector3D& boneDir);

	// 2ボーンIK
	static void TwoBoneIK(Vector3D targetPos, Vector3D& joint1Pos, Vector3D& joint1Dir,
				Vector3D& joint2Pos, Vector3D& joint2Dir, float bone1Length, float bone2Length);
};

