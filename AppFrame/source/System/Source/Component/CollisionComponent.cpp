//----------------------------------------------------------------------
// @filename CollisionComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// 衝突判定用コンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/CollisionComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"
#include "../../Header/Collision/MyStructure.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
CollisionComponent::CollisionComponent(ObjectBase* owner, int updateowder) :LogicComponent(owner, updateowder)
{
	m_Col = nullptr;
	m_Owner = owner;
	mManager = nullptr;
	mType = COLLISIONTYPE::NONE;
	mRadius = 0;
	mLineSeg = 0;
	mGroup = COLLISIONGROUP::NONE;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
CollisionComponent::~CollisionComponent()
{
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void CollisionComponent::Update()
{
	mPos = m_Owner->GetPos();
	m_Col->pos = mPos;
}
