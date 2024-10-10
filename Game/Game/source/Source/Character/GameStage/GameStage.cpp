//----------------------------------------------------------------------
// @filename GameStage.cpp
// @author: Fukuma Kyohei
// @explanation
// ゲームステージクラス
// ステージの処理全般クラス
//----------------------------------------------------------------------
#include "../Game/Game/source/Header/Character/GameStage/GameStage.h"
#include "appframe.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
GameStage::GameStage(ModeBase* game):CharacterBase(game){
	//位置初期化
	m_Pos = { 0.0f };
	//スケール設定
	m_Scale = Vector3D(100.0f, 10.0f, 100.0f);

	//入力用コンポーネント初期化
	m_Input = NEW InputComponent(this);

	//描画用コンポーネント初期化
	DrawMV1Component* Model = NEW DrawMV1Component(this);
	//描画用モデル読み込み
	Model->LoadPass("");

	//コリジョン用OBB初期化
	m_Collision = NEW OBB("stage", m_Pos, m_Scale);
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
GameStage::~GameStage(){
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void GameStage::Process(){
	//回転地の基底値を設定
	float Num = Math::DegToRad(45.0f);
	//ベクトルの増加量を設定
	float Vec_Dir = Math::DegToRad(3.0f);

	//パッドのアナログスティックのx数値を反映
	if (m_Input->GetPad()->GetLx() > 0) { m_Rotation.x += Vec_Dir; }
	else if(m_Input->GetPad()->GetLx() < 0) { m_Rotation.x -= Vec_Dir; }
	//規定値を超えないように設定
	m_Rotation.x = std::clamp(m_Rotation.x, -Num, Num);

	//パッドのアナログスティックのy数値を反映
	if (m_Input->GetPad()->GetLy() > 0) { m_Rotation.z += Vec_Dir; }
	else if (m_Input->GetPad()->GetLy() < 0) { m_Rotation.z -= Vec_Dir; }
	//規定値を超えないように設定
	m_Rotation.z = std::clamp(m_Rotation.z, -Num, Num);

	//OBBを回転させる
	m_Collision->Rotate(m_Rotation);
}