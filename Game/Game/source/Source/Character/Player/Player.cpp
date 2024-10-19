//----------------------------------------------------------------------
// @filename Player.cpp
// @author: Fukuma Kyohei
// @explanation
// プレイヤークラス
// プレイヤーの処理全般クラス
//----------------------------------------------------------------------
#include "../../../Header/Character/Player/Player.h"
#include "appframe.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
Player::Player(ModeBase* game) :CharacterBase(game){
	m_Pos = { 0.0f,400.0f,0.0f };
	m_UseGravity = true;

	//球体の情報初期化
	m_Sphere = NEW Sphere();
	m_Sphere->r = 100.0f;
	m_Sphere->pos = m_Pos;

	//描画用コンポーネント初期化
	m_Draw = NEW DrawSphereComponent(this);

	//球体用当たり判定コンポーネント追加
	m_Col = NEW SphereColComponent(this);

	//カメラ初期化
	m_Camera = NEW CameraComponent(this);
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
Player::~Player(){
	delete m_Sphere;
	m_Sphere = nullptr;
	delete m_Camera;
	m_Camera = nullptr;
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void Player::Process(){
	CharacterBase::Process();
////////////////////////////////////////////////////////////////////////
//移動処理
////////////////////////////////////////////////////////////////////////
	m_Draw->SetSphere(m_Sphere);
	m_Col->SetCollision(m_Sphere);
}

//----------------------------------------------------------------------
// @brief 描画処理
// @return なし
//----------------------------------------------------------------------
void Player::Render(){
	CharacterBase::Render();
	if (m_Sphere->isHit) {
		m_UseGravity = false;
	}
	else {
		m_UseGravity = true;
	}
}

//----------------------------------------------------------------------
// @brief デバッグ表示
// @return なし
//----------------------------------------------------------------------
void Player::Debug(){
}
