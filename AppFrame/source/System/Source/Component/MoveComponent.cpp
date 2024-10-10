//----------------------------------------------------------------------
// @filename MoveComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// キャラクターの移動を制御するコンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/MoveComponent.h"
#include <Math.h>
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
MoveComponent::MoveComponent(ObjectBase* owner, int updateowder) :LogicComponent(owner, updateowder)
{
	m_Owner->AddComponent(this);
	mAngularSpeed = 0.0f;
	mForwardSpeed = 0.0f;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
MoveComponent::~MoveComponent()
{

}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void MoveComponent::Update()
{
	Component::Update();
}
