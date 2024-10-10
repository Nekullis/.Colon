//----------------------------------------------------------------------
// @filename ObjectBase.h
// @author: Fukuma Kyohei
// @explanation
// オブジェクトの親クラス
// オブジェクトはこのクラス、またはこの派生クラスから生成
//----------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "../../../Header/Math/Vector3D.h"
#include <vector>
#include <string>

class ObjectBase
{
public:
	//状態
	enum class State
	{
		ACTIVE,
		PAUSE,
		DEAD
	};
	ObjectBase(class ModeBase* game);
	virtual ~ObjectBase();
	virtual void Process();
	virtual void Render();
	virtual void Debug();
	//コンポーネント追加
	void AddComponent(class Component* component);
	//コンポーネント削除
	void RemoveComponent(class Component* component);
	//ゲッター
	virtual Vector3D GetPos()		const { return m_Pos; }
	virtual Vector3D GetRotation()	const { return m_Rotation; }
	virtual Vector3D GetScale()		const { return m_Scale; }
	virtual bool GetIsTarget()		const { return m_IsTargetting; }
	virtual State GetState()		const { return m_State; }
	class ModeGame* GetGame()		const { return m_Game; }
	std::vector<class Component*> GetComponent() const{ return m_Components; }
	//セッター
	void SetPos(const Vector3D& pos) { m_Pos = pos; }
	void SetRotation(Vector3D rot) { m_Rotation = rot; }
	void SetScale(Vector3D scale) { m_Scale = scale; }
	void SetState(State state) { m_State = state; }
protected:
	//位置
	Vector3D m_Pos;
	//角度
	Vector3D m_Rotation;
	//スケール
	Vector3D m_Scale;
	//状態
	State m_State;
	//ターゲット可能か
	bool m_IsTargetting;
	//コンポーネント
	std::vector<class Component*> m_Components;
	class ModeGame* m_Game;

};

