//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// ‹…‚Ì“–‚½‚è”»’è‚É—p‚¢‚éƒNƒ‰ƒX
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

