//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// 球の描画用コンポーネントクラス
//----------------------------------------------------------------------
#pragma once
#include "DrawComponent.h"
class DrawSphereComponent : public DrawComponent
{
public:
	DrawSphereComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawSphereComponent();
	void Update()override;
	//セッター
	void SetSphere(class Sphere* sphere) { m_Sphere = sphere; }
protected:
	class Sphere* m_Sphere;
};

