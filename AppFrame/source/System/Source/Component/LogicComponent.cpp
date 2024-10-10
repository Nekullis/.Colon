#include "../AppFrame/source/System/Header/Component/LogicComponent.h"
#include "../AppFrame/source/System/Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
LogicComponent::LogicComponent(ObjectBase* owner, int updateowder) :Component(owner, updateowder) {
	m_Owner->AddComponent(this);
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
LogicComponent::~LogicComponent(){
}

//----------------------------------------------------------------------
// @brief モデルの設定・描画
// @return なし
//----------------------------------------------------------------------
void LogicComponent::Update(){
	Component::Update();
}
