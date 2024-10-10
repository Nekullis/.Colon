//----------------------------------------------------------------------
// @filename DrawBillboardComponent.h
// @author: Fukuma Kyohei
// @explanation
// �r���{�[�h��`�悷�邽�߂̃R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "DrawComponent.h"
class DrawBillboardComponent : public DrawComponent
{
public:
	DrawBillboardComponent(class ObjectBase* owner, int updateowder = 150);
	virtual ~DrawBillboardComponent();
	void Update()override;
	//�Z�b�^�[
	void SetHandle(int handle) { mHandle = handle; }
protected:
	int mHandle;
};

