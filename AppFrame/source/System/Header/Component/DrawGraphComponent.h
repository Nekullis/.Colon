#pragma once
#include "DrawComponent.h"
class DrawGraphComponent : public DrawComponent
{
public:
	DrawGraphComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawGraphComponent();
	void Update()override;
	void LoadPass(const char* pass)override;
};

