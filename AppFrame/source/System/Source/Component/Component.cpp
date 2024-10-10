//----------------------------------------------------------------------
// @filename Component.cpp
// @author: Fukuma Kyohei
// @explanation
// コンポーネント(構成要素)の親クラス
//----------------------------------------------------------------------
#include "../../Header/Component/Component.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
Component::Component(ObjectBase* owner, int updateowder)
{
	m_Owner = owner;
	m_UpdateOwder = updateowder;
	m_Owner->AddComponent(this);
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
Component::~Component()
{
	m_Owner->RemoveComponent(this);
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void Component::Update()
{

}
