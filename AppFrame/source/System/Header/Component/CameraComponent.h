//----------------------------------------------------------------------
// @filename CameraComponent.h
// @author: Fukuma Kyohei
// @explanation
// ゲーム内のカメラ処理全般制御するコンポーネント
//----------------------------------------------------------------------
#pragma once
#include <utility>
#include "LogicComponent.h"
#include "../Math/Vector3D.h"
#include "../Input/XInput.h"
class CameraComponent : public LogicComponent
{
public:
	CameraComponent(ObjectBase* owner,int updateowder = 100);
	virtual ~CameraComponent();
	static CameraComponent* m_CameraInstance;
	void Update()override;
	//ゲッター
	static CameraComponent* GetInstance() { return m_CameraInstance; }
	Vector3D GetTarget() const{ return m_Target; }
	Vector3D GetDir() const{ return m_Dir; }
	Vector3D GetPos() const{ return m_Pos; }
	//セッター
	void SetTarget(Vector3D vec) { m_Target = vec; }
protected:
	XInput* m_Pad;
	//カメラ位置
	Vector3D m_Pos;
	Vector3D m_Dir;
	//カメラ注視点
	Vector3D m_Target;
	//最短描画距離
	float m_Near;
	//最長描画距離
	float m_Far;
	//オブジェクトからカメラまでの距離
	float m_Distance;
	//ばね定数
	float m_Spring;
	//減衰定数
	float m_DampFactor;
	//位置と速度
	Vector3D m_CurrentPos;
	Vector3D m_CurrentVelocity;
};

