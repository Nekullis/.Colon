//----------------------------------------------------------------------
// @filename SplineBox.h
// @author: Saito Ko
// @explanation
// �X�v���C���̋O���ɔz�u����I�u�W�F�N�g�̃N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class SplineBox : public ObjectBase
{
public:
	SplineBox();
	SplineBox(Vector3D pos);
	~SplineBox();
	bool Update()override;
	OBB* GetOBB() { return obb; }
protected:
	OBB* obb;
};