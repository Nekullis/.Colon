//----------------------------------------------------------------------
// @filename ObjectBase.cpp
// @author: Fukuma Kyohei
// @explanation
// �I�u�W�F�N�g�̐e�N���X
// �I�u�W�F�N�g�͂��̃N���X�A�܂��͂��̔h���N���X���琶��
//----------------------------------------------------------------------
#include "../../../Header/Component/Object/ObjectBase.h"
#include "../../../Header/Component/LogicComponent.h"
#include "../../../Header/Component/DrawComponent.h"
#include <algorithm>

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
ObjectBase::ObjectBase(ModeBase* game)
{
	//�ʒu
	m_Pos = { 0 };
	//�p�x
	m_Rotation = { 0 };
	//�X�P�[��
	m_Scale = { 0 };
	m_IsTargetting = false;

	m_Game = nullptr;

	m_State = State::ACTIVE;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
ObjectBase::~ObjectBase()
{

}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Process()
{
	for(auto&& comp : m_Components)
	{
		comp->Update();
	}
}

//----------------------------------------------------------------------
// @brief �`�揈��
// @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Render()
{
#if _DEBUG
	Debug();
#endif
}

//----------------------------------------------------------------------
// @brief �f�o�b�O�\��
// @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Debug()
{

}

//----------------------------------------------------------------------
// @brief �R���|�[�l���g�̒ǉ�
// @param component �R���|�[�l���g
// @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::AddComponent(Component* component)
{
	//�R���e�i�Ɋi�[����
	m_Components.push_back(component);
	//�i�[�����R���|�[�l���g�̕��ёւ�
	std::sort(m_Components.begin(), m_Components.end(), [](Component* a, Component* b) {return a->GetUpdateOwder() < b->GetUpdateOwder(); });
	
}

//----------------------------------------------------------------------
// @brief �R���|�[�l���g�̍폜
// @param component �R���|�[�l���g
// @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::RemoveComponent(Component* component)
{
	//�����ɍ����R���|�[�l���g��T��
	auto itr = std::find(m_Components.begin(), m_Components.end(), component);
	//�T�����R���|�[�l���g�̏���
	if (itr != m_Components.end()) { m_Components.erase(itr); }
}

