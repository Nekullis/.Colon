//----------------------------------------------------------------------
// @filename DrawBillboardComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// ビルボードを描画するためのコンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/DrawBillboardComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawBillboardComponent::DrawBillboardComponent(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder)
{
	m_Owner = owner;
	mHandle = -1;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawBillboardComponent::~DrawBillboardComponent()
{

}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void DrawBillboardComponent::Update()
{
	Component::Update();
	DrawBillboard3D(m_Owner->GetPos().toVECTOR(), 0.5f, 0.5f, 1.0f, 0.0f, mHandle, true);
}
