//----------------------------------------------------------------------
// @filename AICompornent.cpp
// @author: Fukuma Kyohei
// @explanation
// AI�̏�Ԃ��Ǘ�����R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/AIComponent.h"
#include "../../Header/Component/AIState.h"
#include "../../Header/Component/Object/ObjectBase.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
AIComponent::AIComponent(ObjectBase* owner, int updateowder) :LogicComponent(owner, updateowder)
{
	m_Owner->AddComponent(this);
	mState = nullptr;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
AIComponent::~AIComponent()
{
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void AIComponent::Update()
{
	//���݂̏�ԂȂ�΍X�V����
	if (mState) { mState->Update();}
}

//----------------------------------------------------------------------
// @brief ��Ԃ̕ύX
// @param name ��Ԃ̖��O
// @return �Ȃ�
//----------------------------------------------------------------------
void AIComponent::ChangeState(const std::string& name)
{
	//���݂̏�Ԃ���o��
	if (mState) { mState->OnExit(); }
	//�V������Ԃ�z�񂩂�T��
	auto itr = mStateMap.find(name);
	//��Ԃ��z������猩������
	if (itr != mStateMap.end())
	{
		//��Ԃ𖼑O�ɕR�t����ꂽ�ʂ̏�Ԃ�
		mState = itr->second;
		//�V������Ԃɓ���
		mState->OnEnter();
	}
	//������Ȃ�����
	else { mState = nullptr; }
}

//----------------------------------------------------------------------
// @brief ��Ԃ̓o�^
// @param state ���
// @return �Ȃ�
//----------------------------------------------------------------------
void AIComponent::RegisterState(AIState* state)
{
	//���O�ƕR�t���Ĕz����ɓ����
	mStateMap.emplace(state->GetName(), state);
}
