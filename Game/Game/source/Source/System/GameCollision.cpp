//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// ゲーム内のオブジェクト判定管理クラス
// 当たり判定の制御全般を扱うクラス
//----------------------------------------------------------------------
#include "../Game/Game/source/Header/System/GameCollision.h"
#include"../Game/Game/source/Header/Character/CharacterBase.h"
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
// @brief 当たり判定コンポーネント追加
// @param chara オブジェクト
// @return なし
//----------------------------------------------------------------------
void GameCollision::AddCollision(CharacterBase* chara){
	//コンポーネント全検索
	for (auto&& component : chara->GetComponent()) {
		//当たり判定用のコンポーネントだけを別コンテナに
		if (component->GetUpdateOwder() == COL_OWDER) {
			CollisionComponent* col = static_cast<CollisionComponent*>(component);
			m_CollisionList.push_back(col);
		}
	}
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
				//	当たり判定タイプがOBBと球の場合
				if ((*itr)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*jtr)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {
					OBB* Obb = static_cast<OBB*>((*itr)->GetCollision());
					Sphere* Sph = static_cast<Sphere*>((*jtr)->GetCollision());
					if (Collision3D::OBBSphereCol(*Obb, *Sph)) {
						int i = 0;
					}
				}
			}
		}
	}
}