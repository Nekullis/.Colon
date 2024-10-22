//----------------------------------------------------------------------
// @filename CameraComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// ゲーム内のカメラ処理全般制御するコンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/CameraComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"
#include "../../Header/Collision/3DCollision.h"

CameraComponent* CameraComponent::m_CameraInstance = nullptr;

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
CameraComponent::CameraComponent(ObjectBase* owner, int updateowder) : LogicComponent(owner, updateowder)
{
	m_CameraInstance = this;
	//注視点初期化
	m_Target = { 0 };
	//位置初期化
	m_Pos = { 0 };
	m_Dir = Vector3D(0, m_Owner->GetRotation().y, 0);
	//最短描画距離初期化
	m_Near = 20.0f;
	//最長描画距離初期化
	m_Far = 50000.0f;
	//距離値初期化
	m_Distance = -700.0f;
	//ばね定数
	m_Spring = 0.1f;
	//減衰定数
	m_DampFactor = 0.8f;
	m_CurrentPos = m_Pos;
	m_CurrentVelocity;
	//ゲームパッドの取得
	m_Pad = XInput::GetInstance();
	m_Owner->AddComponent(this);
}
//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
CameraComponent::~CameraComponent()
{
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void CameraComponent::Update()
{
	Component::Update();
	//位置設定
	Vector3D pos;
	//パッド入力で角度を代入
	if (m_Pad->GetRx() < 0) { m_Dir.y -= 0.05f; }
	if (m_Pad->GetRx() > 0) { m_Dir.y += 0.05f; }
	//注視点設定
	Vector3D target;
	//カメラ位置をプレーヤー位置に球型座標系から変化した座標系を足した座標にする
	pos = m_Owner->GetPos() + Collision3D::ConvertToCartesian(m_Dir, m_Distance);
	//後頭部より少し高めの位置にする
	pos.y += 100.0f;
	target = Vector3D(m_Owner->GetPos()); 
	m_Pos = pos;
	//ばね力計算
	Vector3D springforce = -m_Spring * (m_CurrentPos - pos);
	//減衰力計算
	Vector3D dampforce = -m_DampFactor * m_CurrentVelocity;
	//総合力を計算している
	Vector3D force = springforce + dampforce;
	Vector3D accseler = force;
	//速度更新
	m_CurrentVelocity += accseler;
	//位置更新
	m_CurrentPos += m_CurrentVelocity;
	m_Pos = m_CurrentPos;
	//カメラ描写の最短距離、最長距離を設定する
	SetCameraNearFar(m_Near, m_Far);
	//カメラの位置と注視点を反映する
	SetCameraPositionAndTarget_UpVecY(m_CurrentPos.toVECTOR(), target.toVECTOR());
}




