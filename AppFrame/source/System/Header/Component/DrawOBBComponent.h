//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBB�`��N���X
//----------------------------------------------------------------------
#pragma once
#include "DrawComponent.h"
class DrawOBBComponent :public DrawComponent
{
public:
	DrawOBBComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawOBBComponent();
	//�X�V
	void Update()override;
	void LoadPass(const char* pass)override;
};

