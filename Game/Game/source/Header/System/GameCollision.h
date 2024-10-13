//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// ゲーム内のオブジェクト判定管理クラス
// 当たり判定の制御全般を扱うクラス
//----------------------------------------------------------------------
#pragma once
#include <vector>
class GameCollision
{
public:
	GameCollision();
	~GameCollision();
	void Process();
	//コリジョン追加
	void AddCollision(class CollisionComponent* col);
	//ゲッター
	std::vector<class CollisionComponent*> GetCollisionList() { return m_CollisionList; }
protected:
	//衝突判定用コンポーネントコンテナ
	std::vector<class CollisionComponent*> m_CollisionList;
};

