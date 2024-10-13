//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBB�̓����蔻��ɗp����N���X
//----------------------------------------------------------------------
#pragma once
#include "CollisionComponent.h"
class OBBColComponent :public CollisionComponent
{
public:
	OBBColComponent(class ObjectBase* owner, int updateowder);
	virtual ~OBBColComponent();
	void Update()override;
	//�Z�b�^�[
	void SetOBB(class OBB* obb) { m_Collision = obb; }

protected:
	class OBB* m_Collision;

};

