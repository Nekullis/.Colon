#include "../AppFrame/source/System/Header/Component/LogicComponent.h"
#include "../AppFrame/source/System/Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
LogicComponent::LogicComponent(ObjectBase* owner, int updateowder) :Component(owner, updateowder) {
	m_Owner->AddComponent(this);
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
LogicComponent::~LogicComponent(){
}

//----------------------------------------------------------------------
// @brief ���f���̐ݒ�E�`��
// @return �Ȃ�
//----------------------------------------------------------------------
void LogicComponent::Update(){
	Component::Update();
}
