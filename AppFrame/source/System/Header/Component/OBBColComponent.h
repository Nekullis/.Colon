//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBB‚Ì“–‚½‚è”»’è‚É—p‚¢‚éƒNƒ‰ƒX
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

