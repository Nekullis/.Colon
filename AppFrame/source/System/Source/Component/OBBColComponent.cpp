//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBB�̓����蔻��ɗp����N���X
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/OBBColComponent.h"
#include "../../AppFrame/source/System/Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
OBBColComponent::OBBColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder)
{
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
OBBColComponent::~OBBColComponent()
{
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void OBBColComponent::Update()
{
}
