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
		for (auto itr_i = m_CollisionList.begin(); itr_i != m_CollisionList.end(); itr_i++) {
			for (auto itr_j = itr_i + 1; itr_j != m_CollisionList.end(); itr_j++) {
				//同じものなら再検索
				if (itr_i == itr_j)continue; 
				//	当たり判定タイプがOBBと球の場合
				if ((*itr_i)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*itr_j)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {
					//各オブジェクトの当たり判定を取得
					OBB* Obb = dynamic_cast<OBB*>((*itr_i)->GetCollision());
					Sphere* Sph = dynamic_cast<Sphere*>((*itr_j)->GetCollision());
					//最近点用の変数初期化
					Vector3D Dist =  Vector3D(0.0f, 0.0f, 0.0f);
					//オブジェクト同士が当たっていた場合
					if (Collision3D::OBBSphereCol(*Obb, *Sph, &Dist)) {
						(*itr_j)->GetCollision()->isHit = true;
						//OBBの面に沿った方向ベクトルを取得
						Vector3D Vec = Obb->dir_vec[0] + Obb->dir_vec[2];
						//正規化
						Vec = Vec.Normalize();
						//OBBの面に沿った方向ベクトルの外積を求める
						Vector3D VecCloss = Vec.Cross(Obb->dir_vec[2]);
						//法線ベクトルを求める
						VecCloss = VecCloss.Normalize();
						if (fabs(VecCloss.y) > 0.999f) {
							float Len = Dist.Len();
							Vector3D Pos = Dist.Normalize() * Len;
							(*itr_j)->GetOwner()->SetPos(Pos);
							return;
						}
						//重力ベクトルを設定
						Vector3D Gravity = Vector3D(0.0f, -9.8f, 0.0f);
						//方向ベクトルに重力ベクトルをスケーリングする
						Vector3D GravityImpactsObb = VecCloss * (Gravity.Dot(VecCloss));
						GravityImpactsObb = Gravity - GravityImpactsObb;
						//オブジェクトの位置に反映
						(*itr_j)->GetOwner()->SetPos((*itr_j)->GetOwner()->GetPos() + GravityImpactsObb);
					}
					else {
						(*itr_j)->GetCollision()->isHit = false;
					}
				}
			}
		}
	}
}