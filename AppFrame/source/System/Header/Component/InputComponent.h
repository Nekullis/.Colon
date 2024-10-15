//----------------------------------------------------------------------
// @filename InputComponent.h
// @author: Fukuma Kyohei
// @explanation
// ���͏����l�����L�����N�^�[�̉�]�E���W�𐧌䂷��R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "MoveComponent.h"
class InputComponent : public MoveComponent
{
public:
	InputComponent(class ObjectBase* owner, int updateowder = 100);
	virtual ~InputComponent();
	void Update()override;
	//�Q�b�^�[
	class XInput* GetPad() { return m_Pad; }
protected:
	class XInput* m_Pad;
};

