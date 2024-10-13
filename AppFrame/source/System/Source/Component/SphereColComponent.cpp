//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// ���̓����蔻��ɗp����N���X
//----------------------------------------------------------------------
#include "../AppFrame/source/System/Header/Component/SphereColComponent.h"
#include "../../AppFrame/source/System/Header/Component/Object/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
SphereColComponent::SphereColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder){
	m_Col = new Sphere();
	mType = COLLISIONTYPE::SPHERE;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
SphereColComponent::~SphereColComponent(){
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void SphereColComponent::Update(){
	CollisionComponent::Update();
}
