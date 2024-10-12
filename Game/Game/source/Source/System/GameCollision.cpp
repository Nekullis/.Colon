//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// ゲーム内のオブジェクト判定管理クラス
// 当たり判定の制御全般を扱うクラス
//----------------------------------------------------------------------
#include "../Game/Game/source/Header/System/GameCollision.h"
#include "appframe.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
GameCollision::GameCollision(){
	//コンテナ初期化
	m_CollisionList.clear();
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
GameCollision::~GameCollision(){
	m_CollisionList.clear();
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @param col 衝突判定用コンポーネント
// @return なし
//----------------------------------------------------------------------
void GameCollision::AddCollision(CollisionComponent* col){
	m_CollisionList.push_back(col);
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void GameCollision::Process(){
	//コンテナサイズが0でないのなら
	if (m_CollisionList.size() > 0) {
		//2重if文で全検索
		for (auto itr = m_CollisionList.begin(); itr != m_CollisionList.end(); itr++) {
			for (auto jtr = itr + 1; jtr != m_CollisionList.end(); jtr++) {
				//同じものなら再検索
				if (itr == jtr)continue;
				//	OBBと球の当たり判定の場合
				if ((*itr)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*jtr)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {

				}
			}
		}
	}
}