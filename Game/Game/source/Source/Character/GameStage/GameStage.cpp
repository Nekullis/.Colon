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
	m_Pos = Vector3D(0.0f, 0.0f, 0.0f);
	//スケール設定
	m_Scale = Vector3D(1000.0f, 100.0f, 1000.0f);

	//入力用コンポーネント初期化
	m_Input = NEW InputComponent(this);

	////描画用コンポーネント初期化
	//DrawMV1Component* Model = NEW DrawMV1Component(this);
	////描画用モデル読み込み
	//Model->LoadPass("");

	//OBB情報初期化
	m_Obb = NEW OBB("stage", m_Pos, m_Scale);

	//OBB描画コンポーネント初期化
	m_Draw = NEW DrawOBBComponent(this);

	//OBB用当たり判定コンポーネント初期化
	m_Col = NEW OBBColComponent(this);
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
GameStage::~GameStage(){
	delete m_Obb;
	m_Obb = nullptr;
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void GameStage::Process(){
	CharacterBase::Process();
	//回転値の規定値を設定
	float Control_Value = Math::DegToRad(30.0f);
	//ベクトルの増加量を設定
	float Vec_Dir = Math::DegToRad(1.0f);

	if (m_Input->GetPad()->IsInputStickLeft()){
		//パッドのアナログスティックのx数値を反映
		if (m_Input->GetPad()->GetLx() > 0) { m_Rotation.z -= Vec_Dir; }
		else if (m_Input->GetPad()->GetLx() < 0) { m_Rotation.z += Vec_Dir; }
		//規定値を超えないように設定
		m_Rotation.z = std::clamp(m_Rotation.z, -Control_Value, Control_Value);

		//パッドのアナログスティックのy数値を反映
		if (m_Input->GetPad()->GetLy() > 0) { m_Rotation.x += Vec_Dir; }
		else if (m_Input->GetPad()->GetLy() < 0) { m_Rotation.x -= Vec_Dir; }
		//規定値を超えないように設定
		m_Rotation.x = std::clamp(m_Rotation.x, -Control_Value, Control_Value);
	}

	//OBBを回転させる
	m_Obb->Rotate(m_Rotation);
	m_Draw->SetOBB(m_Obb);
	m_Col->SetCollision(m_Obb);
}