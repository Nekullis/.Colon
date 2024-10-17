//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// 球の描画用コンポーネントクラス
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawSphereComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
DrawSphereComponent::DrawSphereComponent(ObjectBase* owner, int updateowder):DrawComponent(owner,updateowder){
	m_Sphere = new Sphere();
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawSphereComponent::~DrawSphereComponent(){
	delete m_Sphere;
	m_Sphere = nullptr;
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void DrawSphereComponent::Update(){
	DrawComponent::Update();
	m_Sphere->pos = m_Pos;
	m_Sphere->Render(GetColor(255, 255, 255));
}
