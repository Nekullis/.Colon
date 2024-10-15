//----------------------------------------------------------------------
// @filename Component.h
// @author: Fukuma Kyohei
// @explanation
// ���t���[���X�V�����n�R���|�[�l���g�̐e�N���X
//----------------------------------------------------------------------
#pragma once
#include "Component.h"
class LogicComponent :public Component
{
public:
	LogicComponent(ObjectBase* owner, int updateowder = 100);
	virtual ~LogicComponent();
	//�X�V
	virtual void Update()override;
};

