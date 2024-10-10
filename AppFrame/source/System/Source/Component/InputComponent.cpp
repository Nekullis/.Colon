//----------------------------------------------------------------------
// @filename InputComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// 入力情報を獲得しキャラクターの回転・座標を制御するコンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/InputComponent.h"
#include "../../Header/Component/CameraComponent.h"
#include "../../Header/Math/Matrix3D.h"
#include "../../Header/Math/MyMath.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
//----------------------------------------------------------------------
InputComponent::InputComponent(ObjectBase* owner, int updateowder) :MoveComponent(owner, updateowder)
{
	//コントローラー初期化
	m_Pad = new XInput();
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
InputComponent::~InputComponent()
{
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void InputComponent::Update()
{
	m_Pad->Input();
	
}
