//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// MV1モデル描画用コンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/DrawMV1Component.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawMV1Component::DrawMV1Component(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder){
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawMV1Component::~DrawMV1Component(){
	MV1DeleteModel(m_Handle);
}

//----------------------------------------------------------------------
// @brief モデルの読み込み
// @param pass モデルのパス
// @return なし
//----------------------------------------------------------------------
void DrawMV1Component::LoadPass(const char* pass){
	m_Pass = pass;
	m_Handle = MV1LoadModel((const TCHAR*)(m_Pass));
}

//----------------------------------------------------------------------
// @brief モデルの設定・描画
// @return なし
//----------------------------------------------------------------------
void DrawMV1Component::Update(){
	//コンポーネント更新処理
	DrawComponent::Update();
	//モデルの位置設定
	MV1SetPosition(m_Handle, m_Owner->GetPos().toVECTOR());
	//モデルのサイズ設定
	MV1SetScale(m_Handle, m_Owner->GetScale().toVECTOR());
	//向き設定
	MV1SetRotationXYZ(m_Handle, m_Owner->GetRotation().toVECTOR());
	//描画処理
	MV1DrawModel(m_Handle);
}


