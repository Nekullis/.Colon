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
				//当たり判定の種類
				enum class HITTYPE_3D :int{
					//初期化値
					NONE = 0,
					//球と球
					SPHERE_TO_SPHERE,
					//球とOBB
					SPHERE_TO_OBB,
					//OBBとOBB
					OBB_TO_OBB,
					//カプセルとカプセル
					CAPSULE_TO_CAPSULE
				}
				//ヒットフラグ初期化
				Hit = HITTYPE_3D::NONE;
				//2つのオブジェクトの最短距離初期化
				float dis = 0.0f;
				//	当たり判定タイプがOBBと球の場合
				if ((*itr)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*jtr)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {
					Hit = HITTYPE_3D::SPHERE_TO_OBB;
				}
				switch (Hit)
				{
				case HITTYPE_3D::NONE:
					break;
				case HITTYPE_3D::SPHERE_TO_SPHERE:
					break;
				case HITTYPE_3D::SPHERE_TO_OBB:
					break;
				case HITTYPE_3D::OBB_TO_OBB:
					break;
				case HITTYPE_3D::CAPSULE_TO_CAPSULE:
					break;
				default:
					break;
				}
			}
		}
	}
}