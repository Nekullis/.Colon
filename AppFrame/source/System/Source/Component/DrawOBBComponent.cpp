//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// OBB描画クラス
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawOBBComponent.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawOBBComponent::DrawOBBComponent(ObjectBase* owner, int updateowder):DrawComponent(owner,updateowder){
	m_Collision = new OBB();
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawOBBComponent::~DrawOBBComponent(){
	delete m_Collision;
}

//----------------------------------------------------------------------
// @brief モデルの設定・描画
// @return なし
//----------------------------------------------------------------------
void DrawOBBComponent::Update(){
	DrawComponent::Update();
	m_Collision->Render(GetColor(255,255,255));
}

