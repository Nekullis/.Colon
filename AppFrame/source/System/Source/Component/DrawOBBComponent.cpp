//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// OBB描画クラス
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawOBBComponent.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawOBBComponent::DrawOBBComponent(ObjectBase* owner, int updateowder):DrawComponent(owner,updateowder)
{
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawOBBComponent::~DrawOBBComponent(){
}

//----------------------------------------------------------------------
// @brief 読み込み
// @param pass モデルのパス
// @return なし
//----------------------------------------------------------------------
void DrawOBBComponent::Update(){
	DrawComponent::Update();
}

//----------------------------------------------------------------------
// @brief モデルの設定・描画
// @return なし
//----------------------------------------------------------------------
void DrawOBBComponent::LoadPass(const char* pass){
	DrawComponent::LoadPass(pass);
}
