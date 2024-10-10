//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// 画像描画用コンポーネント
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawGraphComponent.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawGraphComponent::DrawGraphComponent(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder) {
	
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawGraphComponent::~DrawGraphComponent(){
	DeleteGraph(m_Handle);
}

//----------------------------------------------------------------------
// @brief モデルの読み込み
// @param pass モデルのパス
// @return なし
//----------------------------------------------------------------------
void DrawGraphComponent::LoadPass(const char* pass) {
	DrawComponent::LoadPass(pass);
	m_Handle = LoadGraph(m_Pass);
}

//----------------------------------------------------------------------
// @brief モデルの設定・描画
// @return なし
//----------------------------------------------------------------------
void DrawGraphComponent::Update(){
	DrawComponent::Update();
	//描画
	DrawGraph(static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y), m_Handle, true);
}


