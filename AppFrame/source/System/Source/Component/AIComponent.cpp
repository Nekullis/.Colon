//----------------------------------------------------------------------
// @filename AICompornent.cpp
// @author: Fukuma Kyohei
// @explanation
// AIの状態を管理するコンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/AIComponent.h"
#include "../../Header/Component/AIState.h"
#include "../../Header/Component/Object/ObjectBase.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
AIComponent::AIComponent(ObjectBase* owner, int updateowder) :LogicComponent(owner, updateowder)
{
	m_Owner->AddComponent(this);
	mState = nullptr;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
AIComponent::~AIComponent()
{
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void AIComponent::Update()
{
	//現在の状態ならば更新する
	if (mState) { mState->Update();}
}

//----------------------------------------------------------------------
// @brief 状態の変更
// @param name 状態の名前
// @return なし
//----------------------------------------------------------------------
void AIComponent::ChangeState(const std::string& name)
{
	//現在の状態から出る
	if (mState) { mState->OnExit(); }
	//新しい状態を配列から探す
	auto itr = mStateMap.find(name);
	//状態が配列内から見つかった
	if (itr != mStateMap.end())
	{
		//状態を名前に紐付けられた別の状態に
		mState = itr->second;
		//新しい状態に入る
		mState->OnEnter();
	}
	//見つからなかった
	else { mState = nullptr; }
}

//----------------------------------------------------------------------
// @brief 状態の登録
// @param state 状態
// @return なし
//----------------------------------------------------------------------
void AIComponent::RegisterState(AIState* state)
{
	//名前と紐付けて配列内に入れる
	mStateMap.emplace(state->GetName(), state);
}
