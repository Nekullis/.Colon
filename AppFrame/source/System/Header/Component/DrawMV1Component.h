//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// MV1���f���`��p�R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "../Component/DrawComponent.h"
#include "../Math/Vector3D.h"

class DrawMV1Component :public DrawComponent
{
public:
	DrawMV1Component(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawMV1Component();
	//�X�V
	void Update()override;
	void LoadPass(const char* pass)override;
};

