//----------------------------------------------------------------------
// @filename Component.h
// @author: Fukuma Kyohei
// @explanation
// 毎フレーム更新処理系コンポーネントの親クラス
//----------------------------------------------------------------------
#pragma once
#include "Component.h"
class LogicComponent :public Component
{
public:
	LogicComponent(ObjectBase* owner, int updateowder = 100);
	virtual ~LogicComponent();
	//更新
	virtual void Update()override;
};

