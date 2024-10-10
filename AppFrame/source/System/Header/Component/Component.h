//----------------------------------------------------------------------
// @filename Component.h
// @author: Fukuma Kyohei
// @explanation
// コンポーネント(構成要素)の親クラス
//----------------------------------------------------------------------
#pragma once
#include <string>
class Component
{
public:
	Component(class ObjectBase* owner, int updateowder = 100);
	virtual ~Component();
	//更新
	virtual void Update();
	//ゲッター
	int GetUpdateOwder() const { return m_UpdateOwder; }
	class ObjectBase* GetOwner() { return m_Owner; }
protected:
	//所有オブジェクト
	class ObjectBase* m_Owner;
	//更新順序
	int m_UpdateOwder;
};

