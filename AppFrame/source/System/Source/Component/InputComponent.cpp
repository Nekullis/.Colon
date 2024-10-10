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
	////アナログパッドの値をatan2関数で角度を得る
	//float dir = atan2f(static_cast<float>(mPad->GetLy() * -1),static_cast<float>(mPad->GetLx() * -1));
	//float com_dir_y = CameraComponent::GetInstance()->GetDir().y;
	////アナログパッドが動いているのなら
	//if(mPad->IsInputStickLeft())
	//{
	//	//参照オブジェクトの位置を取得
	//	Vector3D pos = m_Owner->GetPos();
	//	//セッターで得た速度を代入
	//	float speed = mForwardSpeed;
	//	//y軸の回転行列を得る
	//	Matrix3D matrix = Matrix3D::MGetRotY(com_dir_y);
	//	//移動量を得る
	//	Vector3D move{ speed * cosf(dir) ,0,speed * sinf(dir) };
	//	//移動量とカメラの回転値の積を求め、カメラの向きと前方ベクトルを一致させる
	//	move = move * matrix;
	//	//位置に反映
	//	pos += move;
	//	//セッターでプレイヤーの位置情報に代入
	//	m_Owner->SetPos(pos);
	//	//移動後の回転値を求める
	//	Vector3D rot = Vector3D(0, -(dir + Math::DegToRad(90.0f))+ com_dir_y, 0);
	//	//プレイヤーの回転値に反映
	//	m_Owner->SetRotation(rot);
	//}
	//
}
