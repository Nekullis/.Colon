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
	OBBColComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~OBBColComponent();
	void Update()override;
};

