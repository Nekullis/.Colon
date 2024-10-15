//----------------------------------------------------------------------
// @filename InputComponent.h
// @author: Fukuma Kyohei
// @explanation
// 入力情報を獲得しキャラクターの回転・座標を制御するコンポーネント
//----------------------------------------------------------------------
#pragma once
#include "MoveComponent.h"
class InputComponent : public MoveComponent
{
public:
	InputComponent(class ObjectBase* owner, int updateowder = 100);
	virtual ~InputComponent();
	void Update()override;
	//ゲッター
	class XInput* GetPad() { return m_Pad; }
protected:
	class XInput* m_Pad;
};

