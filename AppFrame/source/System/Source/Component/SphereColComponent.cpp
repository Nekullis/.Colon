//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// 球の当たり判定に用いるクラス
//----------------------------------------------------------------------
#include "../AppFrame/source/System/Header/Component/SphereColComponent.h"
#include "../../AppFrame/source/System/Header/Component/Object/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
SphereColComponent::SphereColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder){
	m_Col = new Sphere();
	mType = COLLISIONTYPE::SPHERE;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
SphereColComponent::~SphereColComponent(){
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void SphereColComponent::Update(){
	CollisionComponent::Update();
}
