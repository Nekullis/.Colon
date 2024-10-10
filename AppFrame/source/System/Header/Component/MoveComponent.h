//----------------------------------------------------------------------
// @filename MoveComponent.h
// @author: Fukuma Kyohei
// @explanation
// キャラクターの移動を制御するコンポーネント
//----------------------------------------------------------------------
#pragma once
#include "LogicComponent.h"
class MoveComponent : public LogicComponent
{
public:
	MoveComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~MoveComponent();
	//更新
	void Update()override;
	//ゲッター
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	//セッター
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
protected:
	//回転制御(ラジアン/秒)
	float mAngularSpeed;
	//前進運動制御(単位長/秒)
	float mForwardSpeed;
};

