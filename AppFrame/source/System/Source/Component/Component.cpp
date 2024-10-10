//----------------------------------------------------------------------
// @filename Component.cpp
// @author: Fukuma Kyohei
// @explanation
// �R���|�[�l���g(�\���v�f)�̐e�N���X
//----------------------------------------------------------------------
#include "../../Header/Component/Component.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
Component::Component(ObjectBase* owner, int updateowder)
{
	m_Owner = owner;
	m_UpdateOwder = updateowder;
	m_Owner->AddComponent(this);
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Component::~Component()
{
	m_Owner->RemoveComponent(this);
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void Component::Update()
{

}
