//----------------------------------------------------------------------
// @filename IK.h
// @author: Kawai Daisuke
// @explanation
// �t�^���w��p����IK�̌v�Z���s���N���X
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/System/Header/Math/Vector3D.h"
class IK
{
public :
	 // 1�{�[��IK
	static void OneBoneIK(Vector3D targetPos, Vector3D& bonePos, Vector3D& boneDir);

	// 2�{�[��IK
	static void TwoBoneIK(Vector3D targetPos, Vector3D& joint1Pos, Vector3D& joint1Dir,
				Vector3D& joint2Pos, Vector3D& joint2Dir, float bone1Length, float bone2Length);
};

