//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// OBB�̓����蔻��ɗp����N���X
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/OBBColComponent.h"
#include "../../AppFrame/source/System/Header/Component/Object/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
OBBColComponent::OBBColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder){
	m_Col = new OBB();
	mType = COLLISIONTYPE::OBB;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
OBBColComponent::~OBBColComponent(){
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void OBBColComponent::Update(){
	CollisionComponent::Update();
}