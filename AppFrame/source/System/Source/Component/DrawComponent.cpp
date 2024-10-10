//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// 描画用コンポーネントの基底クラス
//----------------------------------------------------------------------
#include"../../AppFrame/source/System/Header/Component/DrawComponent.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawComponent::DrawComponent(ObjectBase* owner, int updateowder):Component(owner, updateowder) {
	m_Owner = owner;
	m_Handle = 0;
	m_Pass = "";
	m_Pos = Vector3D(0.0f, 0.0f, 0.0f);
	m_Scale = Vector3D(1.0f, 1.0f, 1.0f);

}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawComponent::~DrawComponent(){
}

//----------------------------------------------------------------------
// @brief 読み込み
// @param pass モデルのパス
// @return なし
//----------------------------------------------------------------------
void DrawComponent::LoadPass(const char* pass) {
	m_Pass = pass;
}

//----------------------------------------------------------------------
// @brief モデルの設定・描画
// @return なし
//----------------------------------------------------------------------
void DrawComponent::Update(){
	Component::Update();
}
