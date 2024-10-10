//----------------------------------------------------------------------
// @filename DrawBillboardComponent.h
// @author: Fukuma Kyohei
// @explanation
// ビルボードを描画するためのコンポーネント
//----------------------------------------------------------------------
#pragma once
#include "DrawComponent.h"
class DrawBillboardComponent : public DrawComponent
{
public:
	DrawBillboardComponent(class ObjectBase* owner, int updateowder = 150);
	virtual ~DrawBillboardComponent();
	void Update()override;
	//セッター
	void SetHandle(int handle) { mHandle = handle; }
protected:
	int mHandle;
};

