//----------------------------------------------------------------------
// @filename MoveComponent.h
// @author: Fukuma Kyohei
// @explanation
// �L�����N�^�[�̈ړ��𐧌䂷��R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "LogicComponent.h"
class MoveComponent : public LogicComponent
{
public:
	MoveComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~MoveComponent();
	//�X�V
	void Update()override;
	//�Q�b�^�[
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	//�Z�b�^�[
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
protected:
	//��]����(���W�A��/�b)
	float mAngularSpeed;
	//�O�i�^������(�P�ʒ�/�b)
	float mForwardSpeed;
};

