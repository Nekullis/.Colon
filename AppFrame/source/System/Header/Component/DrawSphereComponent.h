//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// ���̕`��p�R���|�[�l���g�N���X
//----------------------------------------------------------------------
#pragma once
#include "DrawComponent.h"
class DrawSphereComponent : public DrawComponent
{
public:
	DrawSphereComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawSphereComponent();
	void Update()override;
	//�Z�b�^�[
	void SetSphere(class Sphere* sphere) { m_Sphere = sphere; }
protected:
	class Sphere* m_Sphere;
};

