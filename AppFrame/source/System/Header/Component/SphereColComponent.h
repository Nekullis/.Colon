//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// ���̓����蔻��ɗp����N���X
//----------------------------------------------------------------------
#pragma once
#include "CollisionComponent.h"
class SphereColComponent :public CollisionComponent
{
public:
	SphereColComponent(ObjectBase* owner, int updateowder);
	virtual ~SphereColComponent();
	void Update()override;
};

