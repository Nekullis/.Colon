//----------------------------------------------------------------------
// @filename AIState.h
// @author: Fukuma Kyohei
// @explanation
// AIの状態を管理するコンポーネント
//----------------------------------------------------------------------
#pragma once
#include <memory>
//AIの状態の規定クラス
class AIState
{
public:
	AIState(class AIComponent* owner);
	virtual ~AIState();
	//更新
	virtual void Update();
	//遷移に入る際の処理
	virtual void OnEnter();
	//遷移から出る際の処理
	virtual void OnExit();
	//名前取得
	virtual const char* GetName()const { return ""; }
protected:
	//使うコンポーネント
	class AIComponent* mOwner;
};

