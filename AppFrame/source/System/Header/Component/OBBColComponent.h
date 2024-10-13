//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBBの当たり判定に用いるクラス
//----------------------------------------------------------------------
#pragma once
#include "CollisionComponent.h"
class OBBColComponent :public CollisionComponent
{
public:
	OBBColComponent(class ObjectBase* owner, int updateowder);
	virtual ~OBBColComponent();
	void Update()override;
	//セッター
	void SetOBB(class OBB* obb) { m_Collision = obb; }

protected:
	class OBB* m_Collision;

};

