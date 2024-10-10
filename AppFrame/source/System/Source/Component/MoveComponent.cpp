//----------------------------------------------------------------------
// @filename MoveComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �L�����N�^�[�̈ړ��𐧌䂷��R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/MoveComponent.h"
#include <Math.h>
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
MoveComponent::MoveComponent(ObjectBase* owner, int updateowder) :LogicComponent(owner, updateowder)
{
	m_Owner->AddComponent(this);
	mAngularSpeed = 0.0f;
	mForwardSpeed = 0.0f;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
MoveComponent::~MoveComponent()
{

}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void MoveComponent::Update()
{
	Component::Update();
}
