//----------------------------------------------------------------------
// @filename CameraComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �J�v�Z���^�̏Փ˔���p�R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/CapsuleColComponent.h"

CapsuleColComponent* CapsuleColComponent::capInstance = nullptr;

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
CapsuleColComponent::CapsuleColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder)
{
	capInstance = this;
	//�^�C�v������
	mType = COLLISIONTYPE::CAPSULE;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// ��return �Ȃ�
//----------------------------------------------------------------------
CapsuleColComponent::~CapsuleColComponent()
{

}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void CapsuleColComponent::Update()
{
	CollisionComponent::Update();
}
