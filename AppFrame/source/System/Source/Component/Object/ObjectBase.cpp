//----------------------------------------------------------------------
// @filename ObjectBase.cpp
// @author: Fukuma Kyohei
// @explanation
// オブジェクトの親クラス
// オブジェクトはこのクラス、またはこの派生クラスから生成
//----------------------------------------------------------------------
#include "../../../Header/Component/Object/ObjectBase.h"
#include "../../../Header/Component/LogicComponent.h"
#include "../../../Header/Component/DrawComponent.h"
#include <algorithm>

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
ObjectBase::ObjectBase(ModeBase* game)
{
	//位置
	m_Pos = { 0 };
	//角度
	m_Rotation = { 0 };
	//スケール
	m_Scale = { 0 };
	m_IsTargetting = false;

	m_Game = nullptr;

	m_State = State::ACTIVE;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
ObjectBase::~ObjectBase()
{

}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void ObjectBase::Process()
{
	for(auto&& comp : m_Components)
	{
		comp->Update();
	}
}

//----------------------------------------------------------------------
// @brief 描画処理
// @return なし
//----------------------------------------------------------------------
void ObjectBase::Render()
{
#if _DEBUG
	Debug();
#endif
}

//----------------------------------------------------------------------
// @brief デバッグ表示
// @return なし
//----------------------------------------------------------------------
void ObjectBase::Debug()
{

}

//----------------------------------------------------------------------
// @brief コンポーネントの追加
// @param component コンポーネント
// @return なし
//----------------------------------------------------------------------
void ObjectBase::AddComponent(Component* component)
{
	//コンテナに格納する
	m_Components.push_back(component);
	//格納したコンポーネントの並び替え
	std::sort(m_Components.begin(), m_Components.end(), [](Component* a, Component* b) {return a->GetUpdateOwder() < b->GetUpdateOwder(); });
	
}

//----------------------------------------------------------------------
// @brief コンポーネントの削除
// @param component コンポーネント
// @return なし
//----------------------------------------------------------------------
void ObjectBase::RemoveComponent(Component* component)
{
	//条件に合うコンポーネントを探す
	auto itr = std::find(m_Components.begin(), m_Components.end(), component);
	//探したコンポーネントの消去
	if (itr != m_Components.end()) { m_Components.erase(itr); }
}

