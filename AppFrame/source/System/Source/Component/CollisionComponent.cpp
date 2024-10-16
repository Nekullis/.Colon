//----------------------------------------------------------------------
// @filename CollisionComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �Փ˔���p�R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/CollisionComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"
#include "../../Header/Collision/MyStructure.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
CollisionComponent::CollisionComponent(ObjectBase* owner, int updateowder) :LogicComponent(owner, updateowder)
{
	m_Col = nullptr;
	m_Owner = owner;
	mManager = nullptr;
	mType = COLLISIONTYPE::NONE;
	mRadius = 0;
	mLineSeg = 0;
	mGroup = COLLISIONGROUP::NONE;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
CollisionComponent::~CollisionComponent()
{
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void CollisionComponent::Update()
{
	mPos = m_Owner->GetPos();
	m_Col->pos = mPos;
}
