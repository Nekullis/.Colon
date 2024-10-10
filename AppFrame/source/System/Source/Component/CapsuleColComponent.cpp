//----------------------------------------------------------------------
// @filename CameraComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// カプセル型の衝突判定用コンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/CapsuleColComponent.h"

CapsuleColComponent* CapsuleColComponent::capInstance = nullptr;

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
CapsuleColComponent::CapsuleColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder)
{
	capInstance = this;
	//タイプ初期化
	mType = COLLISIONTYPE::CAPSULE;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// ＠return なし
//----------------------------------------------------------------------
CapsuleColComponent::~CapsuleColComponent()
{

}
//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void CapsuleColComponent::Update()
{
	CollisionComponent::Update();
}
