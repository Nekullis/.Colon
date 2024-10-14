//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBB描画クラス
//----------------------------------------------------------------------
#pragma once
#include "DrawComponent.h"
class DrawOBBComponent :public DrawComponent
{
public:
	DrawOBBComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawOBBComponent();
	//更新
	void Update()override;
	//セッター
	void SetOBB(class OBB* obb) { m_Obb = obb; }

protected:
	class OBB* m_Obb;
};

